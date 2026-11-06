.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x6d86bb,0x6d86c1). One unconditional indirect tail jump.
# CLR VTableFixup: RVA 0x7a556c, count 1, type 0x9; initial MethodDef token
# 0x060010c5 is loader data, NOT a callable native address before CLR fixup.
# Callers consume EAX as an object pointer; target implementation remains external.
.equ runtime_accessor_cell,0xba556c
.global original_runtime_accessor_thunk
original_runtime_accessor_thunk:
 jmp DWORD PTR [runtime_accessor_cell]
.section .note.GNU-stack,"",@progbits
