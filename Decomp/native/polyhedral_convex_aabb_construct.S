# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x47bec0,0x47bf36); INT3 padding excluded.
# ECX=this (writable through byte 0x54); EAX=this; no stack args.
.intel_syntax noprefix
.code32
.text
.equ POLYHEDRAL_AABB_VTABLE,0x9fb030
.global original_polyhedral_convex_aabb_construct
original_polyhedral_convex_aabb_construct:
    mov DWORD PTR [ecx+4],0x23
    mov.s eax,ecx
    mov DWORD PTR [ecx+8],0
    mov DWORD PTR [ecx+0xc],0x3f800000
    mov DWORD PTR [ecx+0x10],0x3f800000
    mov DWORD PTR [ecx+0x14],0x3f800000
    mov DWORD PTR [ecx+0x18],0
    mov DWORD PTR [ecx+0x2c],0x3d23d70a
    mov DWORD PTR [ecx],POLYHEDRAL_AABB_VTABLE
    mov DWORD PTR [ecx+0x34],0x3f800000
    mov DWORD PTR [ecx+0x38],0x3f800000
    mov DWORD PTR [ecx+0x3c],0x3f800000
    mov DWORD PTR [ecx+0x40],0
    mov DWORD PTR [ecx+0x44],0xbf800000
    mov DWORD PTR [ecx+0x48],0xbf800000
    mov DWORD PTR [ecx+0x4c],0xbf800000
    mov DWORD PTR [ecx+0x50],0
    mov BYTE PTR [ecx+0x54],0
    ret
.section .note.GNU-stack,"",@progbits
