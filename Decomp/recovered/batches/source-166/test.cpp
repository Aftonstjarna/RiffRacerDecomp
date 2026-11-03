#include "impl.hpp"
using namespace riff;
extern "C" void __attribute__((thiscall)) original_secondary_window(Window*,uint32_t,uint32_t,uint32_t);
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void*d,const void*s,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=((const uint8_t*)s)[i];return d;}
extern "C" void* memset(void*d,int v,size_t n){for(size_t i=0;i<n;++i)((uint8_t*)d)[i]=(uint8_t)v;return d;}
static bool eq(const void*a,const void*b,unsigned n){for(unsigned i=0;i<n;++i)if(((const uint8_t*)a)[i]!=((const uint8_t*)b)[i])return false;return true;}
static Window* active;
static uint32_t trace[160],count,errors,variant,createResult;
static Rect parent,output;
static void event(uint32_t x){if(count<160)trace[count++]=x;else ++errors;}
static int32_t SW_STDCALL destroy(uint32_t h){event(1);event(h);event(active->secondary);return 0;}
static int32_t SW_STDCALL adjust(Rect*r,uint32_t s,int32_t menu){event(2);event(s);event(menu);event(r->left);event(r->top);event(r->right);event(r->bottom);*r=output;return variant&1?0:1;}
static int32_t SW_STDCALL rect(uint32_t h,Rect*r){event(3);event(h);*r=parent;return variant&1?0:1;}
static bool wide(const uint16_t*p,const char*s){while(*s){if(*p++!=(uint8_t)*s++)return false;}return !*p;}
static uint32_t SW_STDCALL create(uint32_t ex,const uint16_t*c,const uint16_t*t,uint32_t s,uint32_t x,uint32_t y,uint32_t w,uint32_t h,uint32_t owner,uint32_t menu,uint32_t inst,void*p){
 event(4);event(ex);event(s);event(x);event(y);event(w);event(h);event(owner);event(menu);event(inst);
 event(active->horizontalOffset);event(active->verticalOffset);event(active->secondary);
 if(p!=active||!((uintptr_t)c==0x9fbd8c||wide(c,"Octane5WindowClass"))||!((uintptr_t)t==0x9fbd68||wide(t,"Second screen lol")))++errors;
 return createResult;
}
static int32_t SW_STDCALL position(uint32_t h,uint32_t z,uint32_t x,uint32_t y,uint32_t w,uint32_t ht,uint32_t f){event(6);event(h);event(z);event(x);event(y);event(w);event(ht);event(f);return 0;}
static int32_t SW_STDCALL show(uint32_t h,int32_t n){event(7);event(h);event(n);return 0;}
static int32_t SW_STDCALL style(uint32_t h,int32_t n,uint32_t s){event(8);event(h);event(n);event(s);return 0;}
// Explicit boundary double for the out-of-scope frame helper. Reentrant field
// changes verify reloads after the call; this is ordinary C++ code, not a thunk.
extern "C" void __attribute__((thiscall,section(".frame_boundary"),noinline)) frame(Window*w){event(5);event(w->secondary);if(variant&2){w->verticalOffset+=17;w->horizontalOffset-=9;w->secondary^=0x1234;}}
uint32_t iat[0x600/4] __attribute__((section(".oracle_iat"),aligned(4)))={0};
uint32_t cookie __attribute__((section(".oracle_cookie"),aligned(4)))=0x19876543;
struct Guarded { uint32_t pre[8];Window w;uint32_t post[8]; };
static void reset(Window*w){active=w;count=errors=0;for(unsigned i=0;i<160;++i)trace[i]=0;}
extern "C" int test_main(){
 WindowApi api={destroy,adjust,rect,create,position,show,style,frame};
 bool mapped=(uintptr_t)iat==0x92d000 && (uintptr_t)&cookie==0xbaabc0 && (uintptr_t)&frame==0x48cab0;
 if(mapped){
 #define BIND(off,member) *reinterpret_cast<decltype(api.member)*>((uint8_t*)iat+off)=api.member
 BIND(0x530,destroy);BIND(0x580,adjust);BIND(0x524,rect);BIND(0x578,create);BIND(0x56c,position);BIND(0x574,show);BIND(0x5ac,style);
 #undef BIND
 }
 const uint32_t edges[]={0,1,2,3,720,1920,0x7fffffff,0x80000000,0x80000001,0xfffffffe,0xffffffff};
 unsigned cases=0;
 for(unsigned wi=0;wi<11;++wi)for(unsigned hi=0;hi<11;++hi)for(unsigned mode=0;mode<4;++mode)for(unsigned exists=0;exists<2;++exists)for(variant=0;variant<4;++variant)for(unsigned success=0;success<2;++success){
 uint32_t w=edges[wi],h=edges[hi];uint8_t popup=mode==0?0:mode==1?1:mode==2?2:255;
 parent.left=edges[(wi+2)%11];parent.right=edges[(hi+3)%11];parent.top=edges[(wi+5)%11];parent.bottom=edges[(hi+7)%11];
 output.left=edges[(hi+1)%11];output.top=edges[(wi+4)%11];output.right=w+7;output.bottom=h+13;
 createResult=success?0x56781234:0;
 Guarded a,b,initial;for(unsigned i=0;i<sizeof(a);++i)((uint8_t*)&a)[i]=(uint8_t)(i*37+cases);
 a.w.secondary=exists?0x98765432:0; initial=a;b=a;
 reset(&a.w);a.w.secondaryWithApi(w,h,popup,api);
 uint32_t saved[160];memcpy(saved,trace,sizeof(trace));unsigned savedCount=count;
 if(errors)return 1;
 // Independent footprint check, including guard words and unknown fields.
 Guarded expected=initial;expected.w.secondary=a.w.secondary;
 if(!exists && !((!w||!h)&&initial.w.secondary)){expected.w.horizontalOffset=a.w.horizontalOffset;expected.w.verticalOffset=a.w.verticalOffset;}
 if(!eq(&a,&expected,sizeof(a)))return 2;
 if((!w||!h)&&exists){if(count!=3||trace[0]!=1||a.w.secondary)return 3;}
 if(mapped){reset(&b.w);original_secondary_window(&b.w,w,h,popup);if(errors||count!=savedCount||!eq(saved,trace,sizeof(trace))||!eq(&a,&b,sizeof(a)))return 4;
 b=initial;reset(&b.w);b.w.secondaryWindow(w,h,popup);if(errors||count!=savedCount||!eq(saved,trace,sizeof(trace))||!eq(&a,&b,sizeof(a)))return 5;}
 ++cases;
 }
 if(mapped)test_write("PASS: 15488 direct oracle and ABI-wrapper comparisons\n",sizeof("PASS: 15488 direct oracle and ABI-wrapper comparisons\n")-1);
 else test_write("PASS: portable checks only; fixed oracle mappings required\n",sizeof("PASS: portable checks only; fixed oracle mappings required\n")-1);
 return 0;
}
