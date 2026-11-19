#include "impl.hpp"
#include <stddef.h>
extern "C" GlyphRecord* __attribute__((thiscall)) original_font_glyph_lookup(FontLookup*, uint16_t, uint8_t*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static_assert(sizeof(GlyphRecord)==0x2c, "glyph size");
static_assert(offsetof(FontLookup, begin)==0x28 && offsetof(FontLookup, end)==0x2c && offsetof(FontLookup, fallback)==0x34 && offsetof(FontLookup, line_break)==0x38 && offsetof(FontLookup, secondary)==0x68, "font layout");
static void fill(void* p, unsigned n, unsigned char v) { unsigned char* b=(unsigned char*)p; for(unsigned i=0;i<n;++i) b[i]=v; }
static bool same(const void* a,const void* b,unsigned n) { const unsigned char* x=(const unsigned char*)a; const unsigned char* y=(const unsigned char*)b; for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false; return true; }
extern "C" int test_main() {
    unsigned fs_storage[8] = {0x12345678};
    if (test_install_fs(fs_storage) != 0 || test_get_fs_head() != 0x12345678) return 3;
    GlyphRecord primary[3], secondary[3], fallback;
    FontLookup font, alt;
    fill(&font,sizeof(font),0x91); fill(&alt,sizeof(alt),0x82);
    fill(primary,sizeof(primary),0x73); fill(secondary,sizeof(secondary),0x64); fill(&fallback,sizeof(fallback),0x55);
    primary[0].character=0; primary[1].character=0x1234; primary[2].character=0x1234;
    secondary[0].character=0x1234; secondary[1].character=0xffff; secondary[2].character=0x0041;
    font.begin=primary; font.end=primary+3; font.fallback=&fallback; font.secondary=&alt;
    alt.begin=secondary; alt.end=secondary+3; alt.fallback=secondary; alt.secondary=&font;
    const uint16_t chars[]={0,10,13,0x1234,0xffff,0x41,0x42};
    for(unsigned mode=0;mode<8;++mode) for(unsigned c=0;c<sizeof(chars)/sizeof(chars[0]);++c) {
        font.begin=primary; font.end=(mode&1)?primary:primary+3;
        alt.begin=secondary; alt.end=(mode&2)?secondary:secondary+3;
        font.secondary=(mode&4)?0:&alt;
        for(unsigned use=0;use<2;++use) {
            FontLookup before=font, alt_before=alt; GlyphRecord p_before[3],s_before[3],f_before=fallback;
            for(unsigned i=0;i<3;++i) {p_before[i]=primary[i];s_before[i]=secondary[i];}
            unsigned char a[3]={0xa5,0xcc,0x5a}, b[3]={0xa5,0xcc,0x5a};
            GlyphRecord* expected=original_font_glyph_lookup(&font,chars[c],use?&a[1]:0);
            if (test_get_fs_head() != 0x12345678) return 4;
            FontLookup after=font, alt_after=alt; GlyphRecord p_after[3],s_after[3],f_after=fallback;
            for(unsigned i=0;i<3;++i) {p_after[i]=primary[i];s_after[i]=secondary[i];}
            font=before; alt=alt_before; fallback=f_before;
            for(unsigned i=0;i<3;++i) {primary[i]=p_before[i];secondary[i]=s_before[i];}
            GlyphRecord* actual=font.lookup(chars[c],use?&b[1]:0);
            if(actual!=expected || !same(a,b,3) || !same(&font,&after,sizeof(font)) || !same(&alt,&alt_after,sizeof(alt)) || !same(primary,p_after,sizeof(primary)) || !same(secondary,s_after,sizeof(secondary)) || !same(&fallback,&f_after,sizeof(fallback))) return 1;
        }
    }
    // Aliasing the output with the first character byte changes the subsequent search.
    primary[0].character=0x1201; font.begin=primary; font.end=primary+3; font.secondary=&alt;
    GlyphRecord* a=original_font_glyph_lookup(&font,0x1200,(uint8_t*)&primary[0].character);
    if (test_get_fs_head() != 0x12345678) return 5;
    primary[0].character=0x1201;
    GlyphRecord* b=font.lookup(0x1200,(uint8_t*)&primary[0].character);
    if(a!=b || b!=primary || primary[0].character!=0x1200) return 2;
    return 0;
}
