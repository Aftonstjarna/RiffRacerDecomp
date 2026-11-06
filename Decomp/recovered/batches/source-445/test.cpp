#include "impl.hpp"
extern "C" void __attribute__((thiscall)) original_record24_append_one(Record24Storage*, const void*);
extern "C" int test_install_fs(void*);
extern "C" unsigned test_get_fs_head();
extern "C" void test_write(const char*, unsigned);
// Link-only sentinel, never a replacement oracle: no case may request growth.
static unsigned unexpected_growth;
void RECORD_THISCALL Record24Storage::grow(unsigned char*) { ++unexpected_growth; }
static unsigned char a[512], b[512];
static bool equal(const unsigned char* x,const unsigned char* y,unsigned n) {
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    unsigned fs[8]={0x13579bdf,0,0,0,0,0,0,0};
    if(test_install_fs(fs)!=0) return 1;
    // Every byte source offset covers internal record rounding, external sources,
    // source==end, sources before begin and partially overlapping destinations.
    for(unsigned alignment=0;alignment<4;++alignment) {
        for(unsigned count=0;count<=8;++count) {
            for(unsigned offset=0;offset<=360;++offset) {
                for(unsigned i=0;i<512;++i) a[i]=b[i]=static_cast<unsigned char>(i*37+offset*11+count);
                unsigned base=32+alignment, finish=base+count*24;
                Record24Storage x={a+base,a+finish,a+400};
                Record24Storage y={b+base,b+finish,b+400};
                original_record24_append_one(&y,b+offset);
                if(test_get_fs_head()!=fs[0]) return 2;
                x.append(a+offset);
                if(unexpected_growth) return 3;
                if(!equal(a,b,512)) return 4;
                if(x.begin!=a+base || y.begin!=b+base || x.end!=a+finish+24 || y.end!=b+finish+24 || x.capacity_end!=a+400 || y.capacity_end!=b+400) return 5;
            }
        }
    }
    // Null destination skips all source reads and still advances end by 24.
    Record24Storage x={0,0,reinterpret_cast<unsigned char*>(48)};
    Record24Storage y=x;
    original_record24_append_one(&y,0);
    if(test_get_fs_head()!=fs[0]) return 6;
    x.append(0);
    if(x.begin!=y.begin || x.end!=y.end || x.capacity_end!=y.capacity_end || reinterpret_cast<uintptr_t>(x.end)!=24) return 7;
    static const char message[]="record24 append: 12997 cases passed\n";
    test_write(message,sizeof(message)-1);
    return unexpected_growth ? 8 : 0;
}
