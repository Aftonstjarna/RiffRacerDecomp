# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x8f8f50..0x8f90ed exclusive; alternate entries 0x8f8f5f and 0x8f8f6e.
.intel_syntax noprefix
.code32
.text
.global original_sse_float_to_integer
.equ conversion_exception,0x8f90ed
original_sse_float_to_integer:
 mov    ecx,0x1
 movsd  xmm5,QWORD PTR [0x982518]
 jmp .L8f8f7b
# Alternate mode-2 entry, retained as part of the shared original span.
.L8f8f5f:
 mov    ecx,0x2
 movsd  xmm5,QWORD PTR [0x982520]
 jmp .L8f8f7b
# Alternate mode-3 entry.
.L8f8f6e:
 mov    ecx,0x3
 movsd  xmm5,QWORD PTR [0x982518]
.L8f8f7b:
 movd   eax,xmm0
 and    eax,0x7fffffff
 cmp    eax,0x7f800000
 jae .L8f90db
 cvtss2sd xmm0,xmm0
 cmp    ecx,0x2
 jne .L8f8fb0
 movsd  xmm2,QWORD PTR [0x982538]
 comisd xmm0,xmm2
 jbe .L8f8fb0
 mov    edx,0x10
 call conversion_exception
.L8f8fb0:
 comisd xmm0,xmm5
 jae .L8f90db
 movsd  xmm6,QWORD PTR [0x982510]
 comisd xmm0,xmm6
 jb .L8f90db
 movdqa xmm1,xmm0
 psllq  xmm1,0x1
 psrlq  xmm1,0x1
 cmp    ecx,0x1
 je .L8f9019
 movsd  xmm2,QWORD PTR [0x982530]
 comisd xmm1,xmm2
 ja .L8f9019
 xorpd  xmm2,xmm2
 comisd xmm1,xmm2
 je .L8f9019
 push   eax
 fstcw  WORD PTR [esp]
 mov    ax,WORD PTR [esp]
 test   ax,0x10
 pop    eax
 jne .L8f9019
 mov    edx,0x2
 call conversion_exception
 xor.s    eax,eax
 mov    edx,0x80000000
 ret
.L8f9019:
 xorpd  xmm6,xmm6
 comisd xmm1,xmm6
 je .L8f90cd
 movsd  xmm3,QWORD PTR [0x9824f0]
 movsd  xmm4,QWORD PTR [0x9824f8]
 movd   xmm5,DWORD PTR [0x982550]
 movdqa xmm6,xmm0
 cmpeqsd xmm6,xmm1
 movdqa xmm2,xmm1
 pand   xmm2,xmm3
 por    xmm2,xmm4
 psrlq  xmm1,0x34
 movdqa xmm4,xmm1
 psubq  xmm4,xmm5
 movdqa xmm3,xmm2
 psllq  xmm3,xmm4
 movdqa xmm4,xmm5
 psubq  xmm4,xmm1
 movdqa xmm7,xmm2
 psrlq  xmm7,xmm4
 pcmpgtd xmm1,xmm5
 punpckldq xmm1,xmm1
 pand   xmm3,xmm1
 pandn  xmm1,xmm7
 por    xmm1,xmm3
 pxor   xmm5,xmm5
 psubq  xmm5,xmm1
 pand   xmm1,xmm6
 pandn  xmm6,xmm5
 por    xmm6,xmm1
 movd   eax,xmm4
 cmp    eax,0x0
 jle .L8f90cd
 psllq  xmm7,xmm4
 pxor   xmm2,xmm7
 movd   eax,xmm2
 psrldq xmm2,0x4
 movd   edx,xmm2
 or.s     eax,edx
 je .L8f90cd
 mov    edx,0x10
 call conversion_exception
.L8f90cd:
 movd   eax,xmm6
 psrldq xmm6,0x4
 movd   edx,xmm6
 ret
.L8f90db:
 mov    edx,0x8
 call conversion_exception
 xor.s    eax,eax
 mov    edx,0x80000000
 ret
.section .note.GNU-stack,"",@progbits
