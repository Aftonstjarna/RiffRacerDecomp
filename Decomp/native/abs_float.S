# Mechanically transcribed reference evidence, NOT high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x426cf0..0x426d1b exclusive; neighboring INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_abs_float
original_abs_float:
# cdecl: float at entry ESP+4; result ST(0); caller removes argument.
# EBP preserved; XMM0 clobbered. No calls or conditional branches.
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff8
 sub esp,0x8
 movss xmm0,DWORD PTR [ebp+0x8]
 cvtps2pd xmm0,xmm0
# Original aligned 128-bit constant: two 0x7fffffffffffffff masks.
 andpd xmm0,XMMWORD PTR [absolute_mask]
 cvtpd2ps xmm0,xmm0
 movss DWORD PTR [esp+0x4],xmm0
 fld DWORD PTR [esp+0x4]
 mov.s esp,ebp
 pop ebp
 ret
.equ absolute_mask,0xa071c0
.section .note.GNU-stack,"",@progbits
