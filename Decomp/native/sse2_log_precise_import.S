.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8f28,0x8f8f2e); neighboring import thunks excluded.
# Sole control-flow edge: indirect tail transfer through loader-populated IAT.
.global original_sse2_log_precise_import
original_sse2_log_precise_import:
    jmp DWORD PTR [log_precise_iat]
.equ log_precise_iat,0x92d428
.section .note.GNU-stack,"",@progbits
