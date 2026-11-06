.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f99c0, complete six-byte import tail thunk.
.equ TYPE_INFO_DESTRUCTOR_IAT,0x92d2a4
.global original_type_info_destructor_import
original_type_info_destructor_import:
    jmp DWORD PTR [TYPE_INFO_DESTRUCTOR_IAT]
.section .note.GNU-stack,"",@progbits
