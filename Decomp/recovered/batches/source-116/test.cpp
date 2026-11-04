#include "impl.hpp"
#include <stddef.h>
extern "C" void test_write(const char*, unsigned);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_substring(NarrowString*, const NarrowString*, uint32_t, uint32_t);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_erase(NarrowString*, uint32_t, uint32_t);
extern "C" void* memcpy(void* d, const void* s, size_t n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    const unsigned char* b=static_cast<const unsigned char*>(s);
    for(size_t i=0;i<n;++i)a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d,int v,size_t n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    for(size_t i=0;i<n;++i)a[i]=static_cast<unsigned char>(v);
    return d;
}
static bool equal(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
static void* jump_state[5];
static const char* error_message;
static unsigned error_kind;
RIFF_NORETURN void narrow_out_of_range(const char* p) {
    error_message=p;error_kind=1;__builtin_longjmp(jump_state,1);
}
RIFF_NORETURN void narrow_length_error(const char* p) {
    error_message=p;error_kind=2;__builtin_longjmp(jump_state,1);
}
// Optional local linker mappings intercept ONLY unavailable dependencies.
// These C++ test doubles are not original CRT or recovered target bytes.
extern "C" __attribute__((section(".oracle_copy"),noinline))
void* oracle_copy(void* d,const void* s,unsigned n) { return memcpy(d,s,n); }
extern "C" void* oracle_move(void* d,const void* s,unsigned n) {
    // erase(0,offset) only moves left, excluding the terminator.
    return memcpy(d,s,n);
}
extern "C" {
__attribute__((section(".oracle_iat"),aligned(4))) void* oracle_iat[208];
}
static bool mapped;
static unsigned copies,grows,requested,preserved;
static char growth_buffer[128];
static bool fail_growth;
void* narrow_copy(void* d,const void* s,uint32_t n) {
    ++copies;return memcpy(d,s,n);
}
NarrowString* RIFF_THISCALL NarrowString::erase(uint32_t p,uint32_t n) {
    return original_narrow_erase(this,p,n);
}
void RIFF_THISCALL NarrowString::grow(uint32_t n,uint32_t old) {
    ++grows;requested=n;preserved=old;
    if(fail_growth)__builtin_longjmp(jump_state,1);
    // Test-only controlled relocation; no assertion about allocator policy.
    memset(growth_buffer,0x79,sizeof growth_buffer);
    storage.heap=growth_buffer+8;capacity=95;
}
struct Fixture { uint32_t before[2]; NarrowString s; uint32_t after[2]; char heap[112]; };
static char* data(Fixture& f) { return f.s.capacity<16?f.s.storage.local:f.s.storage.heap; }
static void init(Fixture& f,unsigned cap,unsigned len) {
    memset(&f,0xa5,sizeof f);f.s.capacity=cap;f.s.length=len;
    if(cap>=16)f.s.storage.heap=f.heap+8;
    for(unsigned i=0;i<len;++i)data(f)[i]=static_cast<char>(i%5==0?0:i*37+19);
    data(f)[len]=0x61; // Nonzero old terminator detects exact writes.
}
static void clone(Fixture& d,const Fixture& s) {
    memcpy(&d,&s,sizeof d);if(d.s.capacity>=16)d.s.storage.heap=d.heap+8;
}
static bool equivalent(Fixture& a,Fixture& b) {
    char* saved=b.s.storage.heap;
    if(b.s.capacity>=16)b.s.storage.heap=a.s.storage.heap;
    bool ok=equal(&a,&b,sizeof a);
    if(b.s.capacity>=16)b.s.storage.heap=saved;
    return ok;
}
static unsigned comparisons,expected_checks;
static int run_case(unsigned cap,unsigned len,unsigned src_cap,unsigned src_len,
                    unsigned pos,unsigned count,bool self) {
    Fixture a,b,e,src,saved;init(a,cap,len);clone(b,a);clone(e,a);
    init(src,src_cap,src_len);clone(saved,src);
    unsigned available=(self?len:src_len)-pos;
    unsigned n=count<available?count:available;
    if(!self&&n>cap)return 0;
    // With no IAT placement, original erase cannot shift a nonempty tail.
    if(self&&pos&&n&&!mapped)return 0;
    if(self) {
        data(e)[pos+n]=0;
        for(unsigned i=0;i<n;++i)data(e)[i]=data(e)[pos+i];
    } else for(unsigned i=0;i<n;++i)data(e)[i]=data(src)[pos+i];
    data(e)[n]=0;e.s.length=n;
    copies=grows=0;
    if(a.s.assign_substring(self?&a.s:&src.s,pos,count)!=&a.s)return 1;
    if(grows||copies!=unsigned(!self&&n!=0))return 2;
    if(!equivalent(a,e)||!equivalent(src,saved))return 3;
    ++expected_checks;
    if(self||n==0||mapped) {
        if(original_narrow_assign_substring(&b.s,self?&b.s:&src.s,pos,count)!=&b.s)return 4;
        if(!equivalent(a,b)||!equivalent(src,saved))return 5;
        ++comparisons;
    }
    return 0;
}
static int error_case(bool original,bool self,unsigned len,unsigned pos,unsigned count,unsigned kind) {
    Fixture d,s,db,sb;init(d,15,3);init(s,15,0);
    if(self)d.s.length=len;else s.s.length=len;
    clone(db,d);clone(sb,s);error_kind=0;error_message=0;copies=grows=0;
    if(__builtin_setjmp(jump_state)==0) {
        if(original)original_narrow_assign_substring(&d.s,self?&d.s:&s.s,pos,count);
        else d.s.assign_substring(self?&d.s:&s.s,pos,count);
        return 6;
    }
    if(error_kind!=kind||copies||grows||!equivalent(d,db)||!equivalent(s,sb))return 7;
    if(original) {
        if(reinterpret_cast<size_t>(error_message)!=(kind==1?0x99995cu:0x99994cu))return 8;
    } else {
        const char* text=kind==1?"invalid string position":"string too long";
        unsigned n=0;while(text[n])++n;
        if(!equal(text,error_message,n+1))return 9;
    }
    return 0;
}
static int growth_case(unsigned cap,unsigned old,unsigned src_cap,unsigned len,unsigned pos,unsigned count,bool fail) {
    Fixture d,s,db,sb;init(d,cap,old);init(s,src_cap,len);clone(db,d);clone(sb,s);
    unsigned n=len-pos;if(count<n)n=count;if(n<=cap)return 0;
    copies=grows=0;fail_growth=fail;
    if(__builtin_setjmp(jump_state)==0) {
        if(d.s.assign_substring(&s.s,pos,count)!=&d.s)return 10;
        if(fail)return 11;
    } else if(!fail)return 12;
    if(grows!=1||requested!=n||preserved!=old||!equivalent(s,sb))return 13;
    if(fail) {
        if(copies||!equivalent(d,db))return 14;
    } else {
        if(copies!=1||d.s.length!=n||d.s.capacity!=95||d.s.storage.heap!=growth_buffer+8)return 15;
        for(unsigned i=0;i<n;++i)if(d.s.storage.heap[i]!=data(s)[pos+i])return 16;
        if(d.s.storage.heap[n]!=0)return 17;
        // Only the heap pointer and two metadata words may change in object.
        db.s.storage.heap=d.s.storage.heap;db.s.length=n;db.s.capacity=95;
        if(!equal(&d,&db,sizeof d))return 18;
        for(unsigned i=0;i<sizeof growth_buffer;++i)
            if((i<8||i>8+n)&&growth_buffer[i]!=0x79)return 19;
    }
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(NarrowString)==24,"original x86 layout");
    static_assert(offsetof(NarrowString,length)==16,"length");
    static_assert(offsetof(NarrowString,capacity)==20,"capacity");
    mapped=reinterpret_cast<size_t>(oracle_iat)==0x92d168u
        &&reinterpret_cast<size_t>(&oracle_copy)==0x8f8d66u;
    oracle_iat[0]=reinterpret_cast<void*>(&narrow_length_error);
    oracle_iat[1]=reinterpret_cast<void*>(&narrow_out_of_range);
    oracle_iat[207]=reinterpret_cast<void*>(&oracle_move);
    const unsigned caps[]={0,7,15,16,31,63};
    const unsigned counts[]={0,1,2,7,15,16,31,63,64,0xfffffffeu,0xffffffffu};
    for(unsigned c=0;c<6;++c)for(unsigned len=0;len<=caps[c];++len)
        for(unsigned pos=0;pos<=len;++pos)for(unsigned k=0;k<11;++k) {
            int r=run_case(caps[c],len,0,0,pos,counts[k],true);if(r)return r;
        }
    for(unsigned c=0;c<6;++c)for(unsigned s=0;s<6;++s)
        for(unsigned len=0;len<=caps[s];++len)for(unsigned pos=0;pos<=len;++pos)
            for(unsigned k=0;k<11;++k) {
                int r=run_case(caps[c],caps[c],caps[s],len,pos,counts[k],false);if(r)return 20+r;
            }
    for(unsigned original=0;original<=unsigned(mapped);++original) {
        for(unsigned self=0;self<2;++self) {
            int r=error_case(original!=0,self!=0,3,4,0,1);if(r)return 40+r;
            r=error_case(original!=0,self!=0,3,0xffffffffu,1,1);if(r)return 40+r;
        }
        int r=error_case(original!=0,false,0xffffffffu,0,0xffffffffu,2);if(r)return 40+r;
    }
    for(unsigned c=0;c<4;++c)for(unsigned s=4;s<6;++s)
        for(unsigned pos=0;pos<4;++pos)for(unsigned fail=0;fail<2;++fail) {
            int r=growth_case(caps[c],caps[c],caps[s],caps[s],pos,0xffffffffu,fail!=0);if(r)return 60+r;
        }
    if(!comparisons||!expected_checks)return 99;
    if(mapped) {
        const char m[]="PASS: original non-growth and error comparisons with test CRT hooks; controlled C++ growth checks.\n";
        test_write(m,sizeof(m)-1);
    } else {
        const char m[]="PASS: original empty/no-shift comparisons; C++ copy/growth/error checks. Full original copy/shift/error comparisons require mapped test dependencies.\n";
        test_write(m,sizeof(m)-1);
    }
    return 0;
}
