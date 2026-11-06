# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8d60,0x8f8d66). Complete import thunk; no ret or fallthrough.
.intel_syntax noprefix
.code32
.text
.global original_sse2_sqrt_precise_import
.equ sqrt_precise_iat,0x92d498
original_sse2_sqrt_precise_import:
 jmp DWORD PTR [sqrt_precise_iat]
.section .note.GNU-stack,"",@progbits
