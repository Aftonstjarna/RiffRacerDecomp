#include "impl.hpp"
#include <stddef.h>
// Target is a caller-clean internal register convention. regparm(3) maps
// unused->EAX, destination->EDX, stream->ECX, requested->stack exactly.
// Neither GCC thiscall nor fastcall describes this original ABI correctly.
extern "C" uint32_t __attribute__((regparm(3))) original_script_stream_read_block(
    uint32_t unused, void* destination, ScriptStream* stream, uint32_t requested);
extern "C" void* memcpy(void* d, const void* s, size_t n) {
    unsigned char* a = static_cast<unsigned char*>(d);
    const unsigned char* b = static_cast<const unsigned char*>(s);
    for (size_t i=0;i<n;++i) a[i]=b[i];
    return d;
}
typedef void* (*Copy)(void*,const void*,size_t);
Copy copyImport __attribute__((section(".test_iat"),used,aligned(4))) = memcpy;
static unsigned char data[24] = {255,0,128,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21};
struct Feed {
    unsigned calls;
    unsigned lengths[4];
    unsigned incoming[4];
    unsigned offsets[4];
    unsigned nullAt;
    unsigned keepAt;
    bool bad;
};
static const unsigned char* RIFF_CDECL refill(void* first, void* second, uint32_t* size) {
    Feed* f=static_cast<Feed*>(first);
    if (second != data+23 || f->calls >= 4) { f->bad=true; return 0; }
    unsigned i=f->calls++;
    f->incoming[i]=*size;
    if(i != f->keepAt) *size=f->lengths[i];
    return i==f->nullAt ? 0 : data+f->offsets[i];
}
static bool run(unsigned buffered, unsigned request, unsigned mode) {
    Feed a={}, b={};
    a.nullAt=3; a.keepAt=99;
    a.lengths[0]=3; a.lengths[1]=5; a.lengths[2]=2; a.lengths[3]=7;
    a.offsets[0]=4; a.offsets[1]=8; a.offsets[2]=15;
    if(mode==1) a.nullAt=0;
    if(mode==2) a.lengths[0]=0;
    if(mode==3) a.keepAt=1;
    if(mode==4) {a.nullAt=1; a.lengths[1]=0;}
    b=a;
    struct Guarded { uint32_t pre; ScriptStream stream; uint32_t post; };
    Guarded x={0x12345678,{buffered,data,refill,data+23,&a},0xabcdef01};
    Guarded y=x; y.stream.sourceContext=&b;
    unsigned char outA[48],outB[48];
    for(unsigned i=0;i<48;++i) outA[i]=outB[i]=0xa5;
    uint32_t ra=original_script_stream_read_block(0,outA+3,&x.stream,request);
    uint32_t rb=y.stream.readBlock(outB+3,request);
    if(ra!=rb || x.stream.available!=y.stream.available || x.stream.cursor!=y.stream.cursor) return false;
    if(x.pre!=y.pre || x.post!=y.post || x.pre!=0x12345678 || x.post!=0xabcdef01) return false;
    if(x.stream.reader!=refill || y.stream.reader!=refill || x.stream.readerContext!=data+23 || y.stream.readerContext!=data+23 || x.stream.sourceContext!=&a || y.stream.sourceContext!=&b) return false;
    if(a.bad || b.bad || a.calls!=b.calls) return false;
    for(unsigned i=0;i<4;++i) if(a.incoming[i]!=b.incoming[i] || a.lengths[i]!=b.lengths[i] || a.offsets[i]!=b.offsets[i]) return false;
    if(a.calls && a.incoming[0]!=request) return false;
    for(unsigned i=0;i<48;++i) {
        if(outA[i]!=outB[i]) return false;
        if((i<3 || i>=3+request-ra) && outA[i]!=0xa5) return false;
    }
    if(request==0 && (ra!=0 || a.calls!=0 || x.stream.available!=buffered || x.stream.cursor!=data)) return false;
    return true;
}
extern "C" int test_main() {
    static_assert(sizeof(ScriptStream)==20,"original i386 layout");
    copyImport=memcpy;
    for(unsigned mode=0;mode<5;++mode)
        for(unsigned buffered=0;buffered<=8;++buffered)
            for(unsigned request=0;request<=24;++request)
                if(!run(buffered,request,mode)) return 1;
    return 0;
}
