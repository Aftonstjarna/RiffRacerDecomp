.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x008fc1b0,0x008fc1c2); following INT3 padding excluded.
# Two packed doubles enter/return in XMM0; tail targets retain caller return address.
# Signed CPU-level >= 2 selects SSE4.1; all other values select SSE2.
.equ CPU_LEVEL,0x00bfb160
.equ FLOOR_SSE41,0x008fc410
.equ FLOOR_SSE2,0x008fc3c0
.global original_packed_double_floor_dispatch
original_packed_double_floor_dispatch:
    cmp DWORD PTR [CPU_LEVEL],2
    jge FLOOR_SSE41
    jmp FLOOR_SSE2
.section .note.GNU-stack,"",@progbits
