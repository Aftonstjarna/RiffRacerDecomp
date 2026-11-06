#include "impl.hpp"
#include <stddef.h>
extern "C" WideString* __attribute__((fastcall)) original_wide_construct_terminated_register(WideString*,const uint16_t*);
extern "C" WideString* __attribute__((thiscall)) original_wide_assign_range(WideString*,const uint16_t*,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[8];
static unsigned fs_failure;
static unsigned helper_calls, copy_calls;
static const uint16_t* forwarded;
static uint32_t forwarded_count;
WideString* RIFF_THISCALL WideString::assign_range(const uint16_t* p,uint32_t n) {
    ++helper_calls; forwarded=p; forwarded_count=n;
    original_wide_assign_range(this,p,n);
    if(test_get_fs_head()!=fs_storage[0])++fs_failure;
    return 0; // Verify that constructor returns this independently of helper EAX.
}
extern "C" void* copy_bytes(void* d,const void* s,unsigned n) {
    ++copy_calls;
    unsigned char* a=static_cast<unsigned char*>(d);
    const unsigned char* b=static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i)a[i]=b[i];
    return d;
}
extern "C" {
void* (*copy_iat)(void*,const void*,unsigned) __attribute__((section(".test_iat"),used,aligned(4)))=copy_bytes;
}
static void fill(void* p,unsigned n,unsigned char value) {
    unsigned char* a=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i)a[i]=value;
}
static bool equal(const void* p,const void* q,unsigned n) {
    const unsigned char* a=static_cast<const unsigned char*>(p);
    const unsigned char* b=static_cast<const unsigned char*>(q);
    for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;
    return true;
}
struct Guard { uint32_t before[2]; WideString value; uint32_t after[2]; };
static int run(unsigned n,unsigned pattern,unsigned offset,bool alias) {
    Guard a,b,expected;
    uint16_t input[32],saved[32];
    fill(&a,sizeof(a),static_cast<unsigned char>(0x91+pattern));
    fill(input,sizeof(input),0x5a);
    for(unsigned i=0;i<n;++i)input[offset+i]= pattern==0?0x41:pattern==1?0xffff:static_cast<uint16_t>(0xd800+i);
    input[offset+n]=0;
    if(alias)for(unsigned i=0;i<=n;++i)a.value.storage.local[i]=input[offset+i];
    b=a; expected=a;
    for(unsigned i=0;i<32;++i)saved[i]=input[i];
    const uint16_t* pa=alias?a.value.storage.local:input+offset;
    const uint16_t* pb=alias?b.value.storage.local:input+offset;
    expected.value.capacity=7; expected.value.length=n;
    expected.value.storage.local[0]=0;
    if(n) {
        for(unsigned i=0;i<n;++i)expected.value.storage.local[i]=(alias && i==0)?0:input[offset+i];
        expected.value.storage.local[n]=0;
    }
    unsigned hc=helper_calls, cc=copy_calls;
    if(a.value.construct_terminated(pa)!=&a.value)return 1;
    if(helper_calls!=hc+(n!=0))return 2;
    if(n && (forwarded!=pa || forwarded_count!=n))return 3;
    if(original_wide_construct_terminated_register(&b.value,pb)!=&b.value)return 4;
    if(test_get_fs_head()!=fs_storage[0] || fs_failure)return 8;
    if(copy_calls!=cc+2*(n!=0))return 5;
    if(!equal(&a,&b,sizeof(a)) || !equal(&a,&expected,sizeof(a)))return 6;
    if(!equal(input,saved,sizeof(input)))return 7;
    return 0;
}
extern "C" int test_main() {
    static_assert(sizeof(WideString)==24,"x86 object size");
    static_assert(offsetof(WideString,length)==16,"length offset");
    static_assert(offsetof(WideString,capacity)==20,"capacity offset");
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0)return 30;
    if(test_get_fs_head()!=fs_storage[0])return 31;
    copy_iat=copy_bytes;
    for(unsigned n=0;n<=7;++n)for(unsigned pattern=0;pattern<3;++pattern) {
        for(unsigned offset=0;offset<4;++offset) {
            int e=run(n,pattern,offset,false);if(e)return e;
        }
        int e=run(n,pattern,0,true);if(e)return 10+e;
    }
    test_write("wide constructor checks passed\n",31);
    return 0;
}
