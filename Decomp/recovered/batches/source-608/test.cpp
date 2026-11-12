#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_record_pointer_stack_recycle(riff::RecordOwner*, riff::RecordPointerStack*);
extern "C" void test_write(const char*, unsigned);
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static void fill(void* a, unsigned n, unsigned seed) {
    unsigned char* p=static_cast<unsigned char*>(a);
    for(unsigned i=0;i<n;++i) p[i]=static_cast<unsigned char>(i*37+seed);
}
extern "C" int test_main() {
    const uint32_t patterns[]={0,1,0x80000000u,0xffffffffu,0x12345678u};
    for(unsigned pat=0;pat<5;++pat) {
        for(unsigned count=1;count<=9;++count) {
            for(unsigned dest=0;dest<=4;++dest) {
                riff::RecordOwner a,b;
                riff::RecordPointerStack s,t;
                fill(&a,sizeof(a),pat+1); fill(&s,sizeof(s),pat+41);
                for(unsigned i=0;i<4;++i) s.records[i]=patterns[pat];
                s.count=count; a.recycle_count=dest;
                b=a; t=s;
                original_record_pointer_stack_recycle(&a,&s);
                b.recycle(&t);
                if(!equal(&a,&b,sizeof(a)) || !equal(&s,&t,sizeof(s))) return 1;
                if(s.count!=count-1) return 2;
                // Explicit expected side effects, including destination/count overlap.
                riff::RecordOwner expected; riff::RecordPointerStack before;
                fill(&expected,sizeof(expected),pat+1); fill(&before,sizeof(before),pat+41);
                for(unsigned i=0;i<4;++i) before.records[i]=patterns[pat];
                before.count=count-1;
                uint32_t value;
                if(count<=4) value=patterns[pat];
                else if(count<=8) value=before.parallel[count-5];
                else value=count-1;
                expected.recycle_count=dest;
                if(dest<4) { expected.recycled[dest]=value; expected.recycle_count=dest+1; }
                else expected.recycle_count=value+1;
                if(!equal(&a,&expected,sizeof(a)) || !equal(&s,&before,sizeof(s))) return 3;
            }
        }
    }
    // Repeated pops preserve LIFO order and leave source entries untouched.
    riff::RecordOwner a={},b={}; riff::RecordPointerStack s={},t={};
    s.count=4; for(unsigned i=0;i<4;++i) s.records[i]=0x1000+i*16;
    t=s;
    for(unsigned i=0;i<4;++i) {
        original_record_pointer_stack_recycle(&a,&s); b.recycle(&t);
        if(!equal(&a,&b,sizeof(a)) || !equal(&s,&t,sizeof(s))) return 4;
        if(a.recycled[i]!=0x1000+(3-i)*16) return 5;
    }
    test_write("record recycle: passed\n",23);
    return 0;
}
extern "C" void* memcpy(void* d,const void* s, size_t n) {
    unsigned char* dst=static_cast<unsigned char*>(d);
    const unsigned char* src=static_cast<const unsigned char*>(s);
    for(size_t i=0;i<n;++i) dst[i]=src[i];
    return d;
}
extern "C" void* memset(void* d,int c,size_t n) {
    unsigned char* dst=static_cast<unsigned char*>(d);
    for(size_t i=0;i<n;++i) dst[i]=static_cast<unsigned char>(c);
    return d;
}
