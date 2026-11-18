#include "impl.hpp"

WorkerString* worker_empty_string_construct(WorkerString* destination) {
    // The original initializes these fields then assigns zero bytes from the
    // literal at 0x9998bc. With capacity 15 and length 0 that helper only
    // repeats the length and terminator writes; it does not read the literal.
    destination->capacity = 15;
    destination->length = 0;
    destination->inline_storage[0] = 0;
    return destination;
}
