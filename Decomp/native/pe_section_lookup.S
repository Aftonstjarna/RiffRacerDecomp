.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f9a30, complete 67-byte function. GNU .s selects original register encoding.
.global original_pe_section_lookup
original_pe_section_lookup:
    push ebp
    mov.s ebp, esp
    mov eax, DWORD PTR [ebp+8]
    xor.s edx, edx
    push ebx
    push esi
    push edi
    mov ecx, DWORD PTR [eax+0x3c]
    add.s ecx, eax
    movzx eax, WORD PTR [ecx+0x14]
    movzx ebx, WORD PTR [ecx+6]
    add eax, 0x18
    add.s eax, ecx
    test ebx, ebx
    je not_found
    mov edi, DWORD PTR [ebp+0xc]
next_section:
    mov esi, DWORD PTR [eax+0xc]
    cmp.s edi, esi
    jb advance_section
    mov ecx, DWORD PTR [eax+8]
    add.s ecx, esi
    cmp.s edi, ecx
    jb done
advance_section:
    inc edx
    add eax, 0x28
    cmp.s edx, ebx
    jb next_section
not_found:
    xor.s eax, eax
done:
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
