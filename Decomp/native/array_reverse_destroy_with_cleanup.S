# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f93f2,0x8f9461), includes unwind cleanup after first ret.
.intel_syntax noprefix
.code32
.text
.global original_array_reverse_destroy_with_cleanup
.equ seh_prolog,0x8f9c90
.equ seh_epilog,0x8f9cd5
.equ scope_table,0xb9e600
.equ remaining_destroy,0x8f9461
original_array_reverse_destroy_with_cleanup:
    push 0xc
    push scope_table
    call seh_prolog
    and DWORD PTR [ebp-0x1c],0
    mov ebx,DWORD PTR [ebp+0xc]
    mov.s eax,ebx
    mov edi,DWORD PTR [ebp+0x10]
    imul eax,edi
    mov esi,DWORD PTR [ebp+0x8]
    add.s esi,eax
    mov DWORD PTR [ebp+0x8],esi
    and DWORD PTR [ebp-0x4],0
L_loop:
    dec edi
    mov DWORD PTR [ebp+0x10],edi
    js L_finish
    sub.s esi,ebx
    mov DWORD PTR [ebp+0x8],esi
    mov.s ecx,esi
    call DWORD PTR [ebp+0x14]
    jmp L_loop
L_finish:
    xor.s eax,eax
    inc eax
    mov DWORD PTR [ebp-0x1c],eax
    mov DWORD PTR [ebp-0x4],0xfffffffe
    call L_cleanup
    call seh_epilog
    ret 0x10
# Scope-table unwind entry 0x8f9445 at original 0xb9e618.
L_unwind:
    mov edi,DWORD PTR [ebp+0x10]
    mov ebx,DWORD PTR [ebp+0xc]
    mov esi,DWORD PTR [ebp+0x8]
    mov eax,DWORD PTR [ebp-0x1c]
L_cleanup:
    test eax,eax
    jne L_done
    push DWORD PTR [ebp+0x14]
    push edi
    push ebx
    push esi
    call remaining_destroy
L_done:
    ret
.section .note.GNU-stack,"",@progbits
