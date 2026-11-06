#include "impl.hpp"
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_substring_construct(
    const NarrowString*, NarrowString*, uint32_t, uint32_t);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_assign_substring(
    NarrowString*, const NarrowString*, uint32_t, uint32_t);
// Test adapter binds the sole unrecovered member dependency to accepted code.
NarrowString* RIFF_THISCALL NarrowString::assign_substring(
    const NarrowString* source, uint32_t offset, uint32_t count) {
    return original_narrow_assign_substring(this, source, offset, count);
}
extern "C" void test_write(const char*, unsigned);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    char* dst=static_cast<char*>(d); const char* src=static_cast<const char*>(s);
    for(unsigned i=0;i<n;++i) dst[i]=src[i];
    return d;
}
typedef void* (*Copy)(void*,const void*,unsigned);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy;
static void fill(void* p,unsigned n,unsigned char c) {
    unsigned char* b=static_cast<unsigned char*>(p);
    for(unsigned i=0;i<n;++i)b[i]=c;
}
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i)if(x[i]!=y[i])return false;
    return true;
}
struct Guarded { uint32_t before; NarrowString value; uint32_t after; };
static int run(bool alias,bool heap,unsigned length,unsigned offset,unsigned count) {
    Guarded a,b; fill(&a,sizeof(a),0xa5); fill(&b,sizeof(b),0xa5);
    NarrowString src; fill(&src,sizeof(src),0x6d);
    unsigned char backing[80];
    for(unsigned i=0;i<80;++i)backing[i]=static_cast<unsigned char>(i*53+7);
    // Embedded zero and high-bit bytes ensure copying is counted, not strlen.
    backing[3]=0;
    if(heap)src.storage.heap=reinterpret_cast<char*>(backing+4);
    else for(unsigned i=0;i<16;++i)src.storage.local[i]=static_cast<char>(backing[i]);
    src.length=length; src.capacity=heap?63:15;
    if(alias){a.value=src;b.value=src;}
    Guarded expected=a;
    expected.value.capacity=15; expected.value.length=0; expected.value.storage.local[0]=0;
    unsigned selected=alias?0:length-offset;
    if(count<selected)selected=count;
    const char* data=heap?src.storage.heap:src.storage.local;
    for(unsigned i=0;i<selected;++i)expected.value.storage.local[i]=data[offset+i];
    expected.value.length=selected; expected.value.storage.local[selected]=0;
    NarrowString saved=src; unsigned char saved_backing[80];
    memcpy(saved_backing,backing,80);
    unsigned head=test_get_fs_head();
    NarrowString* ra=original_narrow_substring_construct(alias?&a.value:&src,&a.value,offset,count);
    if(test_get_fs_head()!=head)return 1;
    NarrowString* rb=(alias?&b.value:&src)->construct_substring(&b.value,offset,count);
    if(test_get_fs_head()!=head)return 2;
    if(ra!=&a.value || rb!=&b.value)return 3;
    if(!same(&a,&b,sizeof(a)) || !same(&a,&expected,sizeof(a)))return 4;
    if(!same(&src,&saved,sizeof(src)) || !same(backing,saved_backing,80))return 5;
    return 0;
}
extern "C" int test_main() {
    uint32_t fs_storage[16]={0xffffffffU};
    if(test_install_fs(fs_storage)!=0)return 90;
    copy_import=memcpy;
    const unsigned counts[]={0,1,2,7,14,15,16,31,0x7fffffffU,0xffffffffU};
    for(unsigned heap=0;heap<2;++heap) {
        for(unsigned length=0;length<=(heap?63U:15U);++length) {
            for(unsigned offset=0;offset<=length;++offset) {
                for(unsigned j=0;j<sizeof(counts)/sizeof(counts[0]);++j) {
                    unsigned n=length-offset;if(counts[j]<n)n=counts[j];
                    // Growth and exception runtime are outside this wrapper recovery.
                    if(n>15)continue;
                    int e=run(false,heap!=0,length,offset,counts[j]);if(e)return 10+e;
                }
            }
            for(unsigned j=0;j<sizeof(counts)/sizeof(counts[0]);++j) {
                int e=run(true,heap!=0,length,0,counts[j]);if(e)return 20+e;
            }
        }
    }
    test_write("narrow substring tests passed\n",30);
    return 0;
}
