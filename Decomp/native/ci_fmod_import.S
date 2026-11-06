# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc1a2,0x8fc1a8); following INT3 padding excluded.
# Tail transfer preserves the caller's return address and x87 operands.
.intel_syntax noprefix
.code32
.text
.global original_ci_fmod_import
.equ ci_fmod_iat,0x92d4f8
original_ci_fmod_import:
 jmp DWORD PTR [ci_fmod_iat]
.section .note.GNU-stack,"",@progbits
