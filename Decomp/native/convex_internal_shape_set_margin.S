.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x438830,0x438841); adjacent INT3 padding excluded.
.global original_convex_internal_shape_set_margin
original_convex_internal_shape_set_margin:
    push ebp
    {load} mov ebp, esp
    movss xmm0, DWORD PTR [ebp+8]
    movss DWORD PTR [ecx+0x2c], xmm0
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
