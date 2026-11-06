# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8fc260, complete 33-byte function.
.intel_syntax noprefix
.code32
.text
.global original_signed64_arithmetic_shift_right
original_signed64_arithmetic_shift_right:
    cmp cl, 0x40
    jae .Lsign
    cmp cl, 0x20
    jae .Lhigh
    shrd eax, edx, cl
    sar edx, cl
    ret
.Lhigh:
    {load} mov eax, edx
    sar edx, 0x1f
    and cl, 0x1f
    sar eax, cl
    ret
.Lsign:
    sar edx, 0x1f
    {load} mov eax, edx
    ret
.section .note.GNU-stack,"",@progbits
