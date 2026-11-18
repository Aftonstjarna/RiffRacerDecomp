.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4b53c0.
.global original_allocator_statistics_snapshot
original_allocator_statistics_snapshot:
    push   ebp
    {load} mov    ebp,esp
    sub    esp,0x8
    xorps  xmm0,xmm0
    push   esi
    mov    esi,DWORD PTR [ebp+0x8]
    push   0xbfcbd0
    movdqu XMMWORD PTR [esi],xmm0
    movq   QWORD PTR [esi+0x10],xmm0
    call   DWORD PTR [0x92d024]
    cmp    DWORD PTR [0xc00b78],0x0
    jne .L4b53fe
    push   0xbfcbd0
    call   DWORD PTR [0x92d028]
    {load} mov    eax,esi
    pop    esi
    {load} mov    esp,ebp
    pop    ebp
    ret    0x4
.L4b53fe:
    mov    edx,DWORD PTR [0xc00d0c]
    {load} mov    eax,edx
    push   edi
    mov    edi,DWORD PTR [0xc00b6c]
    add    edi,0x20
    mov    DWORD PTR [ebp-0x8],0x1
    mov    DWORD PTR [ebp-0x4],edi
    and    eax,0x7
    je .L4b5424
    neg    eax
    and    eax,0x7
.L4b5424:
    lea    ecx,[eax+edx*1]
    {load} cmp    ecx,edx
    jb .L4b5479
    mov    eax,[0xc00d10]
    mov    esi,0x1
    {load} add    eax,edx
    mov    DWORD PTR [ebp-0x8],eax
    {disp32} lea    ebx,[ebx+0x0]
.L4b5440:
    {load} cmp    ecx,eax
    jae .L4b5473
    cmp    ecx,DWORD PTR [0xc00b78]
    je .L4b5473
    mov    eax,DWORD PTR [ecx+0x4]
    cmp    eax,0x7
    je .L4b5473
    {load} mov    edx,eax
    and    edx,0xfffffffc
    add    DWORD PTR [ebp-0x4],edx
    test   al,0x2
    jne .L4b5463
    {load} add    edi,edx
    inc    esi
.L4b5463:
    and    eax,0xfffffffc
    {load} add    ecx,eax
    mov    eax,DWORD PTR [ebp-0x8]
    cmp    ecx,DWORD PTR [0xc00d0c]
    jae .L4b5440
.L4b5473:
    mov    DWORD PTR [ebp-0x8],esi
    mov    esi,DWORD PTR [ebp+0x8]
.L4b5479:
    mov    eax,DWORD PTR [ebp-0x8]
    mov    ecx,DWORD PTR [0xc00d04]
    mov    edx,DWORD PTR [ebp-0x4]
    mov    DWORD PTR [esi+0x4],eax
    {load} mov    eax,ecx
    {load} sub    eax,edx
    mov    DWORD PTR [esi],edx
    mov    DWORD PTR [esi+0x8],eax
    {load} sub    ecx,edi
    mov    eax,[0xc00d08]
    push   0xbfcbd0
    mov    DWORD PTR [esi+0xc],eax
    mov    DWORD PTR [esi+0x10],ecx
    mov    DWORD PTR [esi+0x14],edi
    call   DWORD PTR [0x92d028]
    pop    edi
    {load} mov    eax,esi
    pop    esi
    {load} mov    esp,ebp
    pop    ebp
    ret    0x4
