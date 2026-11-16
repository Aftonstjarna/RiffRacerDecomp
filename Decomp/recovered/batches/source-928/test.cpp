#include "impl.hpp"
using recovered::AudioFrame;
extern "C" int __attribute__((thiscall)) original_audio_frame_reuse_buffered(AudioFrame*);
extern "C" uint32_t __attribute__((thiscall)) original_audio_bitstream_read16(AudioFrame*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
static uint32_t fs_storage[16];
static bool fs_failed;
uint32_t AudioFrame::read16() {
    uint32_t result=original_audio_bitstream_read16(this);
    if(test_get_fs_head()!=fs_storage[0]) fs_failed=true;
    return result;
}
extern "C" void* memcpy(void* d,const void* s,size_t n) {
    unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s;
    for(size_t i=0;i<n;++i) a[i]=b[i];
    return d;
}
extern "C" {
void* (*copy_import)(void*,const void*,size_t) __attribute__((section(".test_iat"),used,aligned(4))) = memcpy;
void test_write(const char*,unsigned);
}
static AudioFrame a,b;
static uint8_t buffer[128], expected[128];
static void fill(void* p,unsigned n,unsigned seed) { uint8_t* q=(uint8_t*)p; for(unsigned i=0;i<n;++i) q[i]=(uint8_t)(seed+i*37); }
static bool equal(const void* p,const void* q,unsigned n) { const uint8_t* x=(const uint8_t*)p; const uint8_t* y=(const uint8_t*)q; for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false; return true; }
extern "C" int test_main() {
    fs_storage[0]=0xffffffffu;
    if(test_install_fs(fs_storage)!=0) return 2;
    const uint32_t counts[]={0,1,2,0x80000000u,0xffffffffu};
    const uint32_t modes[]={0,2,3,4,0xffffffffu};
    const uint32_t lengths[]={0,1,2,3,16,36};
    for(unsigned f=0;f<5;++f) for(unsigned r=0;r<5;++r)
    for(unsigned m=0;m<5;++m) for(unsigned n=0;n<6;++n)
    for(unsigned p=0;p<3;++p) {
        fill(&a,sizeof(a),f+r+m+n+p);
        fill(buffer,sizeof(buffer),n+p);
        a.frame_count=counts[f]; a.repeats=counts[r]; a.mode=modes[m];
        a.copy_size=lengths[n]; a.read_prefix=p==2?0xffffffffu:p;
        a.buffered=buffer+8; a.cursor=buffer+61; a.bit_offset=7;
        memcpy(&b,&a,sizeof(a));
        int x=original_audio_frame_reuse_buffered(&a);
        if(test_get_fs_head()!=fs_storage[0]) return 3;
        memcpy(expected,buffer,sizeof(buffer));
        fill(buffer,sizeof(buffer),n+p);
        int y=b.reuse_buffered();
        if(fs_failed || x!=y || !equal(&a,&b,sizeof(a)) || !equal(buffer,expected,sizeof(buffer))) return 1;
    }
    test_write("buffered frame oracle checks passed\n",36);
    return 0;
}
