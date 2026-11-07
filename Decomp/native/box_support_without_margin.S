# Mechanically transcribed reference evidence, NOT high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4389b0,0x438a12); excludes following INT3 padding.
# ECX=this; stack arguments output and direction; EAX=output; ret 8.
# Vtable 0x9f98d0 slot +0x3c. No call dependencies; sign mask at 0xa071e0.
.intel_syntax noprefix
.code32
.text
.global original_box_support_without_margin
original_box_support_without_margin:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0xc]
 xorps xmm4,xmm4
 movss xmm3,DWORD PTR [sign_mask]
 movss xmm1,DWORD PTR [ecx+0x24]
 movss xmm0,DWORD PTR [eax+0x8]
 comiss xmm0,xmm4
 jae z_nonnegative
 xorps xmm1,xmm3
z_nonnegative:
 movss xmm0,DWORD PTR [eax+0x4]
 comiss xmm0,xmm4
 movss xmm2,DWORD PTR [ecx+0x20]
 jae y_nonnegative
 xorps xmm2,xmm3
y_nonnegative:
 movss xmm0,DWORD PTR [eax]
 comiss xmm0,xmm4
 movss xmm0,DWORD PTR [ecx+0x1c]
 jae x_nonnegative
 xorps xmm0,xmm3
x_nonnegative:
 mov eax,DWORD PTR [ebp+0x8]
 movss DWORD PTR [eax],xmm0
 movss DWORD PTR [eax+0x4],xmm2
 movss DWORD PTR [eax+0x8],xmm1
 mov DWORD PTR [eax+0xc],0
 pop ebp
 ret 8
.equ sign_mask,0xa071e0
.section .note.GNU-stack,"",@progbits
