# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47b040,0x47b06e); excludes surrounding INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ TRANSFORM_BOUNDS,0x47aec0
.global original_convex_internal_shape_aabb
original_convex_internal_shape_aabb:
 push ebp
 mov.s ebp,esp
 push esi
 push DWORD PTR [ebp+0x10]
 mov.s esi,ecx
 push DWORD PTR [ebp+0xc]
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+0x28]
 call eax
 mov edx,DWORD PTR [ebp+8]
 lea ecx,[esi+0x1c]
 fstp DWORD PTR [ebp+0x10]
 movss xmm1,DWORD PTR [ebp+0x10]
 call TRANSFORM_BOUNDS
 add esp,8
 pop esi
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
