.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58d880,0x58d8d3). Both returns included; INT3 padding excluded.
.global original_audio_input_read_loop
original_audio_input_read_loop:
# cdecl(state*, destination*, signed count); callback uses the same ABI.
    push ebp
    mov.s ebp,esp
    push ebx
    mov ebx,DWORD PTR [ebp+0x10]
    push esi
    xor.s esi,esi
    push edi
    test ebx,ebx
    jle .Ldone
    mov edi,DWORD PTR [ebp+0x8]
.Lread:
    mov.s eax,ebx
    sub.s eax,esi
    push eax
    mov eax,DWORD PTR [ebp+0xc]
    add.s eax,esi
    push eax
    mov eax,DWORD PTR [edi+0x6d58]
    push edi
    call eax
    add esp,0xc
    test eax,eax
    js .Lerror
    je .Ldone
    test BYTE PTR [edi+0x6d50],0x8
    jne .Laccumulate
    add DWORD PTR [edi+0x6d44],eax
.Laccumulate:
    add.s esi,eax
    cmp.s esi,ebx
    jl .Lread
.Ldone:
    pop edi
    mov.s eax,esi
    pop esi
    pop ebx
    pop ebp
    ret
.Lerror:
    pop edi
    pop esi
    or eax,-1
    pop ebx
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
