#include "impl.hpp"
namespace riff {
void State::resizeStringBuckets(uint32_t count,const Services& services) {
    if(global->gcState==2) return;
    String** replacement;
    // Unsigned addition and multiplication wrap exactly as the x86 instructions.
    // UINT32_MAX passes this check; signed loop tests below skip initialization.
    if(count+1u>0x3fffffffu)
        replacement=static_cast<String**>(services.allocationTooLarge(this));
    else
        replacement=static_cast<String**>(services.reallocate(this,0,0,count*4u));
    // Allocation callbacks may change this->global. The original reloads it here.
    Global* captured=global;
    if(static_cast<int32_t>(count)>0) {
        for(uint32_t i=0;i<count;++i) replacement[i]=0;
    }
    for(int32_t i=0;i<static_cast<int32_t>(captured->capacity);++i) {
        String* node=captured->buckets[i];
        while(node) {
            String* next=node->next;
            uint32_t bucket=node->hash&(count-1u);
            node->next=replacement[bucket];
            replacement[bucket]=node;
            node=next;
        }
    }
    // Old buckets and capacity remain published during the free callback.
    // Keep the captured global even if that callback switches this->global.
    services.reallocate(this,captured->buckets,captured->capacity*4u,0);
    captured->buckets=replacement;
    captured->capacity=count;
}
// Call evidence: 0x485150 initializes 32 buckets, 0x4f1b79 requests
// signed capacity/2 during collection, 0x4f5fbc doubles capacity on intern growth.
// No power-of-two validation is performed here; hash masking is unconditional.
}
