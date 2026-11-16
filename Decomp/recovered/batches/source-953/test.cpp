#include "impl.hpp"
extern "C" int32_t __attribute__((cdecl)) original_audio_input_read_loop(riff::AudioInput*, void*, int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
static riff::AudioInput state;
static unsigned char initial[sizeof(state)], after[sizeof(state)];
static unsigned char buffer[64], original_buffer[64];
static uint32_t fs[16];
struct Visit { uintptr_t destination; int32_t remaining; uint32_t position, flags, which; };
static Visit visits[16], oracle_visits[16];
static unsigned calls, oracle_calls, length;
static int32_t results[8];
static bool mutate, write_buffer, bad;
static int32_t RIFF_CDECL alternate(riff::AudioInput*,void*,int32_t);
static int32_t callback(riff::AudioInput* p,void* b,int32_t n,unsigned which) {
    if(p!=&state || calls>=8) { bad=true; return -1; }
    Visit& v=visits[calls];
    v.destination=reinterpret_cast<uintptr_t>(b); v.remaining=n;
    v.position=p->position; v.flags=p->flags; v.which=which;
    if(write_buffer && n>0) *static_cast<unsigned char*>(b)=static_cast<unsigned char>(0x30+calls);
    if(mutate) { p->flags^=8; p->position+=17; p->unknown_0000[13]^=0x81; p->read=alternate; }
    unsigned i=calls++;
    return i<length ? results[i] : 0;
}
static int32_t RIFF_CDECL primary(riff::AudioInput* p,void* b,int32_t n) {return callback(p,b,n,0);}
static int32_t RIFF_CDECL alternate(riff::AudioInput* p,void* b,int32_t n) {return callback(p,b,n,1);}
static void copy(void* d,const void* s,unsigned n) {unsigned char* a=(unsigned char*)d; const unsigned char* b=(const unsigned char*)s;for(unsigned i=0;i<n;++i)a[i]=b[i];}
static bool equal(const void* d,const void* s,unsigned n) {const unsigned char* a=(const unsigned char*)d; const unsigned char* b=(const unsigned char*)s;for(unsigned i=0;i<n;++i)if(a[i]!=b[i])return false;return true;}
extern "C" int test_main() {
    fs[0]=0x12345678; if(test_install_fs(fs)!=0)return 1;
    const int32_t scripts[][8]={{0},{-1},{-2147483647-1},{2,3,0},{2,-57},{3,3,3,3},{11},{2147483646,5,0},{2147483647,2147483647,0}};
    const unsigned lengths[]={1,1,1,3,2,4,1,3,3};
    const int32_t counts[]={-2147483647-1,-1,0,1,7,10,2147483647};
    for(unsigned s=0;s<9;++s)for(unsigned c=0;c<7;++c)for(unsigned mode=0;mode<8;++mode) {
        unsigned char* bytes=(unsigned char*)&state;
        for(unsigned i=0;i<sizeof(state);++i)bytes[i]=(unsigned char)(i*37+mode);
        state.position=(mode&1)?0xfffffffdu:23; state.flags=(mode&2)?0xffffff08u:0xffff0000u;
        state.read=primary; copy(initial,&state,sizeof(state));
        length=lengths[s];for(unsigned i=0;i<8;++i)results[i]=scripts[s][i];
        mutate=(mode&4)!=0; write_buffer=(s<7); bad=false; calls=0;
        for(unsigned i=0;i<64;++i)buffer[i]=(unsigned char)(i^0xa5);
        // Huge-return scenarios use opaque addresses, never dereferenced.
        void* dest=write_buffer ? (void*)buffer : reinterpret_cast<void*>(uintptr_t(0xf0000000u));
        int32_t expected=original_audio_input_read_loop(&state,dest,counts[c]);
        if(test_get_fs_head()!=fs[0] || bad)return 2;
        oracle_calls=calls; copy(oracle_visits,visits,sizeof(visits));
        copy(after,&state,sizeof(state));copy(original_buffer,buffer,64);
        copy(&state,initial,sizeof(state)); calls=0;
        for(unsigned i=0;i<64;++i)buffer[i]=(unsigned char)(i^0xa5);
        int32_t actual=riff::audio_input_read_loop(&state,dest,counts[c]);
        if(actual!=expected || calls!=oracle_calls || bad)return 3;
        if(!equal(after,&state,sizeof(state)) || !equal(buffer,original_buffer,64))return 4;
        if(!equal(visits,oracle_visits,calls*sizeof(Visit)))return 5;
    }
    // Early exit must not dereference even null state/destination.
    for(int n=-1;n<=0;++n) {
        if(original_audio_input_read_loop(0,0,n)!=0 || test_get_fs_head()!=fs[0])return 6;
        if(riff::audio_input_read_loop(0,0,n)!=0)return 7;
    }
    test_write("504 differential cases passed\n",30);
    return 0;
}
extern "C" void* memset(void* p,int value,size_t n) { unsigned char* d=(unsigned char*)p; for(size_t i=0;i<n;++i)d[i]=(unsigned char)value;return p; }
extern "C" void* memcpy(void* d,const void* s,size_t n) { copy(d,s,(unsigned)n);return d; }
