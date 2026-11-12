.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete function VA [0x438d10,0x438d16); INT3 padding excluded.
# Box vtable 0x9f98d0 + 0x50: vertex count, EAX=8. No object read.
.global original_box_shape_vertex_count
original_box_shape_vertex_count:
    mov eax, 8
    ret
.section .note.GNU-stack,"",@progbits
