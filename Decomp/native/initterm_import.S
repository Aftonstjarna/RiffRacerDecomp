# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9c82,0x8f9c88): complete MSVCR120.dll!_initterm import thunk.
# Tail transfer preserves the caller return address and two cdecl arguments.
.intel_syntax noprefix
.code32
.text
.equ initterm_iat,0x92d4dc
.global original_initterm_import
original_initterm_import:
 jmp DWORD PTR ds:initterm_iat
.section .note.GNU-stack,"",@progbits
