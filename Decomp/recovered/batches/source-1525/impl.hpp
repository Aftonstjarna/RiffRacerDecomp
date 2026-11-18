#ifndef WORKER_VIEW_RANGE_HPP
#define WORKER_VIEW_RANGE_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define VIEW_THISCALL __thiscall
#define VIEW_STDCALL __stdcall
#elif defined(__i386__)
#define VIEW_THISCALL __attribute__((thiscall))
#define VIEW_STDCALL __attribute__((stdcall))
#else
#define VIEW_THISCALL
#define VIEW_STDCALL
#endif
// The first table's second word is a byte displacement to the counted object.
struct ViewTable { void* unknown; int32_t counted_offset; };
struct CountedView;
typedef void (VIEW_THISCALL *ViewDestroy)(CountedView*, unsigned);
struct CountedViewTable { ViewDestroy destroy; };
struct CountedView { CountedViewTable* table; uint32_t references; };
struct WorkerView { ViewTable* table; };
void VIEW_STDCALL worker_view_pointer_range_destroy(WorkerView** first, WorkerView** last);
#endif
