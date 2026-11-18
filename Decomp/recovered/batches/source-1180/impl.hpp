#ifndef RECOVERED_GC_SHRINK_HPP
#define RECOVERED_GC_SHRINK_HPP
#include <stdint.h>
#include <stddef.h>
struct ScriptGlobal {
    void** buckets; uint32_t used; int32_t bucketCount;
    void* (*allocator)(void*,void*,uint32_t,uint32_t); void* allocatorData;
    uint8_t other[32]; void* buffer; uint8_t gap[4]; uint32_t bufferSize;
};
struct ScriptState;
struct ScriptServices {
    void (*resizeBuckets)(ScriptState*,int32_t);
    void* (*reallocate)(ScriptState*,void*,uint32_t,uint32_t);
};
struct ScriptState {
    uint8_t unknown[16]; ScriptGlobal* global;
    void shrinkBuffers(const ScriptServices& services);
};
static_assert(offsetof(ScriptGlobal,buffer)==0x34,"buffer offset");
static_assert(offsetof(ScriptGlobal,bufferSize)==0x3c,"size offset");
static_assert(offsetof(ScriptState,global)==0x10,"global offset");
#endif
