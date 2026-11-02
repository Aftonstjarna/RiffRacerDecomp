#include "impl.hpp"
using namespace riff;
extern "C" void test_write(const char*, unsigned);
extern "C" void* memset(void* p, int c, unsigned n) {
    auto b = static_cast<unsigned char*>(p);
    for (unsigned i=0;i<n;++i) b[i]=static_cast<unsigned char>(c);
    return p;
}
extern "C" void* memcpy(void* d, const void* s, unsigned n) {
    auto a=static_cast<unsigned char*>(d);
    auto b=static_cast<const unsigned char*>(s);
    for(unsigned i=0;i<n;++i) a[i]=b[i];
    return d;
}
struct Fixture { RequestOwner owner; unsigned char tail[32]; };
struct Mock { Resource base; unsigned id; unsigned calls; };
struct Event { unsigned id; unsigned char image[sizeof(Fixture)]; };
struct Result { unsigned count; Event events[8]; unsigned calls[4]; unsigned char finalImage[sizeof(Fixture)]; bool returned; };
static Fixture fixture;
static Mock mocks[4];
static Result actual, expected;
static Result* recording;
static unsigned mode;
static Resource*& field(unsigned i) {
    switch(i) {
    case 0: return fixture.owner.resource440;
    case 1: return fixture.owner.resource43c;
    case 2: return fixture.owner.resource448;
    default: return fixture.owner.resource444;
    }
}
static uint32_t __attribute__((stdcall)) releaseMock(Resource* resource) {
    auto m = reinterpret_cast<Mock*>(resource);
    unsigned step=recording->count++;
    if(step>=8) return 0;
    recording->events[step].id=m->id;
    memcpy(recording->events[step].image,&fixture,sizeof(fixture));
    ++m->calls;
    if(mode==1) {
        // Replace future and previously cleared fields during the call.
        for(unsigned j=0;j<4;++j) field(j)=&mocks[(step+j+1)%4].base;
        fixture.owner.unknown000[17] ^= static_cast<unsigned char>(step+1);
        fixture.tail[3]++;
    } else if(mode==2) {
        for(unsigned j=0;j<4;++j) field(j)=nullptr;
    }
    // Varied counts, including zero and high-bit-set values, must be ignored.
    return (m->id&1) ? 0xfedcba98u : 0;
}
static ResourceVtable vtable={nullptr,nullptr,releaseMock};
static void run(Result& result, bool original, unsigned mask, bool alias, unsigned mutation) {
    memset(&result,0,sizeof(result));
    memset(&fixture,0xa5,sizeof(fixture));
    for(unsigned i=0;i<4;++i) {
        mocks[i].base.vtable=&vtable;
        mocks[i].id=i;
        mocks[i].calls=0;
        field(i)=(mask&(1u<<i)) ? &mocks[alias?0:i].base : nullptr;
    }
    recording=&result;
    mode=mutation;
    result.returned=original ? original_request_cleanup(&fixture.owner) : request_cleanup(&fixture.owner);
    for(unsigned i=0;i<4;++i) result.calls[i]=mocks[i].calls;
    memcpy(result.finalImage,&fixture,sizeof(fixture));
}
static bool equal(const void* a,const void* b,unsigned n) {
    auto x=static_cast<const unsigned char*>(a);
    auto y=static_cast<const unsigned char*>(b);
    for(unsigned i=0;i<n;++i) if(x[i]!=y[i]) return false;
    return true;
}
extern "C" int test_main() {
    for(unsigned mutation=0;mutation<3;++mutation)
    for(unsigned alias=0;alias<2;++alias)
    for(unsigned mask=0;mask<16;++mask) {
        run(expected,true,mask,alias,mutation);
        run(actual,false,mask,alias,mutation);
        if(!equal(&actual,&expected,sizeof(actual)) || !actual.returned) return 1;
        if(mutation==0) {
            unsigned step=0;
            for(unsigned i=0;i<4;++i) if(mask&(1u<<i)) {
                if(actual.events[step++].id!=(alias?0:i)) return 2;
            }
            if(step!=actual.count) return 3;
            for(unsigned i=0;i<4;++i) if(field(i)!=nullptr) return 4;
            for(unsigned i=0;i<sizeof(fixture.owner.unknown000);++i)
                if(fixture.owner.unknown000[i]!=0xa5) return 5;
            for(unsigned i=0;i<sizeof(fixture.tail);++i) if(fixture.tail[i]!=0xa5) return 6;
            unsigned before=actual.count;
            if(!request_cleanup(&fixture.owner) || actual.count!=before) return 7;
            if(!original_request_cleanup(&fixture.owner) || actual.count!=before) return 8;
        }
    }
    test_write("request-cleanup: 96 differential cases passed\n",46);
    return 0;
}
