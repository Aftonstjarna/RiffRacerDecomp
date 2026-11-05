# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8c48,0x8f8c4e). Complete scalar operator-delete import thunk.
# cdecl void operator delete(void*): pointer at [ESP+4], caller pops argument.
# Sole branch is an indirect tail jump; no local return, stack or register writes.
# CRT implementation and runtime IAT binding remain external dependencies.
.intel_syntax noprefix
.code32
.text
.global original_operator_delete_import
.equ operator_delete_iat,0x92d4b0
original_operator_delete_import:
 jmp DWORD PTR [operator_delete_iat]
.section .note.GNU-stack,"",@progbits
