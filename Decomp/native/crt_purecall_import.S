.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x008f893a, complete six-byte import thunk.
.equ PURECALL_IAT,0x0092d4d8
.global original_crt_purecall_import
original_crt_purecall_import:
    jmp DWORD PTR [PURECALL_IAT]
.section .note.GNU-stack,"",@progbits
