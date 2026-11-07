# Mechanically transcribed reference evidence, NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4385f0,0x4386ec); sole return included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_matrix_scaled_vector_accumulate
original_matrix_scaled_vector_accumulate:
 push   ebp
 mov.s ebp,esp
 mov    eax,DWORD PTR [ebp+0x8]
 movss  xmm0,DWORD PTR [ecx+0x100]
 movss  xmm6,DWORD PTR [ecx+0x104]
 movss  xmm3,DWORD PTR [ecx+0x114]
 movss  xmm1,DWORD PTR [eax+0x4]
 movss  xmm2,DWORD PTR [eax]
 movss  xmm5,DWORD PTR [eax+0x8]
 mulss  xmm0,xmm2
 movss  xmm4,DWORD PTR [ecx+0x124]
 mulss  xmm6,xmm1
 mulss  xmm3,xmm1
 addss  xmm6,xmm0
 mulss  xmm4,xmm1
 movss  xmm0,DWORD PTR [ecx+0x108]
 mulss  xmm0,xmm5
 movss  xmm1,DWORD PTR [ecx+0x218]
 addss  xmm6,xmm0
 movss  xmm0,DWORD PTR [ecx+0x110]
 mulss  xmm0,xmm2
 addss  xmm3,xmm0
 mulss  xmm1,xmm6
 movss  xmm0,DWORD PTR [ecx+0x118]
 mulss  xmm0,xmm5
 addss  xmm3,xmm0
 movss  xmm0,DWORD PTR [ecx+0x120]
 mulss  xmm0,xmm2
 movss  xmm2,DWORD PTR [ecx+0x21c]
 addss  xmm4,xmm0
 mulss  xmm2,xmm3
 movss  xmm0,DWORD PTR [ecx+0x128]
 movss  xmm3,DWORD PTR [ecx+0x220]
 mulss  xmm0,xmm5
 addss  xmm4,xmm0
 movss  xmm0,DWORD PTR [ecx+0x140]
 addss  xmm0,xmm1
 mulss  xmm3,xmm4
 movss  DWORD PTR [ecx+0x140],xmm0
 movss  xmm0,DWORD PTR [ecx+0x144]
 addss  xmm0,xmm2
 movss  DWORD PTR [ecx+0x144],xmm0
 movss  xmm0,DWORD PTR [ecx+0x148]
 addss  xmm0,xmm3
 movss  DWORD PTR [ecx+0x148],xmm0
 pop    ebp
 ret    0x4
.section .note.GNU-stack,"",@progbits
