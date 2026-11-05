# Mechanically transcribed reference evidence, NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8c42,0x8f8c48). One unconditional indirect tail jump.
# cdecl operator new(unsigned int): size at [ESP+4], result EAX.
# Retains caller return address/arguments; CRT owns allocation and exceptions.
.intel_syntax noprefix
.code32
.text
.global original_operator_new_import
original_operator_new_import:
 jmp DWORD PTR [operator_new_iat]
.equ operator_new_iat,0x92d4b4
.section .note.GNU-stack,"",@progbits
