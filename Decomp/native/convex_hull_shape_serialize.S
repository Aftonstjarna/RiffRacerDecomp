.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; NOT high-level source recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x47d2e0, end exclusive 0x47d383. See original.dis and inspection.txt.
.equ base_serialize,0x438870
.global original_convex_hull_shape_serialize
original_convex_hull_shape_serialize:
    push   ebp
    {load} mov    ebp,esp
    push   ebx
    mov    ebx,DWORD PTR [ebp+0xc]
    push   esi
    push   edi
    push   ebx
    push   DWORD PTR [ebp+0x8]
    {load} mov    edi,ecx
    call base_serialize
    mov    eax,DWORD PTR [ebp+0x8]
    mov    esi,DWORD PTR [edi+0x5c]
    mov    DWORD PTR [eax+0x3c],esi
    test   esi,esi
    je L_47d312
    mov    eax,DWORD PTR [ebx]
    {load} mov    ecx,ebx
    push   DWORD PTR [edi+0x64]
    call   DWORD PTR [eax+0x18]
    {load} mov    ecx,eax
    mov    eax,DWORD PTR [ebp+0x8]
    jmp L_47d314
L_47d312:
    {load} xor    ecx,ecx
L_47d314:
    mov    DWORD PTR [eax+0x34],ecx
    mov    DWORD PTR [eax+0x38],0x0
    test   esi,esi
    je L_47d377
    mov    eax,DWORD PTR [ebx]
    {load} mov    ecx,ebx
    push   esi
    push   0x10
    call   DWORD PTR [eax+0xc]
    mov    DWORD PTR [ebp+0x8],eax
    mov    edx,DWORD PTR [eax+0x8]
    test   esi,esi
    jle L_47d360
    {load} xor    ebx,ebx
L_47d338:
    mov    ecx,DWORD PTR [edi+0x64]
    lea    edx,[edx+0x10]
    {load} add    ecx,ebx
    add    ebx,0x10
    mov    eax,DWORD PTR [ecx]
    mov    DWORD PTR [edx-0x10],eax
    mov    eax,DWORD PTR [ecx+0x4]
    mov    DWORD PTR [edx-0xc],eax
    mov    eax,DWORD PTR [ecx+0x8]
    mov    DWORD PTR [edx-0x8],eax
    mov    eax,DWORD PTR [ecx+0xc]
    mov    DWORD PTR [edx-0x4],eax
    dec    esi
    jne L_47d338
    mov    ebx,DWORD PTR [ebp+0xc]
L_47d360:
    push   DWORD PTR [edi+0x64]
    mov    eax,DWORD PTR [ebx]
    {load} mov    ecx,ebx
    push   0x59415241
    push   0x9fb0f8
    push   DWORD PTR [ebp+0x8]
    call   DWORD PTR [eax+0x10]
L_47d377:
    pop    edi
    pop    esi
    mov    eax,0x9fb10c
    pop    ebx
    pop    ebp
    ret    0x8
.section .note.GNU-stack,"",@progbits
