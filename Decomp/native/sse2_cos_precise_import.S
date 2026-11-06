.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8f22,0x8f8f28). Tail jump only; adjacent thunk excluded.
.global original_sse2_cos_precise_import
original_sse2_cos_precise_import:
    jmp DWORD PTR [cos_precise_iat]
.equ cos_precise_iat,0x92d42c
.section .note.GNU-stack,"",@progbits
