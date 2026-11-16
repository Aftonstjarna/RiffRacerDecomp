#ifndef RIFF_COLLISION_WORKSPACE_HPP
#define RIFF_COLLISION_WORKSPACE_HPP
#include <stdint.h>
#include <stddef.h>
#if defined(_MSC_VER)
#define RIFF_THISCALL __thiscall
#elif defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
namespace riff {
struct CollisionRecord {
    uint32_t unknown_payload[12];
    CollisionRecord* previous;
    CollisionRecord* next;
    uint32_t unknown_tail;
};
struct CollisionWorkspace {
    uint32_t mode;
    unsigned char unknown_04[0x24];
    uint32_t cleared_28[4];
    uint32_t cleared_38;
    unsigned char unknown_3c[0x800];
    CollisionRecord records[128];
    uint32_t cleared_263c;
    uint32_t unknown_2640[2];
    CollisionRecord* free_head;
    uint32_t free_count;
    void RIFF_THISCALL linkFreeRecords();
};
#if UINTPTR_MAX == UINT32_MAX
static_assert(sizeof(CollisionRecord) == 0x3c, "original record stride");
static_assert(offsetof(CollisionWorkspace, records) == 0x83c, "record array");
static_assert(offsetof(CollisionWorkspace, free_head) == 0x2648, "free head");
static_assert(offsetof(CollisionWorkspace, free_count) == 0x264c, "free count");
static_assert(sizeof(CollisionWorkspace) == 0x2650, "observed extent");
#endif
}
#endif
