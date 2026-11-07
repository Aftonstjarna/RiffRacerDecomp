.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level source recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x438420; complete half-open span [0x438420,0x438474).
# ECX points to 48 writable bytes. No stack arguments or dependencies.
.global original_matrix48_initialize_basis
original_matrix48_initialize_basis:
    mov DWORD PTR [ecx],0x3f800000
    mov DWORD PTR [ecx+0x4],0
    mov DWORD PTR [ecx+0x8],0
    mov DWORD PTR [ecx+0xc],0
    mov DWORD PTR [ecx+0x10],0
    mov DWORD PTR [ecx+0x14],0x3f800000
    mov DWORD PTR [ecx+0x18],0
    mov DWORD PTR [ecx+0x1c],0
    mov DWORD PTR [ecx+0x20],0
    mov DWORD PTR [ecx+0x24],0
    mov DWORD PTR [ecx+0x28],0x3f800000
    mov DWORD PTR [ecx+0x2c],0
    ret
.section .note.GNU-stack,"",@progbits
