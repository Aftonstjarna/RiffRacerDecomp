.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x008fc410,0x008fc417). CPU dispatcher 0x8fc1b0 tail-branches here.
# XMM0 holds two doubles on entry and return. Requires SSE4.1.
# Immediate 1 selects round toward negative infinity, with precision reporting enabled.
# No branches, memory operands, calls, stack arguments, or nonvolatile-register writes.
.global original_packed_double_floor_sse41
original_packed_double_floor_sse41:
    roundpd xmm0,xmm0,1
    ret
.section .note.GNU-stack,"",@progbits
