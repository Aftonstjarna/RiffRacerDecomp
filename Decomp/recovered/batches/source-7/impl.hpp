#ifndef RIFF_SAVE_DEVICE_CLOSE_HPP
#define RIFF_SAVE_DEVICE_CLOSE_HPP
#include <stddef.h>
namespace riff {
#if defined(_MSC_VER)
using CloseStream = int (__cdecl *)(void*);
#else
using CloseStream = int (__attribute__((cdecl)) *)(void*);
#endif
// Only the prefix touched by this routine is named. Full object size and the
// meaning of +0xC remain unresolved; do not treat it as a boolean.
struct SaveDevicePrefix {
    unsigned char opaque[12];
    unsigned state;
    void* stream;
};
static_assert(sizeof(unsigned) == 4, "32-bit word required");
static_assert(offsetof(SaveDevicePrefix, state) == 12, "state offset");
static_assert(sizeof(void*) != 4 || offsetof(SaveDevicePrefix, stream) == 16, "handle offset");
// close_stream supplies the platform fclose dependency (cdecl in Game.exe).
// The opaque stream belongs to that runtime; never pass a Windows FILE to Linux.
bool save_device_close(SaveDevicePrefix* device, CloseStream close_stream);
}
#endif
