#include "impl.hpp"
#include <stddef.h>
extern "C" void __attribute__((thiscall)) original_text_colour_forward(TextItem*, const float*);
extern "C" void __attribute__((thiscall)) original_ui_item_set_colour(TextItem*, const float*);
extern "C" void __attribute__((thiscall)) original_visual_colour_set(Visual*, const float*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// These adapters link the separately recovered operations to their accepted references.
void TextItem::set_base_colour(const float* p) { original_ui_item_set_colour(this, p); }
void Visual::set_colour(const float* p) { original_visual_colour_set(this, p); }
static unsigned fs[64];
static void fill(void* p, unsigned n, unsigned seed) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i) b[i]=(unsigned char)(i*37+seed); }
static bool equal(const void* p,const void* q,unsigned n) { const unsigned char* a=(const unsigned char*)p; const unsigned char* b=(const unsigned char*)q; for(unsigned i=0;i<n;++i) if(a[i]!=b[i]) return false; return true; }
union Bits { uint32_t u; float f; };
static float value(uint32_t u) { Bits b; b.u=u; return b.f; }
static bool run(uint32_t kind, bool same_colour, bool nan, bool null_visual) {
    TextItem a,b; Visual av,bv; fill(&a,sizeof a,11); fill(&av,sizeof av,17);
    a.kind=kind; a.entries_begin=0; a.entries_end=0; a.visual=null_visual ? 0 : &av;
    const uint32_t words[4]={0x3f800000,0x80000000,0x40400000,0xff800000};
    float input[4]; for(unsigned i=0;i<4;++i) input[i]=value(words[i]);
    if(nan) input[2]=value(0x7fc12345);
    float* ac=(float*)((unsigned char*)&av+0x90);
    for(unsigned i=0;i<4;++i) ac[i]=same_colour?input[i]:value(0x40000000);
    *(uint32_t*)((unsigned char*)&av+0x170)=0x40000002;
    b=a; bv=av; b.visual=null_visual ? 0 : &bv;
    float saved[4]; for(unsigned i=0;i<4;++i) saved[i]=input[i];
    unsigned head=test_get_fs_head(); original_text_colour_forward(&a,input);
    if(test_get_fs_head()!=head) return false;
    b.set_colour(input); if(test_get_fs_head()!=head) return false;
    a.visual=b.visual;
    if(!equal(&a,&b,sizeof a)||!equal(&av,&bv,sizeof av)||!equal(input,saved,sizeof input)) return false;
    if(!equal(a.colour,input,sizeof input)) return false;
    uint32_t expected=0x40000002 | ((kind!=3 && (!same_colour || nan))?0x100:0);
    if(*(uint32_t*)((unsigned char*)&av+0x170)!=expected) return false;
    return true;
}
extern "C" int test_main() {
    if(offsetof(TextItem,kind)!=0x10||offsetof(TextItem,colour)!=0x54||offsetof(TextItem,entries_begin)!=0x184||offsetof(TextItem,entries_end)!=0x188||offsetof(TextItem,visual)!=0x1c4) return 1;
    fs[0]=0xffffffffu; if(test_install_fs(fs)!=0||test_get_fs_head()!=fs[0]) return 2;
    if(!run(3,false,false,true)) return 3;
    if(!run(3,false,false,false)) return 4;
    if(!run(0,false,false,false)) return 5;
    if(!run(2,true,false,false)) return 6;
    if(!run(4,true,true,false)) return 7;
    if(!run(0xffffffffu,false,false,false)) return 8;
    return 0;
}
extern "C" void* memcpy(void* d,const void* s,unsigned n) { unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s; for(unsigned i=0;i<n;++i) a[i]=b[i]; return d; }
