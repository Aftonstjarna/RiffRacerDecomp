# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x47d0c0,0x47d1b9); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_convex_hull_batched_support_without_margin
original_convex_hull_batched_support_without_margin:
    push   ebp
    mov.s    ebp,esp
    and    esp,0xfffffff0
    mov    edx,DWORD PTR [ebp+0x10]
    sub    esp,0x18
    push   esi
    mov.s    esi,ecx
    push   edi
    test   edx,edx
    jle L_47d0ef
    mov    eax,DWORD PTR [ebp+0xc]
    add    eax,0xc
    {disp32} lea    ebx,[ebx+0x0]
L_47d0e0:
    mov    DWORD PTR [eax],0xdd5e0b6b
    lea    eax,[eax+0x10]
    dec    edx
    jne L_47d0e0
    mov    edx,DWORD PTR [ebp+0x10]
L_47d0ef:
    xor.s    edi,edi
    cmp    DWORD PTR [esi+0x5c],edi
    jle L_47d1b1
    xor.s    ecx,ecx
    mov    DWORD PTR [esp+0x1c],edi
    mov    DWORD PTR [esp+0xc],ecx
    jmp L_47d110
    {disp32} lea    esp,[esp+0x0]
    {disp8} lea    ecx,[ecx+0x0]
L_47d110:
    mov    eax,DWORD PTR [esi+0x64]
    movss  xmm2,DWORD PTR [eax+ecx*1]
    movss  xmm3,DWORD PTR [eax+ecx*1+0x4]
    movss  xmm4,DWORD PTR [eax+ecx*1+0x8]
    mulss  xmm2,DWORD PTR [esi+0xc]
    mulss  xmm3,DWORD PTR [esi+0x10]
    mulss  xmm4,DWORD PTR [esi+0x14]
    movss  DWORD PTR [esp+0x10],xmm2
    movss  DWORD PTR [esp+0x14],xmm3
    movss  DWORD PTR [esp+0x18],xmm4
    test   edx,edx
    jle L_47d1a0
    mov    eax,DWORD PTR [ebp+0xc]
    mov    ecx,DWORD PTR [ebp+0x8]
    add    eax,0xc
    movdqa xmm5,XMMWORD PTR [esp+0x10]
    add    ecx,0x8
    jmp L_47d160
    {disp8} lea    ecx,[ecx+0x0]
L_47d160:
    movss  xmm0,DWORD PTR [ecx-0x4]
    movss  xmm1,DWORD PTR [ecx-0x8]
    mulss  xmm0,xmm3
    mulss  xmm1,xmm2
    addss  xmm1,xmm0
    movss  xmm0,DWORD PTR [ecx]
    mulss  xmm0,xmm4
    addss  xmm1,xmm0
    comiss xmm1,DWORD PTR [eax]
    jbe L_47d190
    movdqu XMMWORD PTR [eax-0xc],xmm5
    movss  DWORD PTR [eax],xmm1
L_47d190:
    add    ecx,0x10
    add    eax,0x10
    dec    edx
    jne L_47d160
    mov    ecx,DWORD PTR [esp+0xc]
    mov    edx,DWORD PTR [ebp+0x10]
L_47d1a0:
    inc    edi
    add    ecx,0x10
    mov    DWORD PTR [esp+0xc],ecx
    cmp    edi,DWORD PTR [esi+0x5c]
    jl L_47d110
L_47d1b1:
    pop    edi
    pop    esi
    mov.s    esp,ebp
    pop    ebp
    ret    0xc
.section .note.GNU-stack,"",@progbits
