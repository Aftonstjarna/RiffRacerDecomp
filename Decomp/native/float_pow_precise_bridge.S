# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f2590,0x4f25c0); complete bridge, next function excluded.
.intel_syntax noprefix
.code32
.text
.global original_float_pow_precise_bridge
.equ POW_PRECISE,0x8f8f2e
original_float_pow_precise_bridge:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff8
 sub esp,8
 movss xmm1,DWORD PTR [ebp+0xc]
 movss xmm0,DWORD PTR [ebp+8]
 cvtps2pd xmm0,xmm0
 cvtps2pd xmm1,xmm1
 call POW_PRECISE
 cvtsd2ss xmm0,xmm0
 movss DWORD PTR [esp+4],xmm0
 fld DWORD PTR [esp+4]
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
