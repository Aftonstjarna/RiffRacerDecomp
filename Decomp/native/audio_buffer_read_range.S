.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e0d0,0x58e17f); both returns, excluding INT3 padding.
# ECX=buffer, EDX=destination, stack=count; caller pops count; EAX=result.
.equ memcpy_import,0x8f8d66
.global original_audio_buffer_read_range
original_audio_buffer_read_range:
    push ebp
    mov.s ebp,esp
    sub esp,0xc
    mov eax,DWORD PTR [ecx+8]
    push ebx
    push esi
    mov esi,DWORD PTR [ecx]
    xor.s ebx,ebx
    push edi
    mov edi,DWORD PTR [ecx+0xc]
    sub.s eax,edi
    mov DWORD PTR [ebp-8],edx
    xor.s edx,edx
    mov DWORD PTR [ebp-0xc],ecx
    mov DWORD PTR [ebp-4],edx
    cmp eax,DWORD PTR [ebp+8]
    jge .Lenough
    mov eax,DWORD PTR [ecx+0x10]
    pop edi
    pop esi
    mov DWORD PTR [ecx+0xc],eax
    lea eax,[edx-0xa]
    pop ebx
    mov.s esp,ebp
    pop ebp
    ret
.Lenough:
    test esi,esi
    je .Lcount
    {disp32} lea esp,[esp+0]
.Llocate:
    mov eax,DWORD PTR [esi+4]
    add.s eax,ebx
    cmp.s eax,edi
    jg .Lcount
    mov esi,DWORD PTR [esi+0xc]
    mov.s ebx,eax
    test esi,esi
    jne .Llocate
.Lcount:
    mov eax,DWORD PTR [ebp+8]
    test eax,eax
    jle .Ldone
    {disp32} lea esp,[esp+0]
.Lcopy:
    test esi,esi
    je .Ldone
    mov ecx,DWORD PTR [ecx+0xc]
    mov.s edi,eax
    mov eax,DWORD PTR [esi+4]
    sub.s ecx,ebx
    sub.s eax,ecx
    sub.s edi,edx
    cmp.s edi,eax
    cmovg edi,eax
    mov eax,DWORD PTR [esi]
    add.s eax,ecx
    push edi
    push eax
    mov eax,DWORD PTR [ebp-8]
    add.s eax,edx
    push eax
    call memcpy_import
    mov ecx,DWORD PTR [ebp-0xc]
    add esp,0xc
    mov edx,DWORD PTR [ebp-4]
    mov eax,DWORD PTR [ebp+8]
    add.s edx,edi
    mov DWORD PTR [ebp-4],edx
    add DWORD PTR [ecx+0xc],edi
    add ebx,DWORD PTR [esi+4]
    mov esi,DWORD PTR [esi+0xc]
    cmp.s edx,eax
    jl .Lcopy
.Ldone:
    pop edi
    pop esi
    mov.s eax,edx
    pop ebx
    mov.s esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
