#include "impl.hpp"
namespace riff {
// Original VA 0x43fd50, 56 bytes. The end is recomputed each iteration.
// No allocation, terminator scan, metadata update or error handling occurs.
// EAX happens to contain end() on return; no semantic return is established.
void RIFF_STDCALL normalize_path_slashes(NarrowString* path) {
    char* cursor = path->data();
    while (cursor != path->data() + path->length) {
        if (*cursor == '\\')
            *cursor = '/';
        ++cursor;
    }
}
}
