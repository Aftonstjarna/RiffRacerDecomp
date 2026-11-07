#include "impl.hpp"
// Game.exe VA 0x438420, RVA 0x38420, size 84. Original is thiscall,
// has no stack arguments and leaves EAX unspecified (no return assignment).
// Direct calls at 0x4d7b2f and 0x4d7b37 initialize two matrix destinations.
// Every word in [this,this+48) is replaced; no imports, allocation or FP math.
// Valid writable object storage is required; null/faulting pointers are outside
// the portable C++ contract. No larger enclosing-object layout is inferred.
void Matrix48::initialize_basis() {
    basis[0][0] = 1.0f;
    basis[0][1] = 0.0f;
    basis[0][2] = 0.0f;
    basis[0][3] = 0.0f;
    basis[1][0] = 0.0f;
    basis[1][1] = 1.0f;
    basis[1][2] = 0.0f;
    basis[1][3] = 0.0f;
    basis[2][0] = 0.0f;
    basis[2][1] = 0.0f;
    basis[2][2] = 1.0f;
    basis[2][3] = 0.0f;
}
