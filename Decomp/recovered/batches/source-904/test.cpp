#include "impl.hpp"
#include <stddef.h>
using namespace riff;
// ECX/EDX, no stack arguments: fastcall has exactly the original ABI here.
extern "C" void __attribute__((fastcall)) original_script_prototype_dispose(State*, Prototype*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static_assert(sizeof(Prototype)==76,"prototype layout");
static_assert(offsetof(Prototype,local_count)==0x38,"prototype counts");
static_assert(offsetof(Global,allocated_bytes)==0x44,"accounting layout");
static_assert(offsetof(State,global)==0x10,"state layout");
struct Call { void* block; uint32_t old_size, new_size, owner, before; };
struct Fixture {
 State state;
 Global globals[2];
 Prototype proto;
 uint8_t buffers[6][24];
 Call calls[7];
 uint32_t count, bad, mode, result;
};
static Fixture f;
static uint8_t expected[sizeof f];
static uint32_t fsStorage[32];
static const unsigned ptrOffsets[6]={12,16,8,20,24,28};
static const unsigned countOffsets[6]={44,52,40,48,56,36};
static const uint32_t factors[6]={4,4,8,4,12,4};
static uint32_t& word(unsigned offset) {
 return *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(&f.proto)+offset);
}
extern "C" void* observe(void* user, void* block, uint32_t oldSize, uint32_t newSize) {
 unsigned owner=static_cast<unsigned>(reinterpret_cast<uintptr_t>(user));
 unsigned i=f.count++;
 if(i>=7){f.bad=1;return 0;}
 Call& c=f.calls[i];
 c.block=block;c.old_size=oldSize;c.new_size=newSize;c.owner=owner;
 c.before=f.globals[owner].allocated_bytes;
 if(newSize || block!=(i==6?static_cast<void*>(&f.proto):reinterpret_cast<void*>(word(ptrOffsets[i]))) ||
    oldSize!=(i==6?76:word(countOffsets[i])*factors[i])) f.bad=1;
 // Challenge temporal loads: later fields and the state owner can change.
 // Also mutate captured-owner accounting, which must be decremented afterward.
 if(f.mode && i<6){
   word(countOffsets[i+1==6?0:i+1]) ^= 0x80000003u;
   if(i<5)word(ptrOffsets[i+1])=reinterpret_cast<uintptr_t>(&f.buffers[5-i][3]);
   f.state.global=&f.globals[1-owner];
   f.globals[owner].allocated_bytes += 0x12345678u;
 }
 return f.result?static_cast<void*>(&f.buffers[0][0]):0;
}
static void init(unsigned seed,unsigned mode,unsigned result) {
 uint8_t* b=reinterpret_cast<uint8_t*>(&f);
 for(unsigned i=0;i<sizeof f;++i)b[i]=static_cast<uint8_t>(i*37+seed);
 f.state.global=&f.globals[0];
 for(unsigned j=0;j<2;++j){
   f.globals[j].allocator=observe;
   f.globals[j].allocator_user=reinterpret_cast<void*>(j);
   f.globals[j].allocated_bytes=seed?0x12345678u*seed:0;
 }
 f.count=f.bad=0;f.mode=mode;f.result=result;
 for(unsigned i=0;i<sizeof f.calls;++i)reinterpret_cast<uint8_t*>(f.calls)[i]=0;
 const uint32_t sizes[]={0,1,7,0x1fffffffu,0x40000000u,0x80000001u,0xffffffffu};
 for(unsigned i=0;i<6;++i){
   word(ptrOffsets[i])=((seed+i)%3==0)?0:reinterpret_cast<uintptr_t>(&f.buffers[i][0]);
   word(countOffsets[i])=sizes[(seed+i)%7];
 }
}
extern "C" int test_main() {
 fsStorage[0]=0xffffffffu;
 if(test_install_fs(fsStorage)!=0)return 1;
 for(unsigned seed=0;seed<28;++seed)for(unsigned mode=0;mode<2;++mode)for(unsigned result=0;result<2;++result){
   init(seed,mode,result);
   original_script_prototype_dispose(&f.state,&f.proto);
   if(test_get_fs_head()!=fsStorage[0])return 2;
   if(f.bad || f.count!=7)return 3;
   for(unsigned i=0;i<sizeof f;++i)expected[i]=reinterpret_cast<uint8_t*>(&f)[i];
   init(seed,mode,result);
   f.state.dispose_prototype(&f.proto);
   if(f.bad || f.count!=7)return 4;
   for(unsigned i=0;i<sizeof f;++i)if(expected[i]!=reinterpret_cast<uint8_t*>(&f)[i])return 5;
 }
 // Independent check: zero lengths and null arrays must still produce calls;
 // no prototype bytes or data buffers may be cleared by the destructor.
 init(0,0,0);
 for(unsigned i=0;i<6;++i){word(ptrOffsets[i])=0;word(countOffsets[i])=0;}
 uint8_t saved[sizeof(Prototype)];
 for(unsigned i=0;i<sizeof saved;++i)saved[i]=reinterpret_cast<uint8_t*>(&f.proto)[i];
 f.state.dispose_prototype(&f.proto);
 if(f.count!=7 || f.globals[0].allocated_bytes!=uint32_t(0)-76)return 6;
 for(unsigned i=0;i<6;++i)if(f.calls[i].block || f.calls[i].old_size || f.calls[i].new_size)return 7;
 for(unsigned i=0;i<sizeof saved;++i)if(saved[i]!=reinterpret_cast<uint8_t*>(&f.proto)[i])return 8;
 test_write("prototype disposal: 112 differential cases passed\n", sizeof("prototype disposal: 112 differential cases passed\n")-1);
 return 0;
}
