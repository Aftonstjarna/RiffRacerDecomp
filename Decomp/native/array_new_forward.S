# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x8f87c8,0x8f87d1); adjacent INT3 and import thunk excluded.
.intel_syntax noprefix
.code32
.text
.global original_array_new_forward
original_array_new_forward:
# cdecl size at [entry ESP+4]; caller return and arguments survive tail jump.
 push ebp
 {load} mov ebp,esp
 pop ebp
 jmp operator_new_import
.equ operator_new_import,0x8f8c42
.section .note.GNU-stack,"",@progbits
