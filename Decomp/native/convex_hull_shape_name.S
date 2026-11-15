# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47cd20,0x47cd26). INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ convex_name,0x9fb0f0
.global original_convex_hull_shape_name
original_convex_hull_shape_name:
    mov eax,convex_name
    ret
.section .note.GNU-stack,"",@progbits
