# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41f4a0.
.intel_syntax noprefix
.code32
.text
.global original_float_cos_precise_bridge
.equ cos_thunk,0x8f8f22
original_float_cos_precise_bridge:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff8
 sub esp,0x8
 movss xmm0,DWORD PTR [ebp+0x8]
 cvtps2pd xmm0,xmm0
 call cos_thunk
 cvtsd2ss xmm0,xmm0
 movss DWORD PTR [esp+0x4],xmm0
 fld DWORD PTR [esp+0x4]
 mov.s esp,ebp
 pop ebp
 ret
