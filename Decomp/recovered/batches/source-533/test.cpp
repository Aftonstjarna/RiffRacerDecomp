#include "impl.hpp"
extern "C" uint32_t __attribute__((thiscall)) original_resource_index_acquire(ResourceIndex*, uint32_t);
extern "C" void test_write(const char*, unsigned);
static uint32_t address(const void* p) { return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(p)); }
static bool equal(const void* a, const void* b, unsigned n) {
    const unsigned char* x = static_cast<const unsigned char*>(a);
    const unsigned char* y = static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
static int run(uint32_t span, uint32_t index, uint32_t seed, bool alias) {
    uint32_t entries[10], counts[10], beforeEntries[10], beforeCounts[10];
    for(unsigned i=0;i<10;++i) {
        entries[i] = i == 3 ? 0 : 0x12340000u + i;
        counts[i] = seed+i;
        beforeEntries[i]=entries[i]; beforeCounts[i]=counts[i];
    }
    ResourceIndex obj;
    for(unsigned i=0;i<13;++i) obj.unknown00[i]=0xaabb0000u+i;
    obj.entriesBegin=address(entries+1); obj.entriesEnd=obj.entriesBegin+span;
    obj.unknown3c=0xdeadbeefu; obj.counters=address((alias?entries:counts)+1);
    ResourceIndex before=obj;
    uint32_t got=original_resource_index_acquire(&obj,index);
    uint32_t oracleEntries[10], oracleCounts[10];
    for(unsigned i=0;i<10;++i) {oracleEntries[i]=entries[i];oracleCounts[i]=counts[i];entries[i]=beforeEntries[i];counts[i]=beforeCounts[i];}
    if(!equal(&obj,&before,sizeof(obj))) return 1;
    uint32_t recovered=obj.acquire(index);
    if(got!=recovered || !equal(entries,oracleEntries,sizeof(entries)) || !equal(counts,oracleCounts,sizeof(counts)) || !equal(&obj,&before,sizeof(obj))) return 2;
    uint32_t count=(span>>2)|((span&0x80000000u)?0xc0000000u:0);
    bool valid=index<count;
    for(unsigned i=0;i<10;++i) {
        uint32_t inc=valid && i==index+1 ? 1:0;
        if(entries[i]!=beforeEntries[i]+(alias?inc:0) || counts[i]!=beforeCounts[i]+(alias?0:inc)) return 3;
    }
    if(recovered!=(valid?beforeEntries[index+1]+(alias?1:0):0)) return 4;
    return 0;
}
extern "C" int test_main() {
    const uint32_t spans[]={0,1,3,4,7,8,28,31,0xfffffffcu,0x80000000u,0x7fffffffu};
    const uint32_t indices[]={0,1,2,6,7,0x80000000u,0xffffffffu};
    const uint32_t seeds[]={0,0x7fffffffu,0xfffffffeu,0xffffffffu};
    for(unsigned s=0;s<sizeof(spans)/sizeof(spans[0]);++s)
      for(unsigned i=0;i<sizeof(indices)/sizeof(indices[0]);++i) {
        uint32_t n=(spans[s]>>2)|((spans[s]&0x80000000u)?0xc0000000u:0);
        if(indices[i]<n && indices[i]>=8) continue; // no huge invalid backing accesses
        for(unsigned k=0;k<4;++k) for(unsigned a=0;a<2;++a) {
          int r=run(spans[s],indices[i],seeds[k],a!=0); if(r) return r;
        }
      }
    // Rejected empty table does not touch either null array.
    ResourceIndex empty={};
    if(original_resource_index_acquire(&empty,0)!=0 || empty.acquire(0)!=0) return 5;
    static const char message[]="resource-index-acquire comparisons passed\n";
    test_write(message,sizeof(message)-1);
    return 0;
}
