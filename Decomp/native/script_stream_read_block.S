# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f60a0,0x4f6139); both returns included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_stream_read_block
.equ MEMCPY_THUNK,0x8f8d66
original_script_stream_read_block:
L_4f60a0:
    push ebp
L_4f60a1:
    mov.s ebp,esp
L_4f60a3:
    push ecx
L_4f60a4:
    push ebx
L_4f60a5:
    mov ebx,DWORD PTR [ebp+0x8]
L_4f60a8:
    mov DWORD PTR [ebp-0x4],edx
L_4f60ab:
    push esi
L_4f60ac:
    mov.s esi,ecx
L_4f60ae:
    push edi
L_4f60af:
    test ebx,ebx
L_4f60b1:
    je L_4f6127
L_4f60b3:
    cmp DWORD PTR [esi],0x0
L_4f60b6:
    jne L_4f60f9
L_4f60b8:
    lea eax,[ebp+0x8]
L_4f60bb:
    push eax
L_4f60bc:
    push DWORD PTR [esi+0xc]
L_4f60bf:
    mov eax,DWORD PTR [esi+0x8]
L_4f60c2:
    push DWORD PTR [esi+0x10]
L_4f60c5:
    call eax
L_4f60c7:
    mov.s ecx,eax
L_4f60c9:
    add esp,0xc
L_4f60cc:
    test ecx,ecx
L_4f60ce:
    je L_4f6130
L_4f60d0:
    mov eax,DWORD PTR [ebp+0x8]
L_4f60d3:
    test eax,eax
L_4f60d5:
    je L_4f6130
L_4f60d7:
    lea edx,[eax-0x1]
L_4f60da:
    mov DWORD PTR [esi+0x4],ecx
L_4f60dd:
    mov DWORD PTR [esi],edx
L_4f60df:
    movzx eax,BYTE PTR [ecx]
L_4f60e2:
    inc ecx
L_4f60e3:
    mov DWORD PTR [esi+0x4],ecx
L_4f60e6:
    cmp eax,0xffffffff
L_4f60e9:
    je L_4f6130
L_4f60eb:
    lea eax,[edx+0x1]
L_4f60ee:
    mov edx,DWORD PTR [ebp-0x4]
L_4f60f1:
    mov DWORD PTR [esi],eax
L_4f60f3:
    lea eax,[ecx-0x1]
L_4f60f6:
    mov DWORD PTR [esi+0x4],eax
L_4f60f9:
    mov ecx,DWORD PTR [esi+0x4]
L_4f60fc:
    movzx eax,BYTE PTR [ecx]
L_4f60ff:
    cmp eax,0xffffffff
L_4f6102:
    je L_4f6130
L_4f6104:
    mov.s edi,DWORD PTR [esi]
L_4f6106:
    cmp.s ebx,edi
L_4f6108:
    cmovbe edi,ebx
L_4f610b:
    push edi
L_4f610c:
    push ecx
L_4f610d:
    push edx
L_4f610e:
    call MEMCPY_THUNK
L_4f6113:
    mov edx,DWORD PTR [ebp-0x4]
L_4f6116:
    add esp,0xc
L_4f6119:
    sub DWORD PTR [esi],edi
L_4f611b:
    add.s edx,edi
L_4f611d:
    add DWORD PTR [esi+0x4],edi
L_4f6120:
    mov DWORD PTR [ebp-0x4],edx
L_4f6123:
    sub.s ebx,edi
L_4f6125:
    jne L_4f60b3
L_4f6127:
    pop edi
L_4f6128:
    pop esi
L_4f6129:
    xor.s eax,eax
L_4f612b:
    pop ebx
L_4f612c:
    mov.s esp,ebp
L_4f612e:
    pop ebp
L_4f612f:
    ret 
L_4f6130:
    pop edi
L_4f6131:
    pop esi
L_4f6132:
    mov.s eax,ebx
L_4f6134:
    pop ebx
L_4f6135:
    mov.s esp,ebp
L_4f6137:
    pop ebp
L_4f6138:
    ret 
.section .note.GNU-stack,"",@progbits
