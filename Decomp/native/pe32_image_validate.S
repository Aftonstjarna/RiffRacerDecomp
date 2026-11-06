.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f9b40, complete 49-byte function including both returns.
.global original_pe32_image_validate
original_pe32_image_validate:
    push ebp
    mov.s ebp, esp
    mov eax, DWORD PTR [ebp+8]
    mov ecx, 0x5a4d
    cmp WORD PTR [eax], cx
    je nt_header
    xor.s eax, eax
    pop ebp
    ret
nt_header:
    mov ecx, DWORD PTR [eax+0x3c]
    add.s ecx, eax
    xor.s eax, eax
    cmp DWORD PTR [ecx], 0x4550
    jne done
    mov edx, 0x10b
    cmp WORD PTR [ecx+0x18], dx
    sete al
done:
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
