# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8f3a,0x8f8f40); one complete indirect tail jump.
# Adjacent import thunks are separate entries, not fallthrough code.
# cdecl double ceil(double): argument at ESP+4, result in x87 ST(0).
# No stack/register modification before dispatch through MSVCR120.dll IAT.
.intel_syntax noprefix
.code32
.text
.global original_ceil_import
original_ceil_import:
 jmp DWORD PTR [ceil_iat]
.equ ceil_iat,0x92d41c
.section .note.GNU-stack,"",@progbits
