#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((fastcall)) original_script_gc_visit_thread(Collector*,Thread*);
extern "C" void __attribute__((fastcall)) original_script_stack_relocate_pointers(Thread*,uint32_t);
static uint32_t addr(const void* p){return (uint32_t)(uintptr_t)p;}
static unsigned char global_data[128], collector[128], objects[4][16], saved_objects[4][16], saved_collector[128];
static uint32_t fs_storage[32];
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void __attribute__((fastcall)) original_script_gc_mark_object(void*,uint32_t);
static uint32_t values[256], frames[24*24/4];
static Thread thread_state;
static unsigned calls, old_sizes[4], new_sizes[4], mark_calls;
static void* allocate(void*, void* p, uint32_t oldn, uint32_t newn){ old_sizes[calls]=oldn;new_sizes[calls]=newn;++calls; return p; }
static void mark(void* g,uint32_t p){++mark_calls;original_script_gc_mark_object(g,p);}
static uint32_t resize(Thread*,uint32_t p,uint32_t a,uint32_t b){old_sizes[calls]=a;new_sizes[calls]=b;++calls;return p;}
static uint32_t too_large(Thread*){return 0;}
static void relocate(Thread* t,uint32_t old){original_script_stack_relocate_pointers(t,old);}
namespace riff { const Services services={mark,resize,too_large,relocate}; }
static void fill(void* p,unsigned n,unsigned char c){unsigned char* b=(unsigned char*)p;while(n--)*b++=c;}
static bool equal(const void* a,const void* b,unsigned n){const unsigned char *x=(const unsigned char*)a,*y=(const unsigned char*)b;while(n--)if(*x++!=*y++)return false;return true;}
static Thread saved_thread; static uint32_t saved_values[256],saved_frames[144]; static unsigned char saved_global[128];
static void copy(void* a,const void* b,unsigned n){unsigned char* x=(unsigned char*)a;const unsigned char* y=(const unsigned char*)b;while(n--)*x++=*y++;}
static int run(int fc,int sc,int active,int last,int framecount){
 fill(objects,sizeof objects,0); for(int i=0;i<4;i++){objects[i][4]=0;objects[i][5]=(unsigned char)(i+1);}
 fill(&thread_state,sizeof thread_state,0);fill(global_data,sizeof global_data,0);fill(collector,sizeof collector,0x35);fill(values,sizeof values,0x72);fill(frames,sizeof frames,0x51);
 *(uint32_t*)(global_data+12)=addr((void*)allocate); *(uint32_t*)(global_data+16)=0; *(uint32_t*)(global_data+68)=10000;
 thread_state.global=addr(global_data);thread_state.stack=addr(values);thread_state.top=addr(values+active*2);thread_state.base=addr(values+2);
 thread_state.first_frame=addr(frames);thread_state.current_frame=addr(frames+framecount*6);thread_state.stack_capacity=sc;thread_state.frame_capacity=fc;
 thread_state.stack_limit=addr(values+(sc>100?200:sc)*2);thread_state.frame_limit=addr(frames+120);
 for(int i=0;i<=framecount;i++){frames[i*6]=addr(values+2);frames[i*6+1]=addr(values+4);frames[i*6+2]=addr(values+last*2);}
 for(int i=0;i<active;i++){values[i*2]=addr(objects[i%4]);values[i*2+1]=(i%3==0)?4:i%4;}
 thread_state.special_value=addr(objects[3]);thread_state.special_tag=(active==4)?4:3;
 Thread initial=thread_state; uint32_t iv[256],ifrm[144]; unsigned char ig[128];copy(iv,values,sizeof values);copy(ifrm,frames,sizeof frames);copy(ig,global_data,sizeof global_data);
 calls=mark_calls=0;original_script_gc_visit_thread((Collector*)collector,&thread_state);if(test_get_fs_head()!=fs_storage[0])return 4; unsigned expected_calls=calls;unsigned eo[4],en[4];copy(eo,old_sizes,sizeof eo);copy(en,new_sizes,sizeof en);
 saved_thread=thread_state;copy(saved_objects,objects,sizeof objects);copy(saved_collector,collector,sizeof collector);copy(saved_values,values,sizeof values);copy(saved_frames,frames,sizeof frames);copy(saved_global,global_data,sizeof global_data);
 thread_state=initial;fill(collector,sizeof collector,0x35);fill(objects,sizeof objects,0); for(int i=0;i<4;i++){objects[i][4]=0;objects[i][5]=(unsigned char)(i+1);}copy(values,iv,sizeof values);copy(frames,ifrm,sizeof frames);copy(global_data,ig,sizeof global_data);calls=mark_calls=0;
 ((Collector*)collector)->visit(&thread_state);
 // The real allocator updates accounting; the test service mirrors it below.
 for(unsigned i=0;i<calls;i++) *(uint32_t*)(global_data+68)+=new_sizes[i]-old_sizes[i];
 if(calls!=expected_calls||test_get_fs_head()!=fs_storage[0])return 1;
 for(unsigned i=0;i<calls;i++)if(eo[i]!=old_sizes[i]||en[i]!=new_sizes[i])return 2;
 if(!equal(objects,saved_objects,sizeof objects)||!equal(collector,saved_collector,sizeof collector))return 5;
 if(!equal(&thread_state,&saved_thread,sizeof thread_state)||!equal(values,saved_values,sizeof values)||!equal(frames,saved_frames,sizeof frames)||!equal(global_data,saved_global,sizeof global_data))return 3;
 return 0;
}
extern "C" int test_main(){
 fs_storage[0]=0x12345678; if(test_install_fs(fs_storage)!=0)return 10;
 const int fcs[]={16,17,32,20000,20001};const int scs[]={90,91,128};
 for(unsigned i=0;i<5;i++)for(unsigned j=0;j<3;j++)for(int k=0;k<3;k++){int r=run(fcs[i],scs[j],k*2,7+k,k);if(r)return r;}
 return 0;
}
