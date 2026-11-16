#include "impl.hpp"
#include <stddef.h>
#include <stdarg.h>
// regparm(3) uses EAX,EDX,ECX; EAX is ignored by these originals.
// This adapter also leaves the fourth argument on the caller-cleaned stack.
extern "C" int __attribute__((regparm(3))) original_audio_stream_append_buffer(unsigned,const void*,AudioStream*,int32_t);
extern "C" int __attribute__((regparm(3))) original_audio_buffer_append(unsigned,const void*,AudioBuffer*,int32_t);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*,unsigned);
extern "C" void* memcpy(void* d,const void* s,size_t n) {
    for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=((const unsigned char*)s)[i];
    return d;
}
extern "C" void* memset(void* d,int c,size_t n) {
    for(size_t i=0;i<n;++i) ((unsigned char*)d)[i]=(unsigned char)c;
    return d;
}
typedef void* (*Copy)(void*,const void*,size_t);
extern "C" { Copy copy_import __attribute__((section(".test_iat"),used,aligned(4)))=memcpy; }
static unsigned logs,allocs,errors,helper_calls;
static AudioBuffer* expected_buffer;
static const void* expected_source;
static int32_t expected_count;
static int mode;
static unsigned char iob[96];
static void* get_iob() { return iob; }
static int print_error(void* stream,const char* fmt,...) {
    va_list a; va_start(a,fmt);
    int line=va_arg(a,int),result=va_arg(a,int); va_end(a);
    if(stream!=iob+64 || (unsigned)fmt!=0xa03c98 || line!=769 || result!=-1) ++errors;
    ++logs; return 123;
}
static void* fail_alloc(size_t) { ++allocs; return 0; }
static void free_unused(void*) { ++errors; }
// Local full-path testing binds only the four audited imports reached here.
// The coordinator may not map this additional section: guard those cases.
struct Imports { int (*print)(void*,const char*,...); void* (*iob)(); uint32_t unused[2]; void* (*alloc)(size_t); uint32_t unused2; void (*release)(void*); };
extern "C" { Imports audio_imports __attribute__((section(".audio_imports"),used,aligned(4)))={print_error,get_iob,{0,0},fail_alloc,0,free_unused}; }
int32_t AudioBuffer::append(const void* s,int32_t n) {
    ++helper_calls;
    if(this!=expected_buffer || s!=expected_source || n!=expected_count) ++errors;
    if(mode) return mode;
    int r=original_audio_buffer_append(0,s,this,n);
    if(test_get_fs_head()!=0xffffffffu) ++errors;
    return r;
}
void audio_append_diagnostic(const char* f,int32_t line,int32_t result) {
    const char* want="\n[..\\SDK\\mpg123\\readers.c:%i] error: Failed to add buffer, return: %i\n";
    unsigned i=0; while(want[i] && f[i]==want[i]) ++i;
    if(f[i]!=want[i] || line!=769 || result!=-1) ++errors;
    ++logs;
}
static bool same(const void* a,const void* b,unsigned n) {
    for(unsigned i=0;i<n;++i) if(((const unsigned char*)a)[i]!=((const unsigned char*)b)[i]) return false;
    return true;
}
static AudioStream stream,before,after;
static unsigned char bytes[32],initial[32],final_bytes[32],source[32];
static int check(int count,unsigned flags,int shape) {
    memset(&stream,0xa5,sizeof stream);
    for(unsigned i=0;i<32;++i) bytes[i]=initial[i]=(unsigned char)(i*3+11),source[i]=(unsigned char)(i*7+99);
    AudioChunk node={bytes+4,shape==1?7:2,8,0};
    AudioChunk old=node;
    stream.buffer.first=&node; stream.buffer.last=&node;
    stream.buffer.length=node.length; stream.buffer.free_list=0;
    stream.buffer.free_count=0; stream.buffer.allocation_size=8;
    stream.flags=(unsigned char)flags;
    before=stream;
    logs=allocs=errors=0;
    int want=original_audio_stream_append_buffer(0,count<=0?0:source,&stream,count);
    if(test_get_fs_head()!=0xffffffffu) return 1;
    after=stream; AudioChunk final_node=node;
    memcpy(final_bytes,bytes,32);
    unsigned nl=logs,na=allocs;
    stream=before; node=old; memcpy(bytes,initial,32);
    logs=allocs=helper_calls=0;
    expected_buffer=&stream.buffer; expected_source=count<=0?0:source; expected_count=count;
    int got=stream.append_buffer(expected_source,count);
    if(want!=got || !same(&stream,&after,sizeof stream) || !same(bytes,final_bytes,32) || !same(&node,&final_node,sizeof node) || logs!=nl || allocs!=na || helper_calls!=1 || errors) return 2;
    int room=old.capacity-old.length;
    int copied=count<=0?0:(count<room?count:room);
    bool fail=count>room;
    if(got!=(fail?-1:0) || node.length!=old.length+copied || stream.buffer.length!=old.length+copied || logs!=(fail && !(flags&32)?1u:0u)) return 3;
    before.buffer.length+=copied;
    if(!same(&stream,&before,sizeof stream)) return 4;
    for(unsigned i=0;i<32;++i) {
        unsigned char expected=(i>=4u+(unsigned)old.length && i<4u+(unsigned)(old.length+copied))?source[i-4-old.length]:initial[i];
        if(bytes[i]!=expected || source[i]!=(unsigned char)(i*7+99)) return 5;
    }
    return 0;
}
extern "C" int test_main() {
    static unsigned fs[8]; fs[0]=0xffffffffu;
    if(test_install_fs(fs)) return 10;
    if(offsetof(AudioStream,buffer)!=0x6d7c || offsetof(AudioStream,flags)!=0x6dac || sizeof(AudioBuffer)!=40) return 11;
    bool imports=(unsigned)&audio_imports==0x92d38c;
    int counts[]={(-2147483647-1),-1,0,1,2,6,7,16,0x7fffffff};
    for(unsigned f=0;f<256;++f) for(int sh=0;sh<2;++sh) for(unsigned c=0;c<9;++c) {
        int room=sh==1?1:6;
        if(counts[c]>room && !imports) continue;
        int r=check(counts[c],f,sh); if(r) return 20+r;
    }
    // Dependency contract: every nonzero result normalizes to -1, including positive results.
    int results[]={1,-1,-2,(-2147483647-1),0x7fffffff};
    for(unsigned i=0;i<5;++i) for(unsigned f=0;f<256;++f) {
        memset(&stream,0x7b,sizeof stream); stream.flags=(unsigned char)f; before=stream;
        expected_buffer=&stream.buffer; expected_source=0; expected_count=-17;
        mode=results[i]; logs=helper_calls=errors=0;
        if(stream.append_buffer(0,-17)!=-1 || logs!=((f&32)?0u:1u) || helper_calls!=1 || errors || !same(&stream,&before,sizeof stream)) return 30;
    }
    if(!imports) { const char msg[]="Allocation-failure oracle paths require .audio_imports at 0x92d38c; success paths compared.\n"; test_write(msg,sizeof(msg)-1); }
    return 0;
}
