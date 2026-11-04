#pragma once
using U32 = unsigned int;
struct Query;
using QueryRelease = U32 (__attribute__((stdcall)) *)(Query*);
struct QueryVtable {
    void* query_interface;
    void* add_ref;
    QueryRelease release;
};
struct Query { QueryVtable* vtable; };
// Partial owner layout only; names of the six query members remain unknown.
struct QueryOwner {
    unsigned char unknown[0x470];
    Query* queries[2][3];
};
static_assert(__builtin_offsetof(QueryOwner, queries) == 0x470, "query offset");
static_assert(sizeof(Query*) == 4, "original i386 layout");
extern "C" void __attribute__((thiscall)) recovered_query_release(QueryOwner*);
extern "C" void __attribute__((thiscall)) original_query_release(QueryOwner*);
