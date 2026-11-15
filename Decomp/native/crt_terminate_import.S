# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9522,0x8f9528). One tail jump; no fallthrough or local ret.
.intel_syntax noprefix
.code32
.text
.global original_crt_terminate_import
.equ terminate_iat,0x92d3f0
original_crt_terminate_import:
    jmp DWORD PTR [terminate_iat]
.section .note.GNU-stack,"",@progbits
