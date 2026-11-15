# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d530,0x47d555); surrounding INT3 padding excluded.
# Sphere vtable 0x9f987c + 0x3c. ECX=this (unused), stack: result, direction (unused).
# Returns result in EAX, clears all four vector words, callee pops 8 bytes.
.intel_syntax noprefix
.code32
.text
.global original_sphere_support_without_margin
original_sphere_support_without_margin:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 mov DWORD PTR [eax],0
 mov DWORD PTR [eax+4],0
 mov DWORD PTR [eax+8],0
 mov DWORD PTR [eax+12],0
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
