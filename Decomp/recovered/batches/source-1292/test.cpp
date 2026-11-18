#include "impl.hpp"
#include <stddef.h>
extern "C" NarrowString* __attribute__((thiscall)) original_worker_narrow_range_replace(NarrowString*,const char*,const char*,const char*,const char*);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_erase(NarrowString*,uint32_t,uint32_t);
extern "C" NarrowString* __attribute__((thiscall)) original_narrow_replace_range(NarrowString*,uint32_t,uint32_t,const char*,uint32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void* memcpy(void* d,const void* s,size_t n) { unsigned char* a=(unsigned char*)d;const unsigned char* b=(const unsigned char*)s;for(size_t i=0;i<n;i++)a[i]=b[i];return d; }
extern "C" void* memset(void* d,int v,size_t n) { unsigned char* a=(unsigned char*)d;for(size_t i=0;i<n;i++)a[i]=(unsigned char)v;return d; }
typedef void* (*Copy)(void*,const void*,size_t);
Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy;
NarrowString* RIFF_THISCALL NarrowString::erase(uint32_t p,uint32_t n) {return original_narrow_erase(this,p,n);}
NarrowString* RIFF_THISCALL NarrowString::replace(uint32_t p,uint32_t n,const char* s,uint32_t z) {return original_narrow_replace_range(this,p,n,s,z);}
struct Fixture { uint32_t guard1; NarrowString s; unsigned char heap[80]; uint32_t guard2; };
static void init(Fixture& f,bool heap,unsigned len) {memset(&f,0xa5,sizeof f);f.s.length=len;f.s.capacity=heap?63:15;if(heap)f.s.storage.heap=(char*)f.heap;char* p=heap?(char*)f.heap:f.s.storage.local;for(unsigned i=0;i<len;i++)p[i]=(char)('A'+i%26);p[len]=0;}
static bool eq(const void* a,const void* b,unsigned n) {const unsigned char* x=(const unsigned char*)a;const unsigned char* y=(const unsigned char*)b;for(unsigned i=0;i<n;i++)if(x[i]!=y[i])return false;return true;}
static int run(bool heap,unsigned len,unsigned pos,unsigned count,unsigned mode,unsigned head) {
 Fixture a,b;init(a,heap,len);init(b,heap,len);char* ap=heap?(char*)a.heap:a.s.storage.local;char* bp=heap?(char*)b.heap:b.s.storage.local;
 static const char source[]="0123456789abcdefghijklmnop";
 const char* af=mode==3?0:ap+pos;const char* bf=mode==3?0:bp+pos;
 const char* al=mode==3?0:ap+pos+count;const char* bl=mode==3?0:bp+pos+count;
 const char* sf=mode==0?0:source;const char* sl=mode==0?0:(mode==4?source:source+count);
 // Mode 2 exercises a null destination end, mode 3 both null.
 if(mode==2){al=0;bl=0;sl=source+1;}
 if(mode==3)sl=source+1;
 if(a.s.replace_range(af,al,sf,sl)!=&a.s || test_get_fs_head()!=head)return 1;
 if(original_worker_narrow_range_replace(&b.s,bf,bl,sf,sl)!=&b.s || test_get_fs_head()!=head)return 2;
 if(heap){if(a.s.storage.heap!=(char*)a.heap||b.s.storage.heap!=(char*)b.heap)return 3;a.s.storage.heap=0;b.s.storage.heap=0;}
 if(!eq(&a,&b,sizeof a))return 4;
 return 0;
}
extern "C" int test_main(){static_assert(sizeof(NarrowString)==24,"layout");static unsigned fs[16];fs[0]=0x12345678;if(test_install_fs(fs)!=0)return 10;unsigned head=fs[0];if(test_get_fs_head()!=head)return 11;
 for(unsigned h=0;h<2;h++)for(unsigned len=0;len<=12;len++)for(unsigned p=0;p<=len;p++){
  int e=run(h!=0,len,p,len-p,0,head);if(e)return 20+e;
  e=run(h!=0,len,p,len-p,4,head);if(e)return 25+e;
  for(unsigned n=1;n<=len-p;n++){e=run(h!=0,len,p,n,1,head);if(e)return 30+e;}
  if(len<12 && p==len){e=run(h!=0,len,p,0,2,head);if(e)return 40+e;}
 }
 for(unsigned h=0;h<2;h++){int e=run(h!=0,0,0,0,3,head);if(e)return 50+e;}
 return 0;}
