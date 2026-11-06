# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4adb10,0x4adb72); complete common return, no INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ unsigned_correction,0xa071b0
.global original_device_sampler_bias_update
original_device_sampler_bias_update:
 push ebp
 mov.s ebp,esp
 cmp BYTE PTR [ecx+0x9a8],0
 je .Lreturn
 mov edx,DWORD PTR [ebp+8]
 push esi
 mov esi,DWORD PTR [ebp+0x10]
 mov.s eax,esi
 shr eax,0x1f
 movd xmm0,esi
 cvtdq2pd xmm0,xmm0
 addsd xmm0,QWORD PTR [eax*8+unsigned_correction]
 cvtpd2ps xmm1,xmm0
 movss xmm0,DWORD PTR [ecx+edx*4+0x9ac]
 ucomiss xmm0,xmm1
 lahf
 test ah,0x44
 jnp .Lrestore
 movss xmm0,DWORD PTR [ebp+0x10]
 movss DWORD PTR [ecx+edx*4+0x9ac],xmm0
 mov eax,DWORD PTR [ecx+0x78]
 push esi
 push 8
 push edx
 mov ecx,DWORD PTR [eax]
 push eax
 call DWORD PTR [ecx+0x114]
.Lrestore:
 pop esi
.Lreturn:
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
