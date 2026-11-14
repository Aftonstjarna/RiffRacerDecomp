.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, NOT high-level source recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x0047b640..0x0047b6b5 inclusive; original RTTI names
# btConvexInternalAabbCachingShape. ECX=this, EAX=this; no stack args.
# Immediate vtable address is preserved evidence, not an embedded data table.
.equ ORIGINAL_VTABLE,0x009fafdc
.global original_convex_aabb_caching_shape_construct
original_convex_aabb_caching_shape_construct:
    mov DWORD PTR [ecx+0x04],0x23
    {load} mov eax,ecx
    mov DWORD PTR [ecx+0x08],0
    mov DWORD PTR [ecx+0x0c],0x3f800000
    mov DWORD PTR [ecx+0x10],0x3f800000
    mov DWORD PTR [ecx+0x14],0x3f800000
    mov DWORD PTR [ecx+0x18],0
    mov DWORD PTR [ecx+0x2c],0x3d23d70a
    mov DWORD PTR [ecx],ORIGINAL_VTABLE
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
