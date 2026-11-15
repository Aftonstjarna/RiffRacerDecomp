.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f93cc,0x8f93d2). One terminal indirect jump; no fallthrough.
# Preserves incoming stack/return address and XMM0 argument for the CRT target.
.equ EXP_PRECISE_IAT,0x92d410
.global original_sse2_exp_precise_import
original_sse2_exp_precise_import:
    jmp DWORD PTR [EXP_PRECISE_IAT]
.section .note.GNU-stack,"",@progbits
