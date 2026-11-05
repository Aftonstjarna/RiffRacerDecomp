# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426f00,0x426f27). Adjacent INT3 padding excluded.
# ECX=destination; three stack pointers; EAX=destination; ret 12.
# Ordered loads/stores preserve original alias behavior; no external dependencies.
.intel_syntax noprefix
.code32
.text
.global original_vector3_construct_refs
original_vector3_construct_refs:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [ecx],eax
 mov eax,DWORD PTR [ebp+12]
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [ecx+4],eax
 mov eax,DWORD PTR [ebp+16]
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [ecx+8],eax
 mov.s eax,ecx
 mov DWORD PTR [ecx+12],0
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
