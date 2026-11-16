#include "impl.hpp"
#include <stddef.h>
#if defined(_M_IX86) || defined(__i386__)
static_assert(offsetof(CollisionFace, previous) == 0x30, "original previous offset");
static_assert(offsetof(CollisionFace, next) == 0x34, "original next offset");
static_assert(offsetof(CollisionFaceList, count) == 4, "original count offset");
#endif

// Game.exe 0x549780..0x5497a9. ECX=list, EDX=face, no stack args.
// Caller 0x54a5a7 uses list at owner+0x2640, then inserts the face into
// another list at owner+0x2648. No allocation, validation or link clearing.
// Keep the ordered reloads: self-linked/overlapping neighbors can modify
// face's links before later steps. A null face is not supported by the original.
void RIFF_FASTCALL CollisionFaceList::unlink(CollisionFace* face) {
    if (face->next)
        face->next->previous = face->previous;
    if (face->previous)
        face->previous->next = face->next;
    if (head == face)
        head = face->next;
    --count; // Original DEC wraps even for an empty/inconsistent list.
}
