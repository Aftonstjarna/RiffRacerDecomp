#include "impl.hpp"
extern "C" float __attribute__((thiscall)) original_font_utf16_advance(Font *, const uint16_t *);
extern "C" unsigned test_get_mxcsr();
extern "C" void test_set_mxcsr(unsigned);
static unsigned bits(float f) { union { float f; unsigned u; } v; v.f=f; return v.u; }
static void fill(void *p, unsigned n, unsigned char v) { unsigned char *q=(unsigned char*)p; while(n--) *q++=v; }
static bool equal(const void *a,const void *b,unsigned n) { const unsigned char *x=(const unsigned char*)a,*y=(const unsigned char*)b; while(n--) if (*x++ != *y++) return false; return true; }
static Font a,b, before_a,before_b;
static FontGlyph primary[4], alternate[3], fallback, before_p[4],before_q[3],before_f;
static uint16_t textbuf[32], before_text[32];
static void copy(void *d,const void *s,unsigned n) { unsigned char *x=(unsigned char*)d; const unsigned char *y=(const unsigned char*)s; while(n--) *x++=*y++; }
static int check(const uint16_t *s) {
    copy(&before_a,&a,sizeof a); copy(&before_b,&b,sizeof b);
    copy(before_p,primary,sizeof primary); copy(before_q,alternate,sizeof alternate); copy(&before_f,&fallback,sizeof fallback); copy(before_text,textbuf,sizeof textbuf);
    unsigned initial=test_get_mxcsr();
    float expected=original_font_utf16_advance(&a,s); unsigned mx1=test_get_mxcsr();
    test_set_mxcsr(initial);
    float actual=a.advance_utf16(s); unsigned mx2=test_get_mxcsr();
    if(bits(expected)!=bits(actual) || mx1!=mx2 || !equal(&a,&before_a,sizeof a) || !equal(&b,&before_b,sizeof b) || !equal(primary,before_p,sizeof primary) || !equal(alternate,before_q,sizeof alternate) || !equal(&fallback,&before_f,sizeof fallback) || !equal(textbuf,before_text,sizeof textbuf)) return 1;
    return 0;
}
extern "C" int test_main() {
    fill(&a,sizeof a,0x69); fill(&b,sizeof b,0x37); fill(primary,sizeof primary,0x41); fill(alternate,sizeof alternate,0x52); fill(&fallback,sizeof fallback,0x73); fill(textbuf,sizeof textbuf,0);
    a.begin=primary; a.end=primary+4; a.fallback=&fallback; a.alternate=&b;
    b.begin=alternate; b.end=alternate+3; b.alternate=&a;
    primary[0].code='A'; primary[0].advance=1.25f; primary[1].code='B'; primary[1].advance=-2.0f; primary[2].code='A'; primary[2].advance=90.0f; primary[3].code=0xd800; primary[3].advance=7.0f;
    alternate[0].code='A'; alternate[0].advance=100.0f; alternate[1].code='C'; alternate[1].advance=3.5f; alternate[2].code=0xdc00; alternate[2].advance=8.0f;
    fallback.advance=0.75f; a.line_break.advance=4.0f;
    if(check(0) || check(textbuf)) return 1;
    const uint16_t values[]={ 'A','C','?',13,10,'B',0xd800,0xdc00,'A',0 };
    copy(textbuf,values,sizeof values);
    if(check(textbuf)) return 2;
    a.alternate=0; if(check(textbuf)) return 3;
    a.alternate=&b; a.end=a.begin; if(check(textbuf)) return 4;
    b.end=b.begin; if(check(textbuf)) return 5;
    a.begin=primary; a.end=primary+4; b.end=alternate+3;
    // Rounding mode and masked exceptional arithmetic are compared as well.
    unsigned saved=test_get_mxcsr();
    for(unsigned mode=0;mode<4;++mode) {
        test_set_mxcsr((saved & ~0x603fu) | (mode<<13));
        primary[0].advance=16777216.0f; alternate[1].advance=1.0f; fallback.advance=-16777216.0f;
        textbuf[0]='A'; textbuf[1]='C'; textbuf[2]='?'; textbuf[3]=0;
        if(check(textbuf)) return 6;
    }
    test_set_mxcsr(saved);
    return 0;
}
