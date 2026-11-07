# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4383e0,0x43840e); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_vector3_dot_sse
original_vector3_dot_sse:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 movss xmm1,DWORD PTR [eax]
 movss xmm0,DWORD PTR [eax+4]
 mulss xmm1,DWORD PTR [ecx]
 mulss xmm0,DWORD PTR [ecx+4]
 addss xmm0,xmm1
 movss xmm1,DWORD PTR [eax+8]
 mulss xmm1,DWORD PTR [ecx+8]
 addss xmm0,xmm1
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
