.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8d84,0x8f8d8a). Complete one-instruction import thunk.
# Tail jump preserves caller return address and five cdecl stack arguments.
# CRT __RTDynamicCast implementation and RTTI graph semantics remain external.
.equ dynamic_cast_iat,0x92d47c
.global original_dynamic_cast_import
original_dynamic_cast_import:
 jmp DWORD PTR [dynamic_cast_iat]
.section .note.GNU-stack,"",@progbits
