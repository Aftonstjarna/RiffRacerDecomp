# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f7d10; exclusive end 0x4f7d95; excludes INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_script_reallocate
.equ script_prepare_error,0x4f4d00
.equ crt_longjmp,0x92d360
original_script_reallocate:
    push ebp
    {load} mov ebp,esp
    and esp,-8
    push ecx
    push ebx
    push esi
    push edi
    mov edi,DWORD PTR [ebp+12]
    {load} mov esi,ecx
    push edi
    push DWORD PTR [ebp+8]
    mov ebx,DWORD PTR [esi+16]
    push edx
    push DWORD PTR [ebx+16]
    mov eax,DWORD PTR [ebx+12]
    call eax
    {load} mov edx,eax
    add esp,16
    mov DWORD PTR [esp+12],edx
    test edx,edx
    jne account_delta
    test edi,edi
    je account_delta
    mov ecx,DWORD PTR [esi+96]
    test ecx,ecx
    je unprotected_failure
    mov DWORD PTR [ecx+68],4
    mov eax,DWORD PTR [esi+96]
    push 1
    add eax,4
    push eax
    call DWORD PTR [crt_longjmp]
unprotected_failure:
    mov eax,DWORD PTR [esi+16]
    mov BYTE PTR [esi+6],4
    cmp DWORD PTR [eax+88],0
    je account_delta
    mov edx,4
    {load} mov ecx,esi
    call script_prepare_error
    mov eax,DWORD PTR [esi+16]
    push esi
    mov eax,DWORD PTR [eax+88]
    call eax
    mov edx,DWORD PTR [esp+16]
    add esp,4
account_delta:
    sub edi,DWORD PTR [ebp+8]
    {load} mov eax,edx
    add DWORD PTR [ebx+68],edi
    pop edi
    pop esi
    pop ebx
    {load} mov esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
