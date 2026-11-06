# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426d60,0x426d88); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_sqrt_float_bridge
.equ sqrt_precise_import,0x8f8d60
original_sqrt_float_bridge:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff8
 sub esp,8
 movss xmm0,DWORD PTR [ebp+8]
 cvtps2pd xmm0,xmm0
 call sqrt_precise_import
 cvtsd2ss xmm0,xmm0
 movss DWORD PTR [esp+4],xmm0
 fld DWORD PTR [esp+4]
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
