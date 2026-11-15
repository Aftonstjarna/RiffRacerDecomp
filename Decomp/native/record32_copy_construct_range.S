# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x520c40,0x520c8c); both returns included; INT3 padding excluded.
# ECX=source begin, EDX=source end, [entry ESP+4]=destination.
# Caller cleans stack; EAX=advanced destination. No calls or absolute data.
.intel_syntax noprefix
.code32
.text
.global original_record32_copy_construct_range
original_record32_copy_construct_range:
    push ebp
    mov.s ebp,esp
    cmp.s ecx,edx
    je empty_range
    push esi
    mov esi,DWORD PTR [ebp+8]
    push edi
    lea edi,[ecx+0x10]
    nop
copy_record:
    test esi,esi
    je advance_record
    movdqu xmm0,XMMWORD PTR [edi-0x10]
    movdqu XMMWORD PTR [esi],xmm0
    mov eax,DWORD PTR [edi]
    mov DWORD PTR [esi+0x10],eax
    mov eax,DWORD PTR [edi+4]
    mov DWORD PTR [esi+0x14],eax
    mov eax,DWORD PTR [edi+8]
    mov DWORD PTR [esi+0x18],eax
    mov eax,DWORD PTR [edi+0xc]
    mov DWORD PTR [esi+0x1c],eax
advance_record:
    add edi,0x20
    add esi,0x20
    lea ecx,[edi-0x10]
    cmp.s ecx,edx
    jne copy_record
    pop edi
    mov.s eax,esi
    pop esi
    pop ebp
    ret
empty_range:
    mov eax,DWORD PTR [ebp+8]
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
