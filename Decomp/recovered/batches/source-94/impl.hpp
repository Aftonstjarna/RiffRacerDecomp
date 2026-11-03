#ifndef QUERY_CREATE_IMPL_HPP
#define QUERY_CREATE_IMPL_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RR_STDCALL __stdcall
#define RR_THISCALL __thiscall
#else
#define RR_STDCALL __attribute__((stdcall))
#define RR_THISCALL __attribute__((thiscall))
#endif
struct Query;
struct Device;
typedef uint32_t (RR_STDCALL *ReleaseQuery)(Query*);
typedef int32_t (RR_STDCALL *CreateQuery)(Device*, uint32_t, Query**);
struct QueryVtable { void* reserved[2]; ReleaseQuery release; };
struct Query { QueryVtable* vtable; };
struct DeviceVtable { void* reserved[118]; CreateQuery createQuery; };
struct Device { DeviceVtable* vtable; };
// Partial original owner layout. Query purpose/names beyond API types unresolved.
struct QueryOwner {
    unsigned char unknown0[0x78];
    Device* device;
    unsigned char unknown7c[0x470-0x7c];
    Query* queries[2][3];
    void RR_THISCALL createQueries();
private:
    void RR_THISCALL clearQueries();
};
static_assert(sizeof(void*) == 4, "original layout requires 32-bit pointers");
static_assert(offsetof(QueryOwner, device) == 0x78, "device offset");
static_assert(offsetof(QueryOwner, queries) == 0x470, "query offset");
#endif
