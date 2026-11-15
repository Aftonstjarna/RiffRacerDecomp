# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x008f8f34, complete 6-byte tail-import thunk.
.intel_syntax noprefix
.code32
.text
.equ SIN_PRECISE_IAT,0x92d420
.global original_sse2_sin_precise_import
original_sse2_sin_precise_import:
    jmp DWORD PTR [SIN_PRECISE_IAT]
.section .note.GNU-stack,"",@progbits
