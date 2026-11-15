# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f94bf,0x8f9521); includes SEH cleanup funclet after main ret.
.intel_syntax noprefix
.code32
.text
.global original_array_construct_with_cleanup
.equ seh_prolog,0x8f9c90
.equ seh_epilog,0x8f9cd5
.equ array_destroy,0x8f9461
original_array_construct_with_cleanup:
L_8f94bf:
    push   0x10
L_8f94c1:
    push   0xb9e640
L_8f94c6:
    call seh_prolog
L_8f94cb:
    xor.s    esi,esi
L_8f94cd:
    mov    DWORD PTR [ebp-0x1c],esi
L_8f94d0:
    mov    DWORD PTR [ebp-0x20],esi
L_8f94d3:
    mov    DWORD PTR [ebp-0x4],esi
L_8f94d6:
    cmp    esi,DWORD PTR [ebp+0x10]
L_8f94d9:
    jge L_8f94ed
L_8f94db:
    mov    ecx,DWORD PTR [ebp+0x8]
L_8f94de:
    call   DWORD PTR [ebp+0x14]
L_8f94e1:
    mov    eax,DWORD PTR [ebp+0xc]
L_8f94e4:
    add    DWORD PTR [ebp+0x8],eax
L_8f94e7:
    inc    esi
L_8f94e8:
    mov    DWORD PTR [ebp-0x1c],esi
L_8f94eb:
    jmp L_8f94d6
L_8f94ed:
    xor.s    eax,eax
L_8f94ef:
    inc    eax
L_8f94f0:
    mov    DWORD PTR [ebp-0x20],eax
L_8f94f3:
    mov    DWORD PTR [ebp-0x4],0xfffffffe
L_8f94fa:
    call L_8f950d
L_8f94ff:
    call seh_epilog
L_8f9504:
    ret    0x14
L_8f9507:
    mov    esi,DWORD PTR [ebp-0x1c]
L_8f950a:
    mov    eax,DWORD PTR [ebp-0x20]
L_8f950d:
    test   eax,eax
L_8f950f:
    jne L_8f9520
L_8f9511:
    push   DWORD PTR [ebp+0x18]
L_8f9514:
    push   esi
L_8f9515:
    push   DWORD PTR [ebp+0xc]
L_8f9518:
    push   DWORD PTR [ebp+0x8]
L_8f951b:
    call array_destroy
L_8f9520:
    ret
.section .note.GNU-stack,"",@progbits
