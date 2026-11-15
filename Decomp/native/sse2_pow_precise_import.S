.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete thunk VA 0x008f8f2e, end-exclusive 0x008f8f34.
# Tail transfer preserves caller stack and XMM arguments/result ABI.
.equ POW_PRECISE_IAT,0x0092d424
.global original_sse2_pow_precise_import
original_sse2_pow_precise_import:
    jmp DWORD PTR [POW_PRECISE_IAT]
.section .note.GNU-stack,"",@progbits
