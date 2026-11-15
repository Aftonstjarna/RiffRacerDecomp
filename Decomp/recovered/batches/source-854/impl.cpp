#include "impl.hpp"
namespace riff {
String* State::intern(const char* text,uint32_t length,const Services& services) {
    uint32_t hash=length;
    const uint32_t step=(length>>5)+1;
    for(uint32_t i=length;i>=step;i-=step)
        hash^=(hash<<5)+(hash>>2)+static_cast<uint8_t>(text[i-1]);
    Global* captured=global;
    for(String* p=captured->buckets[hash&(captured->capacity-1)];p;p=p->next) {
        if(p->length!=length)continue;
        uint32_t i=0;
        while(i<length && text[i]==p->bytes()[i])++i;
        if(i!=length)continue;
        if((static_cast<uint8_t>(~captured->white)&(p->mark&3))!=0)p->mark^=3;
        return p;
    }
    // Unsigned wrap is intentional, including length == UINT32_MAX.
    if(length+1u>0xffffffedu)services.sizeError(this);
    String* p=static_cast<String*>(services.reallocate(this,0,0,length+17u));
    p->length=length;p->hash=hash;
    p->type=4;p->mark=global->white&3;p->reserved=0;
    // Header byte +7 is deliberately left as returned by the allocator.
    for(uint32_t i=0;i<length;++i)p->bytes()[i]=text[i];
    p->bytes()[length]=0;
    Global* current=global;
    uint32_t bucket=hash&(current->capacity-1);
    p->next=current->buckets[bucket];current->buckets[bucket]=p;
    ++current->count;
    if(current->count>current->capacity && static_cast<int32_t>(current->capacity)<=0x3ffffffe)
        services.resizeBuckets(this,current->capacity*2);
    return p;
}
}
