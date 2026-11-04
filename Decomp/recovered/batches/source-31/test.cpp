#include "impl.hpp"
extern "C" void test_write(const char*, unsigned);
struct Resource { Query base; unsigned id, calls, remaining; };
struct Fixture { unsigned before[4]; QueryOwner owner; unsigned after[8]; };
struct Event { unsigned id; unsigned slots[6]; unsigned calls; };
static Fixture fixture;
static Resource resources[7];
static Event events[32], saved_events[32];
static unsigned count, mode;
static unsigned saved_calls[7], saved_remaining[7];
static unsigned char saved_fixture[sizeof(Fixture)];
static Query*& slot(unsigned i) { return fixture.owner.queries[i/3][i%3]; }
static unsigned identity(Query* p) {
    if (!p) return 0;
    for (unsigned i=0;i<7;++i) if (p == &resources[i].base) return i+1;
    return 99;
}
static U32 __attribute__((stdcall)) release_query(Query* p) {
    Resource* r = reinterpret_cast<Resource*>(p);
    if (count >= 32) return 0;
    Event& e = events[count++];
    e.id = r->id;
    for (unsigned i=0;i<6;++i) e.slots[i] = identity(slot(i));
    e.calls = ++r->calls;
    --r->remaining;
    if (mode == 1 && count == 1) {
        // Replace the next member, clear another, and populate a future group.
        slot(1) = &resources[6].base;
        slot(0) = nullptr;
        slot(5) = &resources[6].base;
        slot(2) = &resources[0].base; // overwritten after this callback
    }
    if (mode == 2) {
        // Changes to previously cleared slots must survive later iterations.
        if (count == 2) slot(2) = &resources[6].base;
        if (count == 4) slot(0) = &resources[6].base;
        fixture.owner.unknown[17] ^= static_cast<unsigned char>(r->id);
        fixture.after[3] += r->id;
    }
    return r->remaining;
}
static QueryVtable vtable = {nullptr, nullptr, release_query};
static void initialize(unsigned mask, unsigned alias) {
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&fixture);
    for (unsigned i=0;i<sizeof fixture;++i) bytes[i] = static_cast<unsigned char>(i*37+19);
    for (unsigned i=0;i<7;++i) {
        resources[i].base.vtable = &vtable;
        resources[i].id=i+1; resources[i].calls=0; resources[i].remaining=100+i;
    }
    for (unsigned i=0;i<6;++i) slot(i) = (mask & (1u<<i)) ? &resources[alias ? 0 : i].base : nullptr;
    count=0;
    for (auto& e: events) { e.id=0; e.calls=0; for (auto& s:e.slots) s=0; }
}
static bool same_bytes(const void* a, const void* b, unsigned size) {
    auto x=static_cast<const unsigned char*>(a), y=static_cast<const unsigned char*>(b);
    for (unsigned i=0;i<size;++i) if (x[i]!=y[i]) return false;
    return true;
}
static bool run(unsigned mask, unsigned alias, unsigned mutation) {
    mode=mutation;
    initialize(mask,alias);
    original_query_release(&fixture.owner);
    unsigned expected_count=count;
    for (unsigned i=0;i<32;++i) saved_events[i]=events[i];
    for (unsigned i=0;i<sizeof fixture;++i) saved_fixture[i]=reinterpret_cast<unsigned char*>(&fixture)[i];
    for (unsigned i=0;i<7;++i) { saved_calls[i]=resources[i].calls; saved_remaining[i]=resources[i].remaining; }
    if (!mutation) {
        // All bytes outside the six pointer slots retain the initial pattern.
        const unsigned begin = __builtin_offsetof(Fixture, owner) + 0x470;
        const unsigned end = begin + 24;
        const auto bytes = reinterpret_cast<const unsigned char*>(&fixture);
        for (unsigned i=0;i<sizeof fixture;++i)
            if ((i<begin || i>=end) && bytes[i]!=static_cast<unsigned char>(i*37+19)) return false;
        unsigned n=0;
        const unsigned order[6]={2,1,0,5,4,3};
        for (unsigned i:order) if (mask&(1u<<i)) {
            if (events[n++].id != (alias ? 1 : i+1)) return false;
        }
        if (n!=count) return false;
        for (unsigned i=0;i<6;++i) if (slot(i)) return false;
    }
    initialize(mask,alias);
    recovered_query_release(&fixture.owner);
    if (count!=expected_count || !same_bytes(events,saved_events,sizeof events) ||
        !same_bytes(&fixture,saved_fixture,sizeof fixture)) return false;
    for (unsigned i=0;i<7;++i)
        if (resources[i].base.vtable!=&vtable || resources[i].id!=i+1 ||
            resources[i].calls!=saved_calls[i] || resources[i].remaining!=saved_remaining[i]) return false;
    // A second teardown sees no pointers on the ordinary path.
    if (!mutation) { recovered_query_release(&fixture.owner); if (count!=expected_count) return false; }
    return true;
}
extern "C" int test_main() {
    for (unsigned mask=0;mask<64;++mask)
        for (unsigned alias=0;alias<2;++alias)
            for (unsigned mutation=0;mutation<3;++mutation)
                if (!run(mask,alias,mutation)) { test_write("FAIL\n",5); return 1; }
    static const char passed[] = "query-release: 384 differential cases passed\n";
    test_write(passed, sizeof(passed)-1);
    return 0;
}
