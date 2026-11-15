#include "impl.hpp"
namespace riff {
unsigned char* copy_record520_range(const unsigned char* first,
                                   const unsigned char* last,
                                   unsigned char* destination) {
    while (first != last) {
        // REP MOVSD transfers each entire word before writing that word.
        // Byte temporaries retain unaligned access and sub-word overlap behavior
        // without imposing C++ alignment or aliasing requirements on records.
        for (unsigned word = 0; word != 130; ++word) {
            const unsigned char a = first[0], b = first[1];
            const unsigned char c = first[2], d = first[3];
            destination[0] = a; destination[1] = b;
            destination[2] = c; destination[3] = d;
            first += 4;
            destination += 4;
        }
    }
    return destination;
}
}
