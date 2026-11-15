#include "impl.hpp"
#include <stddef.h>
extern "C" uint32_t __attribute__((fastcall)) original_script_table_count_array_histogram(const riff::ScriptTable*, uint32_t*);
static riff::ScriptArraySlot slots[65538], saved[65538];
static uint32_t a[31], b[31];
static bool equalBytes(const void* x, const void* y, unsigned n) {
    const unsigned char* p = static_cast<const unsigned char*>(x);
    const unsigned char* q = static_cast<const unsigned char*>(y);
    for (unsigned i=0;i<n;++i) if (p[i]!=q[i]) return false;
    return true;
}
static int check(int32_t size, unsigned pattern) {
    riff::ScriptTable table;
    for (unsigned i=0;i<3;++i) {
        table.unknown00[i]=0x12345678u+i;
        table.unknown10[i]=0x87654321u-i;
    }
    table.array=size>0 ? slots : 0;
    table.arraySize=size;
    riff::ScriptTable before=table;
    for (unsigned i=0;i<65538;++i) {
        slots[i].payload=(i&1)?0:0xffffffffu;
        slots[i].tag=pattern==0?0:pattern==1?1:pattern==2?0x80000000u:((i*17+3)%7==0?0:0xffffffffu);
        saved[i]=slots[i];
    }
    for (unsigned i=0;i<31;++i) a[i]=b[i]=0xfffffff0u+i;
    uint32_t expected=0;
    uint32_t bins[27]={0};
    for (int32_t i=0;i<size;++i) if (slots[i].tag) {
        ++expected;
        unsigned bucket=0, limit=1;
        while (static_cast<uint32_t>(i+1)>limit) { ++bucket; limit*=2; }
        ++bins[bucket];
    }
    uint32_t x=table.countArrayHistogram(a+2);
    uint32_t y=original_script_table_count_array_histogram(&table,b+2);
    if (x!=y || x!=expected) return 1;
    if (!equalBytes(a,b,sizeof(a))) return 2;
    for (unsigned i=0;i<31;++i) {
        uint32_t want=0xfffffff0u+i;
        if (i>=2 && i<29) want+=bins[i-2];
        if (a[i]!=want) return 3;
    }
    if (!equalBytes(&table,&before,sizeof(table))) return 4;
    if (!equalBytes(slots,saved,sizeof(slots))) return 5;
    return 0;
}
extern "C" int test_main() {
    static_assert(offsetof(riff::ScriptTable,array)==12,"array offset");
    static_assert(offsetof(riff::ScriptTable,arraySize)==28,"size offset");
    const int32_t sizes[]={(-2147483647-1),-1,0,1,2,3,4,5,7,8,9,15,16,17,31,32,33,255,256,257,1023,1024,1025,65535,65536,65537};
    for(unsigned i=0;i<sizeof(sizes)/sizeof(sizes[0]);++i)
        for(unsigned p=0;p<4;++p) { int r=check(sizes[i],p); if(r) return r; }
    riff::ScriptTable empty={};
    if(empty.countArrayHistogram(0)!=0 || original_script_table_count_array_histogram(&empty,0)!=0) return 6;
    return 0;
}
