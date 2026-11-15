# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f977e,0x8f97e6), including SEH cleanup funclet.
.intel_syntax noprefix
.code32
.text
.global original_array_copy_construct_with_cleanup
.equ seh_prolog,0x8f9c90
.equ seh_epilog,0x8f9cd5
.equ scope_table,0xb9e660
.equ array_destroy,0x8f9461
original_array_copy_construct_with_cleanup:
    push 0x10
    push scope_table
    call seh_prolog
    xor.s esi,esi
    mov DWORD PTR [ebp-0x1c],esi
    mov DWORD PTR [ebp-0x20],esi
    mov DWORD PTR [ebp-0x4],esi
L_loop:
    cmp esi,DWORD PTR [ebp+0x14]
    jge L_success
    push DWORD PTR [ebp+0xc]
    mov ecx,DWORD PTR [ebp+0x8]
    call DWORD PTR [ebp+0x18]
    mov eax,DWORD PTR [ebp+0x10]
    add DWORD PTR [ebp+0x8],eax
    add DWORD PTR [ebp+0xc],eax
    inc esi
    mov DWORD PTR [ebp-0x1c],esi
    jmp L_loop
L_success:
    xor.s eax,eax
    inc eax
    mov DWORD PTR [ebp-0x20],eax
    mov DWORD PTR [ebp-0x4],0xfffffffe
    call L_cleanup
    call seh_epilog
    ret 0x18
# Unwind entry 0x8f97cc, referenced at scope-table address 0xb9e678.
L_unwind:
    mov esi,DWORD PTR [ebp-0x1c]
    mov eax,DWORD PTR [ebp-0x20]
L_cleanup:
    test eax,eax
    jne L_done
    push DWORD PTR [ebp+0x1c]
    push esi
    push DWORD PTR [ebp+0x10]
    push DWORD PTR [ebp+0x8]
    call array_destroy
L_done:
    ret
.section .note.GNU-stack,"",@progbits
