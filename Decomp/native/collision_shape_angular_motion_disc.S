# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47c1b0,0x47c21f); no embedded data or padding.
.intel_syntax noprefix
.code32
.text
.equ dep_426d60,0x426d60
.equ dep_8f8958,0x8f8958
.global original_collision_shape_angular_motion_disc
original_collision_shape_angular_motion_disc:
    push   ebp
    mov.s    ebp,esp
    and    esp,0xfffffff8
    sub    esp,0x18
    mov    eax,ds:0xbaabc0
    xor.s    eax,esp
    mov    DWORD PTR [esp+0x14],eax
    mov    eax,DWORD PTR [ecx]
    lea    edx,[esp]
    push   edx
    lea    edx,[esp+0x8]
    push   edx
    call   DWORD PTR [eax+0x8]
    movss  xmm0,DWORD PTR [esp+0x8]
    movss  xmm1,DWORD PTR [esp+0x4]
    mulss  xmm0,xmm0
    push   ecx
    mulss  xmm1,xmm1
    addss  xmm1,xmm0
    movss  xmm0,DWORD PTR [esp+0x10]
    mulss  xmm0,xmm0
    addss  xmm1,xmm0
    movss  DWORD PTR [esp],xmm1
    call dep_426d60
    fadd   DWORD PTR [esp+0x4]
    mov    ecx,DWORD PTR [esp+0x18]
    add    esp,0x4
    xor.s    ecx,esp
    fstp   DWORD PTR [esp]
    fld    DWORD PTR [esp]
    call dep_8f8958
    mov.s    esp,ebp
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
