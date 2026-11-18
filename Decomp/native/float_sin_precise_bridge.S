.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41f4d0.
.equ SIN_THUNK,0x8f8f34
.global original_float_sin_precise_bridge
original_float_sin_precise_bridge:
    push ebp
    {load} mov ebp,esp
    and esp,0xfffffff8
    sub esp,8
    movss xmm0,DWORD PTR [ebp+8]
    cvtps2pd xmm0,xmm0
    call SIN_THUNK
    cvtsd2ss xmm0,xmm0
    movss DWORD PTR [esp+4],xmm0
    fld DWORD PTR [esp+4]
    {load} mov esp,ebp
    pop ebp
    ret
