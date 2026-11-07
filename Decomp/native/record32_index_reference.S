# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original span: [0x41dfb0,0x41dfd8).
.intel_syntax noprefix
.code32
.text
.global original_record32_index_reference
.equ REFERENCE_TABLE,0xba2150
original_record32_index_reference:
    push ebp
    mov.s ebp,esp
    mov edx,DWORD PTR [ecx+8]
    mov ecx,DWORD PTR [ecx+4]
    mov eax,DWORD PTR [ebp+8]
    mov ecx,DWORD PTR [ecx+8]
    add ecx,DWORD PTR [ebp+12]
    shl ecx,5
    add ecx,DWORD PTR [edx+12]
    mov DWORD PTR [eax],REFERENCE_TABLE
    mov DWORD PTR [eax+4],ecx
    mov DWORD PTR [eax+8],edx
    pop ebp
    ret 8
.section .note.GNU-stack,"",@progbits
