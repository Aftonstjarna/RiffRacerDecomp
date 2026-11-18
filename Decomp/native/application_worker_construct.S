.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x43f310.
.global original_application_worker_construct
original_application_worker_construct:
    push   ebp
    {load} mov    ebp,esp
    push   0xffffffff
    push   0x8fef81
    mov    eax,fs:[0]
    push   eax
    push   ecx
    push   ebx
    push   esi
    push   edi
    mov    eax,DWORD PTR [0xbaabc0]
    {load} xor    eax,ebp
    push   eax
    lea    eax,[ebp-0xc]
    mov    fs:[0],eax
    {load} mov    esi,ecx
    mov    DWORD PTR [ebp-0x10],esi
    mov    DWORD PTR [esi],0x0
    push   0x41f480
    push   0x4223a0
    push   0x14
    push   0x4
    lea    eax,[esi+0x4]
    mov    DWORD PTR [ebp-0x4],0x0
    push   eax
    call target_8f94bf
    mov    DWORD PTR [esi+0x54],0x0
    lea    edi,[esi+0x70]
    mov    DWORD PTR [esi+0x58],0x0
    mov    DWORD PTR [esi+0x5c],0x0
    mov    DWORD PTR [esi+0x60],0x0
    mov    DWORD PTR [esi+0x64],0x0
    mov    DWORD PTR [esi+0x68],0x0
    mov    DWORD PTR [esi+0x6c],0x0
    mov    DWORD PTR [edi+0x14],0xf
    mov    DWORD PTR [edi+0x10],0x0
    mov    BYTE PTR [edi],0x0
    mov    DWORD PTR [esi+0x9c],0xf
    mov    DWORD PTR [esi+0x98],0x0
    mov    BYTE PTR [esi+0x88],0x0
    mov    DWORD PTR [esi+0xb4],0xf
    mov    DWORD PTR [esi+0xb0],0x0
    mov    BYTE PTR [esi+0xa0],0x0
    lea    ecx,[esi+0xb8]
    mov    BYTE PTR [ebp-0x4],0x4
    call target_482bc0
    mov    DWORD PTR [esi+0x128],0x9f9b98
    mov    DWORD PTR [esi+0x12c],0x0
    mov    DWORD PTR [esi+0x130],0x0
    mov    DWORD PTR [esi+0x134],0x0
    mov    edx,DWORD PTR [ebp+0x8]
    mov    BYTE PTR [ebp-0x4],0x6
    mov    WORD PTR [esi+0x138],0x0
    mov    BYTE PTR [esi+0x13a],0x0
    test   edx,edx
    je .L43f460
    cmp    BYTE PTR [edx],0x0
    jne .L43f435
    {load} xor    ecx,ecx
    jmp .L43f449
.L43f435:
    {load} mov    ecx,edx
    lea    ebx,[ecx+0x1]
    {disp32} lea    ebx,[ebx+0x0]
.L43f440:
    mov    al,BYTE PTR [ecx]
    inc    ecx
    test   al,al
    jne .L43f440
    {load} sub    ecx,ebx
.L43f449:
    push   ecx
    push   edx
    {load} mov    ecx,edi
    call target_416520
    push   edi
    call target_43fd50
    push   edi
    {load} mov    ecx,esi
    call target_43fd90
.L43f460:
    {load} mov    ecx,esi
    call target_43f480
    {load} mov    eax,esi
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:[0],ecx
    pop    ecx
    pop    edi
    pop    esi
    pop    ebx
    {load} mov    esp,ebp
    pop    ebp
    ret    0x4
.equ target_416520,0x416520
.equ target_43f480,0x43f480
.equ target_43fd50,0x43fd50
.equ target_43fd90,0x43fd90
.equ target_482bc0,0x482bc0
.equ target_8f94bf,0x8f94bf
