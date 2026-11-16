#ifndef RIFF_COLLISION_FACE_LIST_HPP
#define RIFF_COLLISION_FACE_LIST_HPP
#include <stdint.h>
#if defined(_MSC_VER)
#define RIFF_FASTCALL __fastcall
#elif defined(__i386__)
#define RIFF_FASTCALL __attribute__((fastcall))
#else
#define RIFF_FASTCALL
#endif

// Only the links are identified here; the preceding collision data is opaque.
struct CollisionFace {
    unsigned char opaque[0x30];
    CollisionFace* previous;
    CollisionFace* next;
};
struct CollisionFaceList {
    CollisionFace* head;
    uint32_t count;
    void RIFF_FASTCALL unlink(CollisionFace* face);
};
#endif
