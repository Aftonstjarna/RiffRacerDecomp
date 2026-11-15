# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4420b0,0x442162); both returns included; INT3 padding excluded.
# ECX=destination; stack arguments: source string, position, count; EAX=destination; ret 12.
.intel_syntax noprefix
.code32
.text
.equ PREPARE_CAPACITY,0x416730
.equ MEMCPY_IMPORT,0x8f8d66
.equ XLENGTH_ERROR_IAT,0x92d168
.equ XOUT_OF_RANGE_IAT,0x92d16c
.equ LENGTH_MESSAGE,0x99994c
.equ POSITION_MESSAGE,0x99995c
.global original_narrow_append_substring
original_narrow_append_substring:
    push   ebp
    mov.s    ebp,esp
    push   ebx
    push   esi
    push   edi
    mov    edi,DWORD PTR [ebp+0x8]
    mov.s    esi,ecx
    mov    ecx,DWORD PTR [ebp+0xc]
    mov    eax,DWORD PTR [edi+0x10]
    cmp.s    eax,ecx
    jae    .Lposition_valid
    push   POSITION_MESSAGE
    call   DWORD PTR XOUT_OF_RANGE_IAT
.Lposition_valid:
# Clip count to the remaining source length after checking the position.
    mov    ebx,DWORD PTR [ebp+0x10]
    sub.s    eax,ecx
    mov    ecx,DWORD PTR [esi+0x10]
    cmp.s    eax,ebx
    mov    DWORD PTR [ebp+0x8],ecx
    cmovb  ebx,eax
    or     eax,0xffffffff
    sub.s    eax,ecx
    cmp.s    eax,ebx
    ja     .Llength_valid
    push   LENGTH_MESSAGE
    call   DWORD PTR XLENGTH_ERROR_IAT
.Llength_valid:
# Zero count and a false capacity-helper result share the unchanged return.
    test   ebx,ebx
    je     .Lreturn_destination
    lea    eax,[ecx+ebx*1]
    mov.s    ecx,esi
    push   0x0
    push   eax
    call   PREPARE_CAPACITY
    test   al,al
    je     .Lreturn_destination
# Resolve both storage pointers after the capacity helper (source may be this).
    cmp    DWORD PTR [edi+0x14],0x10
    jb     .Lsource_pointer_ready
    mov    edi,DWORD PTR [edi]
.Lsource_pointer_ready:
    cmp    DWORD PTR [esi+0x14],0x10
    jb     .Ldestination_inline
    mov    ecx,DWORD PTR [esi]
    jmp    .Ldestination_pointer_ready
.Ldestination_inline:
    mov.s    ecx,esi
.Ldestination_pointer_ready:
    test   ebx,ebx
    je     .Lupdate_length
    mov    eax,DWORD PTR [ebp+0xc]
    add.s    eax,edi
    push   ebx
    push   eax
    mov    eax,DWORD PTR [esi+0x10]
    add.s    eax,ecx
    push   eax
    call   MEMCPY_IMPORT
    add    esp,0xc
.Lupdate_length:
    mov    ecx,DWORD PTR [ebp+0x8]
    add.s    ecx,ebx
    cmp    DWORD PTR [esi+0x14],0x10
    mov    DWORD PTR [esi+0x10],ecx
    jb     .Lterminate_inline
    mov    eax,DWORD PTR [esi]
    pop    edi
    mov    BYTE PTR [eax+ecx*1],0x0
    mov.s    eax,esi
    pop    esi
    pop    ebx
    pop    ebp
    ret    0xc
.Lterminate_inline:
# Second return lies after the heap-return instruction and is part of the function.
    mov.s    eax,esi
    mov    BYTE PTR [eax+ecx*1],0x0
.Lreturn_destination:
    pop    edi
    mov.s    eax,esi
    pop    esi
    pop    ebx
    pop    ebp
    ret    0xc
.section .note.GNU-stack,"",@progbits
