.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA span [0x4391d0,0x4391d7); padding excluded.
.equ COLLISION_SHAPE_VTABLE,0x9fb0b8
.global original_collision_shape_vtable_reset
original_collision_shape_vtable_reset:
    mov DWORD PTR [ecx],COLLISION_SHAPE_VTABLE
    ret
