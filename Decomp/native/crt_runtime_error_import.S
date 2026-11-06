.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9a1c,0x8f9a22). Complete import tail thunk.
.equ runtime_error_iat,0x92d2b4
.global original_crt_runtime_error_import
original_crt_runtime_error_import:
 jmp DWORD PTR ds:runtime_error_iat
.section .note.GNU-stack,"",@progbits
