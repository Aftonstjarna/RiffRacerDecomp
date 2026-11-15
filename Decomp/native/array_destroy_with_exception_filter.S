# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x8f9461,0x8f94bf); includes scope-table filter and continuation.
.intel_syntax noprefix
.code32
.text
.global original_array_destroy_with_exception_filter
.equ seh_prolog,0x8f9c90
.equ seh_epilog,0x8f9cd5
.equ terminate_import,0x8f9522
original_array_destroy_with_exception_filter:
    push 0x14
    push 0xb9e620
    call seh_prolog
    and DWORD PTR [ebp-0x4],0x0
L_loop:
    dec DWORD PTR [ebp+0x10]
    js L_finish
    mov ecx,DWORD PTR [ebp+0x8]
    sub ecx,DWORD PTR [ebp+0xc]
    mov DWORD PTR [ebp+0x8],ecx
    call DWORD PTR [ebp+0x14]
    jmp L_loop
# Filter entry at 0x8f9484, referenced by original scope table 0xb9e630.
L_filter:
    mov eax,DWORD PTR [ebp-0x14]
    mov DWORD PTR [ebp-0x1c],eax
    mov eax,DWORD PTR [ebp-0x1c]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ebp-0x20],eax
    mov eax,DWORD PTR [ebp-0x20]
    cmp DWORD PTR [eax],0xe06d7363
    je L_terminate
    mov DWORD PTR [ebp-0x24],0x0
    mov eax,DWORD PTR [ebp-0x24]
    ret
L_terminate:
    call terminate_import
# Handler continuation at 0x8f94ad, also referenced by scope table.
L_continue:
    mov esp,DWORD PTR [ebp-0x18]
L_finish:
    mov DWORD PTR [ebp-0x4],0xfffffffe
    call seh_epilog
    ret 0x10
.section .note.GNU-stack,"",@progbits
