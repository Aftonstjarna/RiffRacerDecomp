# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4f09e0,0x4f0adc); both returns included; surrounding INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_new_key
.equ MAIN_BUCKET,0x4f0110
.equ REHASH,0x4f0800
.equ ENSURE_VALUE,0x4f0c50
.equ DUMMY_NODE,0x99a424
original_script_table_new_key:
# ECX=state, EDX=table, [ESP+4]=tagged key; caller pops argument; EAX=value slot.
    push   ebp
    mov.s    ebp,esp
    push   ecx
    push   ebx
    push   esi
    mov.s    esi,edx
    mov.s    edx,DWORD PTR [ebp+0x8]
    push   edi
    mov.s    edi,ecx
    mov.s    ecx,esi
    mov    DWORD PTR [ebp-0x4],edi
    call MAIN_BUCKET
    mov.s    ebx,eax
    cmp    DWORD PTR [ebx+0x4],0x0
    jne L_4f0a0c
    cmp    ebx,DUMMY_NODE
    jne L_4f0a9f
L_4f0a0c:
# Scan backward for a free 20-byte node.
    mov.s    eax,DWORD PTR [esi+0x10]
    cmp    DWORD PTR [esi+0x14],eax
    jbe L_4f0a25
L_4f0a14:
    add    DWORD PTR [esi+0x14],0xffffffec
    mov.s    edi,DWORD PTR [esi+0x14]
    cmp    DWORD PTR [edi+0xc],0x0
    je L_4f0a4c
    cmp.s    edi,eax
    ja L_4f0a14
L_4f0a25:
    add    DWORD PTR [esi+0x14],0xffffffec
L_4f0a29:
# No free node: rehash and retry through the general setter.
    mov.s    ebx,DWORD PTR [ebp+0x8]
    mov.s    edx,esi
    mov.s    ecx,DWORD PTR [ebp-0x4]
    push   ebx
    call REHASH
    mov.s    ecx,DWORD PTR [ebp-0x4]
    mov.s    edx,esi
    push   ebx
    call ENSURE_VALUE
    add    esp,0x8
    pop    edi
    pop    esi
    pop    ebx
    mov.s    esp,ebp
    pop    ebp
    ret
L_4f0a4c:
    test   edi,edi
    je L_4f0a29
# Find displaced occupant main bucket; relocate or link collision node.
    lea    edx,[ebx+0x8]
    mov.s    ecx,esi
    call MAIN_BUCKET
    cmp.s    eax,ebx
    je L_4f0a91
    cmp    DWORD PTR [eax+0x10],ebx
    lea    ecx,[eax+0x10]
    je L_4f0a70
L_4f0a66:
    mov.s    eax,DWORD PTR [ecx]
    cmp    DWORD PTR [eax+0x10],ebx
    lea    ecx,[eax+0x10]
    jne L_4f0a66
L_4f0a70:
    mov    DWORD PTR [eax+0x10],edi
    movdqu xmm0,XMMWORD PTR [ebx]
    movdqu XMMWORD PTR [edi],xmm0
    mov.s    eax,DWORD PTR [ebx+0x10]
    mov    DWORD PTR [edi+0x10],eax
    mov    DWORD PTR [ebx+0x10],0x0
    mov    DWORD PTR [ebx+0x4],0x0
    jmp L_4f0a9c
L_4f0a91:
    mov.s    eax,DWORD PTR [ebx+0x10]
    mov    DWORD PTR [edi+0x10],eax
    mov    DWORD PTR [ebx+0x10],edi
    mov.s    ebx,edi
L_4f0a9c:
    mov.s    edi,DWORD PTR [ebp-0x4]
L_4f0a9f:
# Copy key payload/tag into the selected node.
    mov.s    ecx,DWORD PTR [ebp+0x8]
    mov.s    eax,DWORD PTR [ecx]
    mov    DWORD PTR [ebx+0x8],eax
    mov.s    eax,DWORD PTR [ecx+0x4]
    mov    DWORD PTR [ebx+0xc],eax
    cmp    DWORD PTR [ecx+0x4],0x4
    jl L_4f0ad3
    mov.s    eax,DWORD PTR [ecx]
    test   BYTE PTR [eax+0x5],0x3
    je L_4f0ad3
# Collectable key and black table: clear black bit and link table to grayagain.
    mov    al,BYTE PTR [esi+0x5]
    test   al,0x4
    je L_4f0ad3
    mov.s    ecx,DWORD PTR [edi+0x10]
    and    al,0xfb
    mov    BYTE PTR [esi+0x5],al
    mov.s    eax,DWORD PTR [ecx+0x28]
    mov    DWORD PTR [esi+0x18],eax
    mov    DWORD PTR [ecx+0x28],esi
L_4f0ad3:
    pop    edi
    pop    esi
    mov.s    eax,ebx
    pop    ebx
    mov.s    esp,ebp
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
