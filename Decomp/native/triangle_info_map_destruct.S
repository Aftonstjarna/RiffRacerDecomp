# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4391e0,0x4391ee); INT3 padding excluded.
# ECX=this; reset vptr, then tail-delegate destruction of this+4.
.intel_syntax noprefix
.code32
.text
.equ TRIANGLE_INFO_MAP_VTABLE,0x9f9944
.equ MEMBER_DESTRUCTOR,0x439290
.global original_triangle_info_map_destruct
original_triangle_info_map_destruct:
 mov DWORD PTR [ecx],TRIANGLE_INFO_MAP_VTABLE
 add ecx,4
 jmp MEMBER_DESTRUCTOR
.section .note.GNU-stack,"",@progbits
