# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d1d0,0x47d27b), excluding INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_convex_hull_edge_without_margin
original_convex_hull_edge_without_margin:
    push ebp
    mov.s ebp,esp
    sub esp,0x10
    push esi
    mov esi,DWORD PTR [ebp+0x8]
    mov.s eax,esi
    cdq
    push edi
    mov edi,DWORD PTR [ecx+0x5c]
    idiv edi
    movss xmm0,DWORD PTR [ecx+0xc]
    mov eax,DWORD PTR [ebp+0xc]
    shl edx,0x4
    add edx,DWORD PTR [ecx+0x64]
    mov DWORD PTR [ebp-0x4],0x0
    mulss xmm0,DWORD PTR [edx]
    movss DWORD PTR [ebp-0x10],xmm0
    movss xmm0,DWORD PTR [ecx+0x10]
    mulss xmm0,DWORD PTR [edx+0x4]
    movss DWORD PTR [ebp-0xc],xmm0
    movss xmm0,DWORD PTR [ecx+0x14]
    mulss xmm0,DWORD PTR [edx+0x8]
    movss DWORD PTR [ebp-0x8],xmm0
    movdqu xmm0,XMMWORD PTR [ebp-0x10]
    mov DWORD PTR [ebp-0x4],0x0
    movdqu XMMWORD PTR [eax],xmm0
    lea eax,[esi+0x1]
    movss xmm0,DWORD PTR [ecx+0xc]
    cdq
    idiv edi
    mov eax,DWORD PTR [ebp+0x10]
    shl edx,0x4
    add edx,DWORD PTR [ecx+0x64]
    pop edi
    pop esi
    mulss xmm0,DWORD PTR [edx]
    movss DWORD PTR [ebp-0x10],xmm0
    movss xmm0,DWORD PTR [ecx+0x10]
    mulss xmm0,DWORD PTR [edx+0x4]
    movss DWORD PTR [ebp-0xc],xmm0
    movss xmm0,DWORD PTR [ecx+0x14]
    mulss xmm0,DWORD PTR [edx+0x8]
    movss DWORD PTR [ebp-0x8],xmm0
    movdqu xmm0,XMMWORD PTR [ebp-0x10]
    movdqu XMMWORD PTR [eax],xmm0
    mov.s esp,ebp
    pop ebp
    ret 0xc
.section .note.GNU-stack,"",@progbits
