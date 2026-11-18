#include "impl.hpp"

WorkerRecord84* worker_record84_move_range(const WorkerRecord84* begin,
                                            const WorkerRecord84* end,
                                            WorkerRecord84* destination) {
    // Integer addresses preserve the original null destination arithmetic.
    uintptr_t src = reinterpret_cast<uintptr_t>(begin);
    const uintptr_t stop = reinterpret_cast<uintptr_t>(end);
    uintptr_t dst = reinterpret_cast<uintptr_t>(destination);
    while (src != stop) {
        if (dst != 0) {
            const unsigned char* s = reinterpret_cast<const unsigned char*>(src);
            unsigned char* d = reinterpret_cast<unsigned char*>(dst);
            // Each of the first three loads precedes its corresponding store;
            // the remaining transfers are four bytes at a time. This matters
            // for overlapping ranges even though the caller uses fresh storage.
            for (unsigned offset = 0; offset < 84;) {
                unsigned n = offset < 48 ? 16 : 4;
                unsigned char temp[16];
                for (unsigned i = 0; i < n; ++i) temp[i] = s[offset + i];
                for (unsigned i = 0; i < n; ++i) d[offset + i] = temp[i];
                offset += n;
            }
        }
        src += 84;
        dst += 84;
    }
    return reinterpret_cast<WorkerRecord84*>(dst);
}
