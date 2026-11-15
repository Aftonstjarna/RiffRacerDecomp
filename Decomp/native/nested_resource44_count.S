# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x512c80,0x512c8e); both returns, no padding.
# ECX points to owner; reads owner+0x44 then nested+0x1c when nonnull.
.intel_syntax noprefix
.code32
.text
.global original_nested_resource44_count
original_nested_resource44_count:
    mov eax,DWORD PTR [ecx+0x44]
    test eax,eax
    je L_null
    mov eax,DWORD PTR [eax+0x1c]
    ret
L_null:
    xor.s eax,eax
    ret
.section .note.GNU-stack,"",@progbits
