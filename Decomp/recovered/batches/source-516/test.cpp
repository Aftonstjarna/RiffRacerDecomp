#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_owner_slot214_assign(riff::Owner*, riff::SharedObject*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(void*) == 4, "oracle is i386");
static_assert(sizeof(riff::Owner) == 0x218, "owner layout");
struct Storage { uint32_t word[64]; };
static riff::Owner owner;
static Storage oldStorage, newStorage;
static int32_t oldTable[2], newTable[2];
static riff::SharedObject *oldObject, *newObject;
static unsigned calls, failed, callbackMode;
static uint32_t* oldCount;
static void* expectedBase;
static void* __attribute__((thiscall)) destroy(void* self, unsigned flags) {
    ++calls;
    if (self != expectedBase || flags != 1 || owner.slot214 != oldObject || *oldCount != 0) failed = 1;
    if (callbackMode) {
        // Demonstrate that acquisition resolves the incoming vbtable after release.
        newTable[1] = 44;
        newStorage.word[33] = 77; // incoming+52 count
    }
    return self;
}
typedef void* (__attribute__((thiscall)) *Dtor)(void*, unsigned);
static Dtor vtable[1] = { destroy };
static uint32_t ptr(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static void initialize(int oldOffset, int newOffset, uint32_t a, uint32_t b) {
    for (unsigned i=0;i<sizeof(owner.unknown);++i) owner.unknown[i]=static_cast<unsigned char>(i*37+9);
    for (unsigned i=0;i<64;++i) { oldStorage.word[i]=0xa1b20000u+i; newStorage.word[i]=0xc3d40000u+i; }
    oldObject=reinterpret_cast<riff::SharedObject*>(&oldStorage.word[20]);
    newObject=reinterpret_cast<riff::SharedObject*>(&newStorage.word[20]);
    oldTable[0]=-777; oldTable[1]=oldOffset;
    newTable[0]=888; newTable[1]=newOffset;
    oldStorage.word[21]=ptr(oldTable); newStorage.word[21]=ptr(newTable);
    unsigned oi=21+oldOffset/4, ni=21+newOffset/4;
    oldStorage.word[oi]=ptr(vtable); oldStorage.word[oi+1]=a;
    newStorage.word[ni]=ptr(vtable); newStorage.word[ni+1]=b;
    expectedBase=&oldStorage.word[oi]; oldCount=&oldStorage.word[oi+1];
    calls=failed=0;
}
struct Snapshot { riff::Owner owner; Storage oldData, newData; int32_t nt[2]; unsigned calls, failed; };
static Snapshot run(bool oracle, unsigned mode, int ao, int bo, uint32_t a, uint32_t b, unsigned cb) {
    initialize(ao,bo,a,b); callbackMode=cb;
    owner.slot214=(mode==0 || mode==1)?0:oldObject;
    riff::SharedObject* incoming=(mode==0 || mode==2)?0:(mode==3?oldObject:newObject);
    if (oracle) original_owner_slot214_assign(&owner,incoming); else owner.assign(incoming);
    if (test_get_fs_head()!=0x12345678u) failed=1;
    if (owner.slot214!=incoming) failed=1;
    for(unsigned i=0;i<sizeof(owner.unknown);++i) if(owner.unknown[i]!=static_cast<unsigned char>(i*37+9)) failed=1;
    unsigned expectedCalls=(mode>=2 && mode!=3 && a==1)?1:0;
    if(calls!=expectedCalls) failed=1;
    Snapshot result={owner,oldStorage,newStorage,{newTable[0],newTable[1]},calls,failed};
    return result;
}
static bool equal(const Snapshot& a,const Snapshot& b) {
    const unsigned char* x=reinterpret_cast<const unsigned char*>(&a);
    const unsigned char* y=reinterpret_cast<const unsigned char*>(&b);
    for(unsigned i=0;i<sizeof(a);++i) if(x[i]!=y[i]) return false;
    return !a.failed && !b.failed;
}
extern "C" int test_main() {
    unsigned fs[8]={0x12345678u};
    if(test_install_fs(fs)!=0) return 1;
    const uint32_t counts[]={0,1,2,0x7fffffffu,0x80000000u,0xffffffffu};
    const int offsets[]={-48,12,76};
    for(unsigned m=0;m<5;++m) for(unsigned i=0;i<6;++i) for(unsigned j=0;j<6;++j)
        for(unsigned k=0;k<3;++k) for(unsigned l=0;l<3;++l) {
            Snapshot a=run(true,m,offsets[k],offsets[l],counts[i],counts[j],0);
            Snapshot b=run(false,m,offsets[k],offsets[l],counts[i],counts[j],0);
            if(!equal(a,b)) return 2;
        }
    Snapshot a=run(true,4,12,12,1,9,1);
    Snapshot b=run(false,4,12,12,1,9,1);
    if(!equal(a,b) || a.newData.word[33]!=78) return 3;
    test_write("owner-slot214-assign: passed\n",28);
    return 0;
}
extern "C" void* memcpy(void* dst, const void* src, unsigned n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    const unsigned char* s=static_cast<const unsigned char*>(src);
    for(unsigned i=0;i<n;++i) d[i]=s[i];
    return dst;
}
