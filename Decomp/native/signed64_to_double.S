# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f92ef,0x8f931d); both returns and backward tail branch included.
# Signed EDX:ECX input; double in XMM0; plain RET, no stack arguments.
# External unsigned helper is already registered. Sign constant is -0.0.
.intel_syntax noprefix
.code32
.text
.global original_signed64_to_double
original_signed64_to_double:
 {load} mov eax,ecx
 sar eax,31
 {load} cmp eax,edx
 jne .Lwide
 cvtsi2sd xmm0,ecx
 ret
.Lwide:
 test edx,edx
 jge unsigned_convert
 movsd xmm7,QWORD PTR [sign_mask]
 neg ecx
 adc edx,0
 neg edx
 call unsigned_convert
 orps xmm0,xmm7
 ret
.equ unsigned_convert,0x8f925e
.equ sign_mask,0x982500
.section .note.GNU-stack,"",@progbits
