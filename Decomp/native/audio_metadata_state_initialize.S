.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58b2c0, complete 59-byte function through RET at 0x58b2fa.
# ECX addresses writable state; byte +7 is deliberately untouched.
.global original_audio_metadata_state_initialize
original_audio_metadata_state_initialize:
    mov DWORD PTR [ecx+0x14],0
    mov DWORD PTR [ecx+0x18],0
    mov DWORD PTR [ecx+0x1c],0
    mov DWORD PTR [ecx+0x8],0
    mov DWORD PTR [ecx+0xc],0
    mov DWORD PTR [ecx+0x10],0
    mov DWORD PTR [ecx+0x3],0
    mov WORD PTR [ecx],0
    mov BYTE PTR [ecx+0x2],0
    ret
