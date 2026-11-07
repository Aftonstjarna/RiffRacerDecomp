# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438410,0x43841f); surrounding INT3 padding excluded.
# ECX=base, stack argument=index; EAX=base+(index<<4), ret 4.
.intel_syntax noprefix
.code32
.text
.global original_matrix_row_pointer
original_matrix_row_pointer:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 shl eax,4
 add.s eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
