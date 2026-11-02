#ifndef RIFF_SAVE_DEVICE_CLOSE_HPP
#define RIFF_SAVE_DEVICE_CLOSE_HPP
namespace riff {
using CloseStream = int (__attribute__((cdecl)) *)(void*);
// Only the prefix touched by this routine is named. Full object size and the
// meaning of +0xC remain unresolved; do not treat it as a boolean.
struct SaveDevicePrefix {
    unsigned char opaque[12];
    unsigned state;
    void* stream;
};
static_assert(sizeof(unsigned) == 4, "32-bit word required");
static_assert(__builtin_offsetof(SaveDevicePrefix, state) == 12, "state offset");
#if __SIZEOF_POINTER__ == 4
static_assert(__builtin_offsetof(SaveDevicePrefix, stream) == 16, "handle offset");
#endif
// close_stream supplies the platform fclose dependency (cdecl in Game.exe).
// The opaque stream belongs to that runtime; never pass a Windows FILE to Linux.
bool save_device_close(SaveDevicePrefix* device, CloseStream close_stream);
}
#endif
