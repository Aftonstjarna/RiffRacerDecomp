.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438d20,0x438d26); surrounding INT3 padding excluded.
# Shared constant-twelve leaf; box vtable 0x9f98d0 + 0x54 (edge count).
.global original_box_shape_edge_count
original_box_shape_edge_count:
    mov eax, 12
    ret
.section .note.GNU-stack,"",@progbits
