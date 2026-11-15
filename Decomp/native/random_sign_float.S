# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Original VA [0x478810,0x478846); excludes following INT3 padding.
# ECX points to writable 32-bit generator state; scalar result in XMM0.
.intel_syntax noprefix
.code32
.text
.equ NEGATIVE_ONE,0xa068ac
.equ POSITIVE_ONE,0xa06558
.global original_random_sign_float
original_random_sign_float:
    imul edx,DWORD PTR [ecx],0x27
    add edx,0x27a39e8f
    mov DWORD PTR [ecx],edx
    shl DWORD PTR [ecx],0xd
    mov eax,DWORD PTR [ecx]
    sar edx,0x13
    and edx,0x1fff
    or.s eax,edx
    mov DWORD PTR [ecx],eax
    test eax,0x8000
    je positive
    movss xmm0,DWORD PTR [NEGATIVE_ONE]
    ret
positive:
    movss xmm0,DWORD PTR [POSITIVE_ONE]
    ret
.section .note.GNU-stack,"",@progbits
