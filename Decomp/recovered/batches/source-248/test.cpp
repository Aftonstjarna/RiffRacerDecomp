#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_narrow_string_reset(NarrowString*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (unsigned i=0;i<n;++i) a[i]=b[i];
    return d;
}
extern "C" void* memset(void* d, int c, unsigned n) {
    unsigned char* a=static_cast<unsigned char*>(d);
    for(unsigned i=0;i<n;++i) a[i]=static_cast<unsigned char>(c);
    return d;
}
typedef void (*DeleteCallback)(void*);
typedef void* (*CopyCallback)(void*,const void*,unsigned);
DeleteCallback delete_import __attribute__((section(".oracle_delete"),used,aligned(4)));
CopyCallback copy_import __attribute__((section(".test_iat"),used,aligned(4)));
unsigned cookie __attribute__((section(".oracle_cookie"),used,aligned(4)))=0x71c35249;
struct Guarded { unsigned before[4]; NarrowString value; unsigned after[4]; };
static Guarded oracle, recovered;
static unsigned char heap_data[64], saved_heap[64];
static NarrowString* current;
static unsigned deletes, failures, copies;
static void* deleted;
static bool from_original;
static unsigned fs_storage[4];
static void check(bool ok) { if(!ok) ++failures; }
extern "C" void RIFF_CDECL recovered_narrow_delete(void* p) {
    ++deletes; deleted=p;
    // Reset is committed before the external deallocator observes it.
    check(current->length==0 && current->capacity==15);
    check(current->storage.inline_bytes[0]==0);
    // The original registers its exception frame throughout the import call.
    if(from_original) check(test_get_fs_head()!=0x13579bdf);
}
static void* copy_callback(void* d,const void* s,unsigned n) {
    ++copies; check(n==1); check(*static_cast<const unsigned char*>(s)==0);
    return memcpy(d,s,n);
}
static void prepare(Guarded& g,unsigned cap,unsigned len,unsigned seed,bool null_heap) {
    for(unsigned i=0;i<4;++i) { g.before[i]=0x12345600+seed+i; g.after[i]=0xabcdef00+seed+i; }
    for(unsigned i=0;i<16;++i) g.value.storage.inline_bytes[i]=static_cast<unsigned char>(seed+i*13);
    if(cap>=16) g.value.storage.heap=null_heap ? 0 : reinterpret_cast<char*>(heap_data);
    else if(len<16) g.value.storage.inline_bytes[len]=0;
    g.value.length=len; g.value.capacity=cap;
}
static void run(unsigned cap,unsigned len,unsigned seed,bool null_heap) {
    prepare(oracle,cap,len,seed,null_heap); prepare(recovered,cap,len,seed,null_heap);
    unsigned char old_storage[16]; memcpy(old_storage,oracle.value.storage.inline_bytes,16);
    for(unsigned i=0;i<64;++i) saved_heap[i]=heap_data[i]=static_cast<unsigned char>(i+seed);
    current=&oracle.value; deletes=copies=0; deleted=0; from_original=true;
    original_narrow_string_reset(current);
    check(test_get_fs_head()==0x13579bdf);
    check(deletes==(cap>=16 ? 1u:0u)); check(copies==(cap>=16 ? 1u:0u));
    if(cap>=16) check(deleted==(null_heap ? 0 : heap_data));
    current=&recovered.value; deletes=0; deleted=0; from_original=false;
    current->reset();
    check(deletes==(cap>=16 ? 1u:0u));
    if(cap>=16) check(deleted==(null_heap ? 0 : heap_data));
    check(oracle.value.length==0 && recovered.value.length==oracle.value.length);
    check(oracle.value.capacity==15 && recovered.value.capacity==oracle.value.capacity);
    check(oracle.value.storage.inline_bytes[0]==0 && recovered.value.storage.inline_bytes[0]==0);
    if(cap>=16) for(unsigned i=1;i<16;++i) {
        check(oracle.value.storage.inline_bytes[i]==old_storage[i]);
        check(recovered.value.storage.inline_bytes[i]==old_storage[i]);
    }
    for(unsigned i=0;i<4;++i) {
        check(oracle.before[i]==0x12345600+seed+i && recovered.before[i]==oracle.before[i]);
        check(oracle.after[i]==0xabcdef00+seed+i && recovered.after[i]==oracle.after[i]);
    }
    for(unsigned i=0;i<64;++i) check(heap_data[i]==saved_heap[i]);
    // A second reset is inline and must not delete the old allocation twice.
    current=&oracle.value; deletes=copies=0; from_original=true;
    original_narrow_string_reset(current);
    check(test_get_fs_head()==0x13579bdf); check(deletes==0 && copies==0);
    current=&recovered.value; from_original=false; current->reset(); check(deletes==0);
    check(current->length==oracle.value.length && current->capacity==oracle.value.capacity);
    check(oracle.value.storage.inline_bytes[0]==0 && current->storage.inline_bytes[0]==0);
    for(unsigned i=0;i<4;++i) {
        check(oracle.before[i]==0x12345600+seed+i && recovered.before[i]==oracle.before[i]);
        check(oracle.after[i]==0xabcdef00+seed+i && recovered.after[i]==oracle.after[i]);
    }
    for(unsigned i=0;i<64;++i) check(heap_data[i]==saved_heap[i]);
}
extern "C" int test_main() {
    static_assert(sizeof(void*)==4,"oracle requires i386");
    static_assert(offsetof(NarrowString,length)==16,"length offset");
    static_assert(offsetof(NarrowString,capacity)==20,"capacity offset");
    fs_storage[0]=0x13579bdf;
    if(test_install_fs(fs_storage)!=0) { test_write("FS setup failed\n",16); return 1; }
    check(test_get_fs_head()==0x13579bdf);
    delete_import=recovered_narrow_delete; copy_import=copy_callback;
    const unsigned caps[]={0,1,14,15,16,17,31,255,0x7fffffff,0x80000000,0xffffffff};
    const unsigned lens[]={0,1,7,15,16,0xffffffff};
    for(unsigned c=0;c<sizeof(caps)/sizeof(caps[0]);++c)
        for(unsigned l=0;l<sizeof(lens)/sizeof(lens[0]);++l) {
            // Inline length is not used by reset. Also probe inconsistent metadata.
            run(caps[c],lens[l],c*23+l*7,false);
            if(caps[c]>=16) run(caps[c],lens[l],c*19+l*11,true);
        }
    if(failures) { test_write("reset differential FAILED\n",26); return 1; }
    const char message[]="reset differential passed: 108 cases, 216 original calls\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
