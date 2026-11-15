# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d8c0,0x47d8d1); trailing INT3 padding excluded.
# Compound-shape vtable 0x9fb1d4 +0x24. ECX=this; one stack float;
# callee pops 4 bytes. Copies bits through XMM0 to this+0x48.
# No branches, calls, imports, constants or exception-state dependencies.
.intel_syntax noprefix
.code32
.text
.global original_compound_shape_set_margin
original_compound_shape_set_margin:
 push ebp
 mov.s ebp,esp
 movss xmm0,DWORD PTR [ebp+8]
 movss DWORD PTR [ecx+0x48],xmm0
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
