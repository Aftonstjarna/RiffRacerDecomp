# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete thunk [0x8f9c7c,0x8f9c82); next address is a separate _initterm thunk.
# Tail transfer preserves caller stack and return address; no local RET.
.intel_syntax noprefix
.code32
.text
.global original_initterm_e_import
original_initterm_e_import:
    jmp DWORD PTR [initterm_e_iat]
.equ initterm_e_iat,0x92d2d4
.section .note.GNU-stack,"",@progbits
