#include "impl.hpp"
extern "C" char** __attribute__((thiscall)) original_narrow_end_pointer(riff::NarrowString*, char**);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned fs_storage[8];
static char heap_bytes[80];
static void copy_bytes(void* to, const void* from, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(to);
    const unsigned char* s = static_cast<const unsigned char*>(from);
    for (unsigned i=0; i<n; ++i) d[i]=s[i];
}
static bool equal_bytes(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(unsigned cap, unsigned len, uintptr_t address, bool overlap) {
    riff::NarrowString value;
    for(unsigned i=0;i<16;++i) value.storage.inline_bytes[i]=static_cast<char>(0x40+i);
    if(cap>=16) value.storage.heap=reinterpret_cast<char*>(address);
    value.length=len; value.capacity=cap;
    unsigned char before[24], oracle_after[24];
    copy_bytes(before,&value,24);
    const uintptr_t base=cap<16 ? reinterpret_cast<uintptr_t>(&value.storage) : address;
    char* expected=reinterpret_cast<char*>(base+len);
    struct Slot { unsigned pre; char* result; unsigned post; } slot={0x12345678u,0,0x87654321u};
    char** output=overlap ? &value.storage.heap : &slot.result;
    if(original_narrow_end_pointer(&value,output)!=output) return 1;
    if(test_get_fs_head()!=fs_storage[0]) return 2;
    if(*output!=expected || slot.pre!=0x12345678u || slot.post!=0x87654321u) return 3;
    copy_bytes(oracle_after,&value,24);
    if(!overlap && !equal_bytes(before,&value,24)) return 4;
    if(overlap && !equal_bytes(before+4,reinterpret_cast<unsigned char*>(&value)+4,20)) return 5;
    copy_bytes(&value,before,24); slot.result=0;
    if(value.end_pointer(output)!=output || *output!=expected) return 6;
    if(!equal_bytes(oracle_after,&value,24)) return 7;
    if(slot.pre!=0x12345678u || slot.post!=0x87654321u) return 8;
    return 0;
}
extern "C" int test_main() {
    fs_storage[0]=0x13579bdfu;
    if(test_install_fs(fs_storage)!=0) return 90;
    const unsigned caps[]={0,1,15,16,17,80,0x80000000u,0xffffffffu};
    const unsigned lengths[]={0,1,15,16,79,0x7fffffffu,0xffffffffu};
    const uintptr_t addresses[]={reinterpret_cast<uintptr_t>(heap_bytes),0,1,0xfffffff0u};
    for(unsigned c=0;c<8;++c)
        for(unsigned l=0;l<7;++l)
            for(unsigned a=0;a<4;++a)
                for(unsigned overlap=0;overlap<2;++overlap) {
                    int r=check(caps[c],lengths[l],addresses[a],overlap!=0);
                    if(r) return r;
                }
    for(unsigned i=0;i<80;++i) if(heap_bytes[i]!=0) return 9;
    return 0;
}
