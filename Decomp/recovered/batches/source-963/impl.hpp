#ifndef RIFF_AUDIO_METADATA_STATE_HPP
#define RIFF_AUDIO_METADATA_STATE_HPP
#include <stdint.h>
#include <stddef.h>
#ifdef _MSC_VER
#define RIFF_THISCALL __thiscall
#else
#define RIFF_THISCALL __attribute__((thiscall))
#endif
// 0x58b2c0 (RVA 0x18b2c0), 59 bytes. Field meanings remain unresolved.
// Packed prefix reflects the original unaligned DWORD at +3. Byte +7 is
// deliberately preserved, whether it is padding or a live field.
#pragma pack(push, 1)
struct AudioMetadataState {
    uint16_t field_00;
    uint8_t field_02;
    uint32_t field_03;
    uint8_t preserved_07;
    uint32_t field_08;
    uint32_t field_0c;
    uint32_t field_10;
    uint32_t field_14;
    uint32_t field_18;
    uint32_t field_1c;
    void RIFF_THISCALL initialize();
};
#pragma pack(pop)
static_assert(sizeof(AudioMetadataState) == 32, "original state extent");
static_assert(offsetof(AudioMetadataState, field_03) == 3, "packed prefix");
static_assert(offsetof(AudioMetadataState, preserved_07) == 7, "untouched byte");
static_assert(offsetof(AudioMetadataState, field_08) == 8, "first triple");
static_assert(offsetof(AudioMetadataState, field_14) == 20, "second triple");
#endif
