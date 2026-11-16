#include "impl.hpp"
#include <stddef.h>
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
// regparm(3) assigns EAX,EDX,ECX in that order and leaves count on the
// caller-cleaned stack. EAX is an ignored dummy, not an original argument.
// Neither thiscall nor fastcall alone describes this optimized internal ABI.
extern "C" int __attribute__((regparm(3))) original_audio_buffer_read_range(
    unsigned ignored_eax, void* destination, AudioBuffer* self, int count);
static unsigned calls, sizes[16];
extern "C" void* memcpy(void* dst, const void* src, size_t n) {
    if (calls < 16) sizes[calls] = n;
    ++calls;
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (size_t i=0;i<n;++i) d[i]=s[i];
    return dst;
}
extern "C" void* memset(void* dst, int value, size_t n) {
    unsigned char* d=static_cast<unsigned char*>(dst);
    for(size_t i=0;i<n;++i) d[i]=static_cast<unsigned char>(value);
    return dst;
}
typedef void* (*Copy)(void*, const void*, size_t);
extern "C" { Copy test_copy_import __attribute__((section(".test_iat"),used,aligned(4))) = memcpy; }
static bool same(const void* a,const void* b,unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int check(int shape,int cursor,int count,int total,int saved) {
    unsigned char data[32], before_data[32], a[64],b[64];
    for(unsigned i=0;i<32;++i) data[i]=before_data[i]=static_cast<unsigned char>(i*7+3);
    for(unsigned i=0;i<64;++i) a[i]=b[i]=0xCD;
    AudioChunk nodes[4]={{data,5,8,0},{data+8,0,8,0},{data+16,7,8,0},{data+24,3,8,0}};
    for(int i=0;i<3;++i) nodes[i].next=&nodes[i+1];
    if(shape==1) nodes[0].next=0;
    AudioChunk before_nodes[4];
    for(int i=0;i<4;++i) before_nodes[i]=nodes[i];
    AudioBuffer x={shape==2?0:nodes,&nodes[3],total,cursor,saved,{11,22,33,44,55}};
    AudioBuffer y=x;
    calls=0;
    int want=original_audio_buffer_read_range(0,a+4,&x,count);
    if(test_get_fs_head()!=0xFFFFFFFFu) return 1;
    unsigned nc=calls, expected_sizes[16];
    for(unsigned i=0;i<16;++i) expected_sizes[i]=sizes[i];
    calls=0;
    int got=y.read_range(b+4,count);
    if(got!=want || !same(a,b,64) || !same(&x,&y,sizeof x) || calls!=nc) return 2;
    for(unsigned i=0;i<nc && i<16;++i) if(sizes[i]!=expected_sizes[i]) return 3;
    if(!same(nodes,before_nodes,sizeof nodes) || !same(data,before_data,32)) return 4;
    // Independently check that only cursor is changed in the object.
    AudioBuffer unchanged={shape==2?0:nodes,&nodes[3],total,cursor,saved,{11,22,33,44,55}};
    unchanged.cursor=x.cursor;
    if(!same(&x,&unchanged,sizeof x)) return 5;
    if(total-cursor<count) {
        if(want!=-10 || x.cursor!=saved || nc) return 6;
        for(unsigned i=0;i<64;++i) if(a[i]!=0xCD) return 7;
    } else if(count<=0 && (want!=0 || x.cursor!=cursor || nc)) return 8;
    return 0;
}
extern "C" int test_main() {
    static unsigned fs[8]; fs[0]=0xFFFFFFFFu;
    if(test_install_fs(fs)!=0) return 10;
    if(sizeof(AudioChunk)!=16 || sizeof(AudioBuffer)!=40) return 11;
    for(int shape=0;shape<3;++shape)
        for(int cursor=0;cursor<=17;++cursor)
            for(int count=-3;count<=20;++count) {
                int r=check(shape,cursor,count,15,2);
                if(r) return 20+r;
            }
    // Huge signed requests fail without copying. Cursor restoration is literal.
    if(check(0,3,0x7fffffff,15,-9)) return 40;
    if(check(0,0,0,0,-9)) return 41;
    return 0;
}
