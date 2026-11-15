# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9ef4,0x8f9efa). Complete import tail thunk; no local return.
.intel_syntax noprefix
.code32
.text
.global original_crt_except_handler4_common_import
.equ except_handler4_common_iat,0x92d310
original_crt_except_handler4_common_import:
    jmp DWORD PTR [except_handler4_common_iat]
.section .note.GNU-stack,"",@progbits
