#include "impl.hpp"
extern "C" void __attribute__((fastcall)) original_script_stack_relocate_pointers(riff::ScriptState*, uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
namespace {
struct Fixture {
    uint32_t guard0[8];
    riff::ScriptState state;
    uint32_t gap[8];
    riff::ScriptFrame frames[6];
    riff::OpenUpvalue upvalues[5];
    uint32_t guard1[8];
};
Fixture data, initial, expected;
uint32_t fsStorage[8];
uint32_t address(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
void copy(Fixture& to, const Fixture& from) {
    unsigned char* d = reinterpret_cast<unsigned char*>(&to);
    const unsigned char* s = reinterpret_cast<const unsigned char*>(&from);
    for (unsigned i=0; i<sizeof(Fixture); ++i) d[i]=s[i];
}
bool equal(const Fixture& a, const Fixture& b) {
    const unsigned char* x = reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y = reinterpret_cast<const unsigned char*>(&b);
    for (unsigned i=0; i<sizeof(Fixture); ++i) if (x[i]!=y[i]) return false;
    return true;
}
uint32_t expectedAddress(uint32_t value, uint32_t oldBase, uint32_t newBase) {
    // Independent expression of the signed floor-division arithmetic.
    uint32_t difference = value-oldBase;
    int64_t signedDifference = difference;
    if (difference & 0x80000000u) signedDifference -= 0x100000000LL;
    int64_t index = signedDifference >= 0 ? signedDifference/8 : -((-signedDifference+7)/8);
    return newBase + static_cast<uint32_t>(index*8);
}
int run(unsigned frameCount, unsigned nodeCount, uint32_t oldBase,
        uint32_t newBase, unsigned salt, bool partialEnd) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&data);
    for (unsigned i=0; i<sizeof(data); ++i) bytes[i]=static_cast<unsigned char>(i*37+salt);
    data.state.stack=newBase;
    data.state.firstFrame=address(data.frames);
    data.state.currentFrame = frameCount ? address(data.frames+frameCount-1)+(partialEnd?7:0) : address(data.frames)-1;
    data.state.openUpvalues=nodeCount?address(data.upvalues):0;
    const uint32_t offsets[12]={0,8,80,0xfffffff8u,0xffffffffu,1,7,9,0x7fffffffu,0x80000000u,0x80000007u,0xfffff001u};
    data.state.top=oldBase+offsets[salt%12];
    data.state.base=oldBase+offsets[(salt+3)%12];
    for(unsigned i=0;i<6;++i) {
        data.frames[i].base=oldBase+offsets[(salt+i)%12];
        data.frames[i].function=oldBase+offsets[(salt+i+1)%12];
        data.frames[i].top=oldBase+offsets[(salt+i+2)%12];
    }
    for(unsigned i=0;i<5;++i) {
        data.upvalues[i].next=i+1<nodeCount?address(data.upvalues+i+1):0;
        data.upvalues[i].value=oldBase+offsets[(salt+i+5)%12];
    }
    copy(initial,data);
    copy(expected,data);
    expected.state.top=expectedAddress(data.state.top,oldBase,newBase);
    expected.state.base=expectedAddress(data.state.base,oldBase,newBase);
    for(unsigned i=0;i<frameCount;++i) {
        expected.frames[i].top=expectedAddress(data.frames[i].top,oldBase,newBase);
        expected.frames[i].base=expectedAddress(data.frames[i].base,oldBase,newBase);
        expected.frames[i].function=expectedAddress(data.frames[i].function,oldBase,newBase);
    }
    for(unsigned i=0;i<nodeCount;++i)
        expected.upvalues[i].value=expectedAddress(data.upvalues[i].value,oldBase,newBase);
    original_script_stack_relocate_pointers(&data.state, oldBase);
    if(test_get_fs_head()!=fsStorage[0]) return 1;
    if(!equal(data,expected)) return 2;
    // Restore the very same addresses before the recovered implementation;
    // whole-fixture comparison also checks list links, unused nodes/frames,
    // state fields, stack bounds/capacity, and surrounding canaries.
    copy(data,initial);
    data.state.relocatePointers(oldBase);
    if(!equal(data,expected)) return 3;
    return 0;
}
}
extern "C" int test_main() {
    fsStorage[0]=0xffffffffu;
    if(test_install_fs(fsStorage)!=0) return 10;
    const uint32_t bases[][2]={{0x10000000u,0x20000000u},{0x20000000u,0x10000000u},
        {0x12345000u,0x12345000u},{0xfffffff8u,3u},{0,0xfffffffcu}};
    for(unsigned b=0;b<5;++b)
        for(unsigned salt=0;salt<12;++salt)
            for(unsigned n=0;n<=5;++n) {
                int result=run(n,n,bases[b][0],bases[b][1],salt,(salt&1)!=0);
                if(result) return 20+result;
                result=run(n,5-n,bases[b][0],bases[b][1],salt,false);
                if(result) return 30+result;
            }
    const char message[]="relocation: 720 oracle comparisons passed\n";
    test_write(message, sizeof(message)-1);
    return 0;
}
