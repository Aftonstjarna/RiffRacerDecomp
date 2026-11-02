#include "impl.hpp"
using riff::NarrowString32;
extern "C" void __attribute__((cdecl)) original_narrow_range_destroy(NarrowString32*, NarrowString32*, unsigned, unsigned);
extern "C" void test_write(const char*, unsigned);
// Optional local linker mapping. Never dereference an unmapped original IAT.
riff::Delete oracle_import __attribute__((section(".oracle_import"), aligned(4))) = nullptr;
static NarrowString32 *active;
static unsigned cursor;
static unsigned calls, addresses[16], snapshots[16][3];
static void __attribute__((cdecl)) observe_delete(void* p) {
    unsigned n = calls++;
    if (n < 16) {
        addresses[n] = reinterpret_cast<unsigned>(p);
        // Find the current heap element by invocation order.
        unsigned k = cursor;
        for (; k < 8; ++k) if (active[k].capacity >= 16u) {
            break;
        }
        cursor = k+1;
        snapshots[n][0] = k;
        snapshots[n][1] = active[k].size;
        snapshots[n][2] = active[k].capacity;
    }
}
static bool equal(const void* a, const void* b, unsigned n) {
    const auto* x = static_cast<const unsigned char*>(a);
    const auto* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
struct Fixture { unsigned before; NarrowString32 strings[8]; unsigned after; };
static void initialize(Fixture& f, unsigned seed) {
    auto* p = reinterpret_cast<unsigned char*>(&f);
    for(unsigned i=0;i<sizeof f;++i) p[i]=static_cast<unsigned char>(i*17+seed);
    const unsigned caps[8]={0,15,16,17,0x7fffffff,0x80000000,0xffffffff,1};
    for(unsigned i=0;i<8;++i) {
        f.strings[i].capacity=caps[(i+seed)%8];
        f.strings[i].size=seed*31+i;
        // Include null delete argument: routine does not filter it.
        unsigned addr=i==3 ? 0 : 0x12340000u+i*0x100+seed;
        for(unsigned j=0;j<4;++j) f.strings[i].storage[j]=addr>>(8*j);
    }
}
extern "C" int test_main() {
    // Equal pointers bypass every access including the IAT read.
    original_narrow_range_destroy(nullptr,nullptr,0xdead,0xbeef);
    riff::destroy_narrow_range(nullptr,nullptr,nullptr);
    const bool mapped = reinterpret_cast<unsigned>(&oracle_import)==0x92d4b0u;
    oracle_import=observe_delete;
    for(unsigned seed=0;seed<8;++seed) for(unsigned begin=0;begin<=8;++begin)
    for(unsigned end=begin;end<=8;++end) {
        Fixture a,b,expected;
        initialize(a,seed); initialize(b,seed); initialize(expected,seed);
        for(unsigned i=begin;i<end;++i) {
            expected.strings[i].capacity=15; expected.strings[i].size=0;
            expected.strings[i].storage[0]=0;
        }
        calls=0; cursor=begin; active=b.strings;
        riff::destroy_narrow_range(b.strings+begin,b.strings+end,observe_delete);
        if(!equal(&b,&expected,sizeof b)) return 1;
        unsigned count=calls, saved[16], state[16][3];
        for(unsigned i=0;i<count;++i) {saved[i]=addresses[i]; for(unsigned j=0;j<3;++j) state[i][j]=snapshots[i][j];}
        unsigned want=0;
        for(unsigned i=begin;i<end;++i) if(a.strings[i].capacity>=16u) ++want;
        if(count!=want) return 2;
        unsigned n=0;
        for(unsigned i=begin;i<end;++i) if(a.strings[i].capacity>=16u) {
            unsigned ptr=0;
            for(unsigned j=0;j<4;++j) ptr|=unsigned(a.strings[i].storage[j])<<(8*j);
            if(saved[n]!=ptr || state[n][0]!=i || state[n][1]!=a.strings[i].size || state[n][2]!=a.strings[i].capacity) return 5;
            ++n;
        }
        if(mapped || begin==end) {
            calls=0; cursor=begin; active=a.strings;
            original_narrow_range_destroy(a.strings+begin,a.strings+end,0xaabbccdd,0x99887766);
            if(!equal(&a,&b,sizeof a) || calls!=count) return 3;
            for(unsigned i=0;i<count;++i) if(saved[i]!=addresses[i] || !equal(state[i],snapshots[i],12)) return 4;
        }
    }
    if(mapped) test_write("Full original comparison passed\n",31);
    else test_write("Empty original comparisons passed; nonempty requires IAT mapping\n",64);
    return 0;
}
