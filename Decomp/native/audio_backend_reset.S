.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58e6f0, complete span through ret at 0x58e74a.
.equ unavailable_backend_table,0xbaf470
.global original_audio_backend_reset
original_audio_backend_reset:
    mov DWORD PTR [ecx+0x6d3c], unavailable_backend_table
    mov DWORD PTR [ecx+0x6d50], 0
    mov DWORD PTR [ecx+0x6d7c], 0
    mov DWORD PTR [ecx+0x6d80], 0
    mov DWORD PTR [ecx+0x6d84], 0
    mov DWORD PTR [ecx+0x6d88], 0
    mov DWORD PTR [ecx+0x6d8c], 0
    mov DWORD PTR [ecx+0x6d90], 0
    mov DWORD PTR [ecx+0x6d40], 0xffffffff
    ret
.section .note.GNU-stack,"",@progbits
