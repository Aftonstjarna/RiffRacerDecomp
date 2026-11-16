#include "impl.hpp"
#include <stddef.h>
extern "C" int original_audio_buffered_read_exact_callback(BufferedAudioStream*,void*,int32_t);
// GCC regparm(3): EAX ignored, EDX destination, ECX buffer; count on stack.
extern "C" int __attribute__((regparm(3))) original_audio_buffer_read_range(unsigned,void*,AudioBuffer*,int32_t);
int32_t AudioBuffer::read_range(void* destination,int32_t count) {
    return original_audio_buffer_read_range(0,destination,this,count);
}
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static unsigned calls, sizes[8];
extern "C" void* memcpy(void* d,const void* s,size_t n) {
    if(calls<8) sizes[calls]=n;
    ++calls;
    for(size_t i=0;i<n;++i) static_cast<unsigned char*>(d)[i]=static_cast<const unsigned char*>(s)[i];
    return d;
}
extern "C" void* memset(void* d,int c,size_t n) {
    for(size_t i=0;i<n;++i) static_cast<unsigned char*>(d)[i]=static_cast<unsigned char>(c);
    return d;
}
typedef void* (*Copy)(void*,const void*,size_t);
extern "C" { Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy; }
static bool same(const void* a,const void* b,unsigned n) {
    for(unsigned i=0;i<n;++i) if(static_cast<const unsigned char*>(a)[i]!=static_cast<const unsigned char*>(b)[i]) return false;
    return true;
}
static BufferedAudioStream x,y,before;
static int check(int shape,int cursor,int count,int total,int saved) {
    unsigned char data[32],original_data[32],a[64],b[64];
    for(unsigned i=0;i<32;++i) data[i]=original_data[i]=static_cast<unsigned char>(i*7+3);
    for(unsigned i=0;i<64;++i) a[i]=b[i]=0xcd;
    AudioChunk nodes[4]={{data,5,8,0},{data+8,0,8,0},{data+16,7,8,0},{data+24,3,8,0}};
    for(int i=0;i<3;++i) nodes[i].next=&nodes[i+1];
    if(shape==1) nodes[0].next=0;
    AudioChunk old_nodes[4];
    for(int i=0;i<4;++i) old_nodes[i]=nodes[i];
    memset(&x,0xa7,sizeof x);
    AudioBuffer buffer={shape==2?0:nodes,&nodes[3],total,cursor,saved,{11,22,33,44,55}};
    x.buffer=buffer; y=x; before=x;
    calls=0;
    int want=original_audio_buffered_read_exact_callback(&x,a+4,count);
    if(test_get_fs_head()!=0xffffffffu) return 1;
    unsigned nc=calls,old_sizes[8];
    for(unsigned i=0;i<8;++i) old_sizes[i]=sizes[i];
    calls=0;
    int got=audio_buffered_read_exact_callback(&y,b+4,count);
    if(test_get_fs_head()!=0xffffffffu) return 2;
    if(want!=got || !same(a,b,64) || !same(&x,&y,sizeof x) || calls!=nc) return 3;
    for(unsigned i=0;i<nc && i<8;++i) if(sizes[i]!=old_sizes[i]) return 4;
    before.buffer.cursor=x.buffer.cursor;
    if(!same(&before,&x,sizeof x) || !same(nodes,old_nodes,sizeof nodes) || !same(data,original_data,32)) return 5;
    if(total-cursor<count) {
        if(want!=-10 || x.buffer.cursor!=saved || nc) return 6;
    } else if(count<0) { if(want!=-1 || nc || x.buffer.cursor!=cursor) return 7; }
    else {
        int copied=0;
        int available=(shape==2?0:(shape==1?5:15))-cursor;
        if(available>0 && count>0) copied=count<available?count:available;
        if(want!=(copied==count?count:-1) || x.buffer.cursor!=cursor+copied) return 8;
    }
    return 0;
}
extern "C" int test_main() {
    static unsigned fs[8]; fs[0]=0xffffffffu;
    if(test_install_fs(fs)!=0) return 10;
    if(sizeof(AudioChunk)!=16 || sizeof(AudioBuffer)!=40 || offsetof(BufferedAudioStream,buffer)!=0x6d7c) return 11;
    for(int shape=0;shape<3;++shape)
        for(int cursor=0;cursor<=17;++cursor)
            for(int count=-3;count<=20;++count) {
                int r=check(shape,cursor,count,15,2);
                if(r) return 20+r;
            }
    if(check(0,3,0x7fffffff,15,-9)) return 40;
    if(check(0,0,0,0,-9)) return 41;
    if(check(0,0,(-2147483647-1),15,-9)) return 42;
    return 0;
}
