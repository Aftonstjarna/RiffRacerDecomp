# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47b100,0x47b167); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ ABS_FLOAT,0x426cf0
.global original_convex_internal_shape_set_scaling
original_convex_internal_shape_set_scaling:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff0
 sub esp,0x18
 push esi
 mov esi,DWORD PTR [ebp+0x8]
 push edi
 push ecx
 mov.s edi,ecx
 movss xmm0,DWORD PTR [esi]
 movss DWORD PTR [esp],xmm0
 call ABS_FLOAT
 movss xmm0,DWORD PTR [esi+0x4]
 fstp DWORD PTR [esp+0x14]
 movss DWORD PTR [esp],xmm0
 call ABS_FLOAT
 movss xmm0,DWORD PTR [esi+0x8]
 fstp DWORD PTR [esp+0x18]
 movss DWORD PTR [esp],xmm0
 call ABS_FLOAT
 fstp DWORD PTR [esp+0x1c]
 add esp,0x4
 mov DWORD PTR [esp+0x1c],0x0
 movdqu xmm0,XMMWORD PTR [esp+0x10]
 movdqu XMMWORD PTR [edi+0xc],xmm0
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret 0x4
.section .note.GNU-stack,"",@progbits
