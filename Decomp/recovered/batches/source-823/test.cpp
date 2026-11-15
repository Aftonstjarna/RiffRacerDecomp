#include "impl.hpp"
extern "C" int32_t __attribute__((fastcall)) original_script_frame_current_line(riff::ScriptState*, riff::ScriptFrame*);
extern "C" void test_write(const char*, unsigned);
namespace {
using namespace riff;
struct Fixture {
    ScriptState state;
    ScriptFrame frame;
    ScriptFrame other;
    ScriptValue value;
    ScriptClosure closure;
    ScriptPrototype prototype;
    int32_t lines[32];
    uint32_t guard[8];
};
Fixture fixture;
unsigned char initial[sizeof(Fixture)];
unsigned char reference_result[sizeof(Fixture)];
void copy(void* dst, const void* src, unsigned n) {
    unsigned char* d = static_cast<unsigned char*>(dst);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for (unsigned i=0;i<n;++i) d[i]=s[i];
}
bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x=static_cast<const unsigned char*>(a);
    const unsigned char* y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
bool check(uint32_t tag, unsigned native, bool active, bool table,
           uint32_t base, uint32_t distance) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&fixture);
    for(unsigned i=0;i<sizeof(fixture);++i) bytes[i]=static_cast<unsigned char>(i*37u+91u);
    fixture.state.active_frame = active ? &fixture.frame : &fixture.other;
    fixture.state.current_pc = base + distance;
    fixture.frame.function = &fixture.value;
    fixture.frame.saved_pc = active ? 0x01234567u : base + distance;
    fixture.value.tag=tag;
    fixture.value.closure=&fixture.closure;
    fixture.closure.native_flag=static_cast<uint8_t>(native);
    fixture.closure.prototype=&fixture.prototype;
    fixture.prototype.code_address=base;
    fixture.prototype.line_table=table ? fixture.lines : 0;
    for(unsigned i=0;i<32;++i) fixture.lines[i]=i==2 ? -1 : i==3 ? 0 : static_cast<int32_t>(100+i*19);
    fixture.lines[5]=static_cast<int32_t>(0x80000000u);
    fixture.lines[6]=0x7fffffff;
    copy(initial,&fixture,sizeof(fixture));
    int32_t original=original_script_frame_current_line(&fixture.state,&fixture.frame);
    copy(reference_result,&fixture,sizeof(fixture));
    copy(&fixture,initial,sizeof(fixture));
    int32_t recovered=script_frame_current_line(&fixture.state,&fixture.frame);
    if(original!=recovered || !equal(&fixture,reference_result,sizeof(fixture))) return false;
    // Independent expectations use a widened signed difference and floor divide.
    int32_t expected=-1;
    if(tag==6 && native==0) {
        int64_t delta=distance;
        if(distance & 0x80000000u) delta-=0x100000000LL;
        int64_t index=(delta>=0 ? delta/4 : -((-delta+3)/4))-1;
        if(index>=0) expected=table ? fixture.lines[static_cast<unsigned>(index)] : 0;
    }
    if(original!=expected) return false;
    // Check every byte against the input with precisely the one permitted store.
    if(tag==6 && native==0 && active) {
        uint32_t pc=base+distance;
        copy(initial+offsetof(Fixture,frame)+offsetof(ScriptFrame,saved_pc),&pc,4);
    }
    return equal(initial,&fixture,sizeof(fixture));
}
}
extern "C" int test_main() {
    const uint32_t tags[]={0,5,6,7,0xffffffffu};
    const unsigned flags[]={0,1,128,255};
    const uint32_t bases[]={0,0x10000000u,0xfffffff0u};
    unsigned count=0;
    for(unsigned t=0;t<5;++t) for(unsigned f=0;f<4;++f)
    for(unsigned a=0;a<2;++a) for(unsigned l=0;l<2;++l)
    for(unsigned b=0;b<3;++b) for(int d=-20;d<=131;++d) {
        if(!check(tags[t],flags[f],a!=0,l!=0,bases[b],static_cast<uint32_t>(d))) return 1;
        ++count;
    }
    const uint32_t extremes[]={0x7fffffffu,0x80000000u,0x80000001u,0xfffffffcu,0xffffffffu,0x40000000u};
    for(unsigned a=0;a<2;++a) for(unsigned b=0;b<3;++b) for(unsigned d=0;d<6;++d) {
        if(!check(6,0,a!=0,false,bases[b],extremes[d])) return 2;
        ++count;
    }
    // Rejection must not touch the closure/prototype or state: poison the
    // downstream pointer while keeping only the fields actually read valid.
    fixture.value.tag=5;
    fixture.value.closure=0;
    fixture.frame.function=&fixture.value;
    copy(initial,&fixture,sizeof(fixture));
    if(original_script_frame_current_line(0,&fixture.frame)!=-1 ||
       script_frame_current_line(0,&fixture.frame)!=-1 ||
       !equal(initial,&fixture,sizeof(fixture))) return 3;
    fixture.value.tag=6;
    fixture.value.closure=&fixture.closure;
    fixture.closure.native_flag=255;
    fixture.closure.prototype=0;
    copy(initial,&fixture,sizeof(fixture));
    if(original_script_frame_current_line(0,&fixture.frame)!=-1 ||
       script_frame_current_line(0,&fixture.frame)!=-1 ||
       !equal(initial,&fixture,sizeof(fixture))) return 4;
    (void)count;
    const char message[]="script-frame-current-line: 36518 cases passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
