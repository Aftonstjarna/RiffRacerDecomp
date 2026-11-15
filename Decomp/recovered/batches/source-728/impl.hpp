#ifndef RIFF_PAGE_HEADER_HPP
#define RIFF_PAGE_HEADER_HPP
#include <stdint.h>
#if defined(__GNUC__) && defined(__i386__)
#define RIFF_THISCALL __attribute__((thiscall))
#else
#define RIFF_THISCALL
#endif
// Partial view only: the original object has a header pointer at offset zero.
// No claim is made about the size or meaning of subsequent object fields.
struct PageHeaderView {
    const uint8_t* header;
    uint32_t RIFF_THISCALL stream_id_le32() const;
};
#endif
