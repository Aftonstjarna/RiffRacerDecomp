# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x486a30,0x486aaf); final tail jump included, INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_error_dispatch
.equ THROW_STATUS,0x4f4d80
.equ GROW_STACK,0x4f4ef0
.equ CALL_HANDLER,0x4f5830
original_script_error_dispatch:
    push esi
    mov.s esi,ecx
    push edi
    mov eax,DWORD PTR [esi+0x64]
    test eax,eax
    je dispatch_status
    mov edi,DWORD PTR [esi+0x20]
    add.s edi,eax
    cmp DWORD PTR [edi+4],6
    je handler_valid
    mov edx,5
    call THROW_STATUS
handler_valid:
    mov ecx,DWORD PTR [esi+8]
    mov eax,DWORD PTR [ecx-8]
    mov DWORD PTR [ecx],eax
    mov eax,DWORD PTR [ecx-4]
    mov DWORD PTR [ecx+4],eax
    mov ecx,DWORD PTR [esi+8]
    mov eax,DWORD PTR [edi]
    mov DWORD PTR [ecx-8],eax
    mov eax,DWORD PTR [edi+4]
    mov DWORD PTR [ecx-4],eax
    mov eax,DWORD PTR [esi+0x1c]
    sub eax,DWORD PTR [esi+8]
    cmp eax,8
    jg stack_ready
    mov edx,DWORD PTR [esi+0x2c]
    mov.s ecx,esi
    cmp edx,1
    jl increment_capacity
    add.s edx,edx
    jmp grow_stack
increment_capacity:
    inc edx
grow_stack:
    call GROW_STACK
stack_ready:
    add DWORD PTR [esi+8],8
    mov.s ecx,esi
    mov edx,DWORD PTR [esi+8]
    push 1
    add edx,-16
    call CALL_HANDLER
    add esp,4
dispatch_status:
    mov edx,2
    mov.s ecx,esi
    pop edi
    pop esi
    jmp THROW_STATUS
.section .note.GNU-stack,"",@progbits
