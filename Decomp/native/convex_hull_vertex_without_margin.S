.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x47d280, complete 84-byte function, exclusive end 0x47d2d4.
.global original_convex_hull_vertex_without_margin
original_convex_hull_vertex_without_margin:
    push ebp
    mov.s ebp, esp
    sub esp, 0x10
    mov eax, DWORD PTR [ebp+8]
    movss xmm0, DWORD PTR [ecx+0xc]
    shl eax, 4
    add eax, DWORD PTR [ecx+0x64]
    mov DWORD PTR [ebp-4], 0
    mulss xmm0, DWORD PTR [eax]
    movss DWORD PTR [ebp-0x10], xmm0
    movss xmm0, DWORD PTR [ecx+0x10]
    mulss xmm0, DWORD PTR [eax+4]
    movss DWORD PTR [ebp-0xc], xmm0
    movss xmm0, DWORD PTR [ecx+0x14]
    mulss xmm0, DWORD PTR [eax+8]
    mov eax, DWORD PTR [ebp+0xc]
    movss DWORD PTR [ebp-8], xmm0
    movdqu xmm0, XMMWORD PTR [ebp-0x10]
    movdqu XMMWORD PTR [eax], xmm0
    mov.s esp, ebp
    pop ebp
    ret 8
