# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47cfd0,0x47cfe8); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ RECALCULATE_AABB,0x47bf40
.global original_convex_hull_shape_set_scaling
original_convex_hull_shape_set_scaling:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+0x8]
    movdqu xmm0,XMMWORD PTR [eax]
    movdqu XMMWORD PTR [ecx+0xc],xmm0
    call RECALCULATE_AABB
    pop ebp
    ret 0x4
.section .note.GNU-stack,"",@progbits
