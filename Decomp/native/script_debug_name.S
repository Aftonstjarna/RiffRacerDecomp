# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x486680.
.intel_syntax noprefix
.code32
.text
.global original_script_debug_name
.equ LOCAL_NAME,0x4f4c40
.equ TRACE_REGISTER,0x4861e0
.equ CONSTANT_NAME,0x486650
original_script_debug_name:
    push ebp
    mov.s ebp,esp
    push ecx
    push ebx
    push esi
    push edi
    mov.s edi,edx
    mov.s edx,ecx
    mov DWORD PTR [ebp-0x4],edx
    mov eax,DWORD PTR [edi+0x4]
    cmp DWORD PTR [eax+0x4],0x6
    jne L48673f
    jmp L4866a0
    {disp8} lea ecx,[ecx+0x0]
L4866a0:
    mov ecx,DWORD PTR [edi+0x4]
    mov eax,DWORD PTR [ecx]
    cmp BYTE PTR [eax+0x6],0x0
    jne L48673f
    cmp DWORD PTR [ecx+0x4],0x6
    mov ebx,DWORD PTR [eax+0x10]
    jne L4866d4
    cmp edi,DWORD PTR [edx+0x14]
    jne L4866c3
    mov eax,DWORD PTR [edx+0x18]
    mov DWORD PTR [edi+0xc],eax
L4866c3:
    mov eax,DWORD PTR [ecx]
    mov esi,DWORD PTR [edi+0xc]
    mov eax,DWORD PTR [eax+0x10]
    sub esi,DWORD PTR [eax+0xc]
    sar esi,0x2
    dec esi
    jmp L4866d7
L4866d4:
    or esi,0xffffffff
L4866d7:
    mov edx,DWORD PTR [ebp+0x8]
    mov.s ecx,ebx
    push esi
    inc edx
    call LOCAL_NAME
    mov ecx,DWORD PTR [ebp+0xc]
    add esp,0x4
    mov DWORD PTR [ecx],eax
    test eax,eax
    jne L4867de
    push DWORD PTR [ebp+0x8]
    mov.s edx,esi
    mov.s ecx,ebx
    call TRACE_REGISTER
    mov.s edx,eax
    add esp,0x4
    and eax,0x3f
    cmp eax,0xb
    ja L48673f
    movzx ecx,BYTE PTR [eax+0x486804]
    jmp DWORD PTR [ecx*4+0x4867ec]
    mov.s eax,edx
    shr edx,0x6
    shr eax,0x17
    and edx,0xff
    mov DWORD PTR [ebp+0x8],eax
    cmp.s eax,edx
    jge L48673f
    mov eax,DWORD PTR [edi+0x4]
    mov edx,DWORD PTR [ebp-0x4]
    cmp DWORD PTR [eax+0x4],0x6
    je L4866a0
L48673f:
    pop edi
    pop esi
    xor.s eax,eax
    pop ebx
    mov.s esp,ebp
    pop ebp
    ret 
    mov eax,DWORD PTR [ebx+0x8]
    mov ecx,DWORD PTR [ebp+0xc]
    shr edx,0xe
    pop edi
    pop esi
    pop ebx
    mov eax,DWORD PTR [eax+edx*8]
    add eax,0x10
    mov DWORD PTR [ecx],eax
    mov eax,0x9fb658
    mov.s esp,ebp
    pop ebp
    ret 
    shr edx,0xe
    mov.s ecx,ebx
    and edx,0x1ff
    call CONSTANT_NAME
    mov ecx,DWORD PTR [ebp+0xc]
    pop edi
    pop esi
    pop ebx
    mov DWORD PTR [ecx],eax
    mov eax,0x9fb640
    mov.s esp,ebp
    pop ebp
    ret 
    mov eax,DWORD PTR [ebx+0x1c]
    test eax,eax
    je L4867a7
    mov ecx,DWORD PTR [ebp+0xc]
    shr edx,0x17
    pop edi
    pop esi
    pop ebx
    mov eax,DWORD PTR [eax+edx*4]
    add eax,0x10
    mov DWORD PTR [ecx],eax
    mov eax,0x9fb648
    mov.s esp,ebp
    pop ebp
    ret 
L4867a7:
    mov ecx,DWORD PTR [ebp+0xc]
    mov eax,0x9f99d0
    pop edi
    pop esi
    pop ebx
    mov DWORD PTR [ecx],eax
    mov eax,0x9fb648
    mov.s esp,ebp
    pop ebp
    ret 
    shr edx,0xe
    mov.s ecx,ebx
    and edx,0x1ff
    call CONSTANT_NAME
    mov ecx,DWORD PTR [ebp+0xc]
    pop edi
    pop esi
    pop ebx
    mov DWORD PTR [ecx],eax
    mov eax,0x9fb688
    mov.s esp,ebp
    pop ebp
    ret 
L4867de:
    pop edi
    pop esi
    mov eax,0x9fb650
    pop ebx
    mov.s esp,ebp
    pop ebp
    ret 
.section .note.GNU-stack,"",@progbits
