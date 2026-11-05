# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8f40,0x8f8f46). Import thunk; no local RET.
# cdecl double floor(double): stack argument and x87 ST(0) return.
# Tail jump preserves the caller's return address and stack layout.
.intel_syntax noprefix
.code32
.text
.global original_floor_import
original_floor_import:
 jmp DWORD PTR [floor_iat]
.equ floor_iat,0x92d418
.section .note.GNU-stack,"",@progbits
