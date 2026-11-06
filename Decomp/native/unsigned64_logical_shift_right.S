# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc380,0x8fc39f); all three returns included; INT3 excluded.
# Register ABI: EDX:EAX input/result, CL unsigned count; no stack arguments.
.intel_syntax noprefix
.code32
.text
.global original_unsigned64_logical_shift_right
original_unsigned64_logical_shift_right:
    cmp cl,0x40
    jae .Lzero
    cmp cl,0x20
    jae .Lhigh
    shrd eax,edx,cl
    shr edx,cl
    ret
.Lhigh:
    {load} mov eax,edx
    {load} xor edx,edx
    and cl,0x1f
    shr eax,cl
    ret
.Lzero:
    {load} xor eax,eax
    {load} xor edx,edx
    ret
.section .note.GNU-stack,"",@progbits
