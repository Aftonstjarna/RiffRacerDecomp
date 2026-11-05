# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f925e..0x8f92ef (exclusive); both RET paths included.
# ECX=low32, EDX=high32 unsigned input; XMM0=double; plain RET.
# Clobbers EAX, ECX, XMM0..XMM6 and flags; EDX unchanged; no stack frame/calls.
# Reads original constants at 0x9824e0/0x9824e8 and 0x982554..0x98255f.
.intel_syntax noprefix
.code32
.text
.global original_unsigned64_to_double
original_unsigned64_to_double:
.L8f925e:
 test   edx,edx
.L8f9260:
 jne .L8f9277
.L8f9262:
 cvtsi2sd xmm0,ecx
.L8f9266:
 shr    ecx,0x1f
.L8f9269:
 movsd  xmm1,QWORD PTR [ecx*8+0x9824e0]
.L8f9272:
 addsd  xmm0,xmm1
.L8f9276:
 ret
.L8f9277:
 movd   xmm4,DWORD PTR [0x982558]
.L8f927f:
 movd   xmm5,DWORD PTR [0x98255c]
.L8f9287:
 movd   xmm6,DWORD PTR [0x982554]
.L8f928f:
 movd   xmm0,ecx
.L8f9293:
 movd   xmm1,edx
.L8f9297:
 punpckldq xmm0,xmm1
.L8f929b:
 mov    eax,0x20
.L8f92a0:
 bsr    ecx,edx
.L8f92a3:
 {load} sub    eax,ecx
.L8f92a5:
 movd   xmm2,eax
.L8f92a9:
 psllq  xmm0,xmm2
.L8f92ad:
 {load} movdqa xmm3,xmm0
.L8f92b1:
 psllq  xmm3,0x33
.L8f92b6:
 psrlq  xmm3,0x33
.L8f92bb:
 {load} movdqa xmm1,xmm3
.L8f92bf:
 psrlq  xmm0,0xd
.L8f92c4:
 psllq  xmm0,0x1
.L8f92c9:
 pcmpgtd xmm3,xmm4
.L8f92cd:
 punpckldq xmm3,xmm3
.L8f92d1:
 psubq  xmm0,xmm3
.L8f92d5:
 pcmpgtd xmm1,xmm5
.L8f92d9:
 punpckldq xmm1,xmm1
.L8f92dd:
 psubq  xmm0,xmm1
.L8f92e1:
 psubq  xmm6,xmm2
.L8f92e5:
 psllq  xmm6,0x34
.L8f92ea:
 paddq  xmm0,xmm6
.L8f92ee:
 ret
.section .note.GNU-stack,"",@progbits
