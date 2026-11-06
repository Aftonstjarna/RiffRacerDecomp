# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f99a0,0x8f99bf). All three returns included; INT3 excluded.
# Register ABI: input/output EDX:EAX, unsigned count CL; no stack arguments.
# CL is masked on the 32..63 path. Flags are not preserved.
.intel_syntax noprefix
.code32
.text
.global original_u64_shift_left
original_u64_shift_left:
 cmp cl,0x40
 jae .Lzero
 cmp cl,0x20
 jae .Lhigh
 shld edx,eax,cl
 shl eax,cl
 ret
.Lhigh:
 {load} mov edx,eax
 {load} xor eax,eax
 and cl,0x1f
 shl edx,cl
 ret
.Lzero:
 {load} xor eax,eax
 {load} xor edx,edx
 ret
.section .note.GNU-stack,"",@progbits
