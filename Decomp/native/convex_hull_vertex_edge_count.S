# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d1c0,0x47d1c4); surrounding INT3 padding excluded.
# Shared hull vertex/edge count vtable accessor: ECX=this, EAX=count.
.intel_syntax noprefix
.code32
.text
.global original_convex_hull_vertex_edge_count
original_convex_hull_vertex_edge_count:
    mov eax,DWORD PTR [ecx+0x5c]
    ret
.section .note.GNU-stack,"",@progbits
