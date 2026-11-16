#include "impl.hpp"
// VA 0x58e6f0, 91 bytes. ECX is the object, no stack arguments, plain RET.
// Caller 0x58a553 passes its own ECX through during broader initialization.
// No return value is defined: EAX is untouched. No cleanup or pointee access.
// Table 0xbaf470 contains mostly 0x58e5b0 callbacks (record error 0x18
// at callback argument+0x6ed8 and return -1), and 0x413f10 entries.
// Only table selection is in scope; those callbacks are not reconstructed.
// Neutral field names avoid asserting unrecovered ownership/state meanings.
void RIFF_THISCALL AudioBackendState::reset() {
    backendTableAddress = 0x00baf470u;
    state6d50 = 0;
    state6d7c = 0;
    state6d80 = 0;
    state6d84 = 0;
    state6d88 = 0;
    state6d8c = 0;
    state6d90 = 0;
    state6d40 = -1;
}
// Valid writable object storage is required. Null/short/read-only objects fault
// in the original; this recovery adds no validation or resource destruction.
