# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8f46,0x8f8f4c); MSVCR120.dll!_libm_sse2_log10_precise.
# Tail jump preserves the original caller return address and XMM0 argument/result ABI.
.intel_syntax noprefix
.code32
.text
.equ LOG10_IAT,0x92d414
.global original_sse2_log10_precise_import
original_sse2_log10_precise_import:
    jmp DWORD PTR [LOG10_IAT]
.section .note.GNU-stack,"",@progbits
