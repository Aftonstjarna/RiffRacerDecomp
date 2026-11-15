# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x478890, complete 98-byte function; no branches or calls.
.intel_syntax noprefix
.code32
.text
.equ conversion_bias,0xa071b0
.equ random_denominator,0xa0684c
.global original_random_range_float
original_random_range_float:
 push ebp
 {load} mov ebp,esp
 imul edx,DWORD PTR [ecx],0x27
 add edx,0x27a39e8f
 mov DWORD PTR [ecx],edx
 shl DWORD PTR [ecx],0xd
 mov eax,DWORD PTR [ecx]
 sar edx,0x13
 and edx,0x1fff
 {load} or eax,edx
 mov DWORD PTR [ecx],eax
 movzx eax,ax
 movd xmm0,eax
 cvtdq2pd xmm0,xmm0
 shr eax,0x1f
 addsd xmm0,QWORD PTR [eax*8+conversion_bias]
 cvtpd2ps xmm2,xmm0
 movss xmm0,DWORD PTR [ebp+0xc]
 divss xmm2,DWORD PTR [random_denominator]
 subss xmm0,DWORD PTR [ebp+0x8]
 mulss xmm2,xmm0
 addss xmm2,DWORD PTR [ebp+0x8]
 movss DWORD PTR [ebp+0xc],xmm2
 fld DWORD PTR [ebp+0xc]
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
