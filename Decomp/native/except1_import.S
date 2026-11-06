# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9d1e,0x8f9d24). Adjacent thunks and INT3 padding excluded.
# Tail transfer preserves caller stack, registers and x87 state.
.intel_syntax noprefix
.code32
.text
.global original_except1_import
original_except1_import:
    jmp DWORD PTR [except1_iat]
.equ except1_iat,0x92d2f8
.section .note.GNU-stack,"",@progbits
