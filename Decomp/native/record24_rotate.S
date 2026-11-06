.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x5434f0, complete function through 0x5435f6.
.global original_record24_rotate
original_record24_rotate:
# ECX=first, EDX=middle, [ESP+4]=last; caller cleans stack.
# Compute record counts and their gcd, then swap 16+8-byte records in cycles.
# GAS {load}/{disp32} retain original direction/displacement encodings.
    push   ebp
    {load} mov    ebp,esp
    sub    esp,0x14
    push   ebx
    push   esi
    {load} mov    esi,ecx
    mov    eax,0x2aaaaaab
    {load} mov    ecx,DWORD PTR [ebp+0x8]
    {load} sub    edx,esi
    imul   edx
    {load} sub    ecx,esi
    mov    DWORD PTR [ebp-0xc],esi
    sar    edx,0x2
    {load} mov    eax,edx
    shr    eax,0x1f
    {load} add    eax,edx
    mov    DWORD PTR [ebp-0x4],eax
    mov    eax,0x2aaaaaab
    imul   ecx
    push   edi
    sar    edx,0x2
    {load} mov    edi,edx
    shr    edi,0x1f
    {load} add    edi,edx
    {load} mov    edx,DWORD PTR [ebp-0x4]
    mov    DWORD PTR [ebp-0x8],edi
    {load} mov    ebx,edi
    {load} mov    ecx,edx
    test   edx,edx
    je     L_54354b
L_543538:
    {load} mov    eax,ebx
    {load} mov    ebx,ecx
    cdq
    idiv   ecx
    {load} mov    ecx,edx
    test   edx,edx
    jne    L_543538
    {load} mov    edx,DWORD PTR [ebp-0x4]
    mov    DWORD PTR [ebp-0x8],ebx
L_54354b:
    {load} cmp    ebx,edi
    jge    L_5435f0
    test   ebx,ebx
    jle    L_5435f0
    lea    ecx,[edx+edx*2]
    shl    ecx,0x3
    lea    eax,[ebx+ebx*2]
    mov    DWORD PTR [ebp-0x10],ecx
    lea    edi,[esi+eax*8]
    {disp32} lea    ebx,[ebx+0x0]
L_543570:
    {load} mov    edx,DWORD PTR [ebp+0x8]
    {load} add    ecx,edi
    {load} mov    ebx,DWORD PTR [ebp-0x10]
    {load} cmp    ecx,edx
    {load} mov    eax,edi
    cmove  ecx,esi
    nop
L_543580:
    movdqu xmm0,XMMWORD PTR [ecx]
    {load} sub    edx,ecx
    mov    DWORD PTR [ebp-0x14],ecx
    movdqu xmm1,XMMWORD PTR [eax]
    movq   xmm2,QWORD PTR [eax+0x10]
    movdqu XMMWORD PTR [eax],xmm0
    movq   xmm0,QWORD PTR [ecx+0x10]
    movq   QWORD PTR [eax+0x10],xmm0
    mov    eax,0x2aaaaaab
    imul   edx
    movdqu XMMWORD PTR [ecx],xmm1
    movq   QWORD PTR [ecx+0x10],xmm2
    sar    edx,0x2
    {load} mov    esi,edx
    shr    esi,0x1f
    {load} add    esi,edx
    {load} mov    edx,DWORD PTR [ebp-0x4]
    {load} cmp    edx,esi
    jge    L_5435c8
    {load} mov    esi,DWORD PTR [ebp-0xc]
    {load} add    ecx,ebx
    jmp    L_5435d5
L_5435c8:
    {load} mov    eax,edx
    {load} sub    eax,esi
    {load} mov    esi,DWORD PTR [ebp-0xc]
    lea    eax,[eax+eax*2]
    lea    ecx,[esi+eax*8]
L_5435d5:
    {load} mov    eax,DWORD PTR [ebp-0x14]
    {load} mov    edx,DWORD PTR [ebp+0x8]
    {load} cmp    ecx,edi
    jne    L_543580
    {load} mov    ebx,DWORD PTR [ebp-0x8]
    sub    edi,0x18
    {load} mov    ecx,DWORD PTR [ebp-0x10]
    dec    ebx
    mov    DWORD PTR [ebp-0x8],ebx
    test   ebx,ebx
    jg     L_543570
L_5435f0:
    pop    edi
    pop    esi
    pop    ebx
    {load} mov    esp,ebp
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
