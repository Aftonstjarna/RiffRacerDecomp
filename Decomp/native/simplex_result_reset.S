.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x546100, exclusive end 0x54612a.
.global original_simplex_result_reset
original_simplex_result_reset:
    mov BYTE PTR [ecx+0x24],0
    mov eax,0xfff0
    mov DWORD PTR [ecx+0x14],0
    mov DWORD PTR [ecx+0x18],0
    mov DWORD PTR [ecx+0x1c],0
    mov DWORD PTR [ecx+0x20],0
    and WORD PTR [ecx+0x10],ax
    ret
.section .note.GNU-stack,"",@progbits
