.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x55b470.
.global original_input_pointer_get
original_input_pointer_get:
    push ebp
    mov.s ebp, esp
    mov eax, DWORD PTR [ebp+8]
    mov.s edx, ecx
    cmp BYTE PTR [edx+0x246], 0
    je .Lstored
    mov DWORD PTR [eax], 0
    mov DWORD PTR [eax+4], 0
    pop ebp
    ret 4
.Lstored:
    mov ecx, DWORD PTR [edx+0x23c]
    mov DWORD PTR [eax], ecx
    mov ecx, DWORD PTR [edx+0x240]
    mov DWORD PTR [eax+4], ecx
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
