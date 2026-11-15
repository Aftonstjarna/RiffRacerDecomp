# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x47cd30,0x47cd36); adjacent INT3 padding excluded.
# btConvexHullShape serialization-size virtual: ECX=this (unused), EAX=68.
.intel_syntax noprefix
.code32
.text
.global original_convex_hull_shape_serialized_size
original_convex_hull_shape_serialized_size:
    mov eax,0x44
    ret
.section .note.GNU-stack,"",@progbits
