.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f8180.
.global original_controller_indexed_float_get
original_controller_indexed_float_get:
    push ebp
    {load} mov ebp, esp
    mov eax, DWORD PTR [ebp+8]
    fld DWORD PTR [ecx+eax*4+0x38]
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
