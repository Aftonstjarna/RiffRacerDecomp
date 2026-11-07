# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438a20,0x438aa9); excludes trailing INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_box_batched_support_without_margin
original_box_batched_support_without_margin:
 push ebp
 mov.s ebp,esp
 push edi
 mov edi,DWORD PTR [ebp+0x10]
 test edi,edi
 jle done
 mov eax,DWORD PTR [ebp+8]
 xorps xmm3,xmm3
 movss xmm4,DWORD PTR [sign_mask]
 push esi
 mov esi,DWORD PTR [ebp+0xc]
 add esi,0xc
 lea edx,[eax+4]
 sub DWORD PTR [ebp+0xc],eax
 mov eax,DWORD PTR [ebp+0xc]
 {disp32} lea esp,[esp+0]
loop_support:
 movss xmm0,DWORD PTR [edx+4]
 comiss xmm0,xmm3
 movss xmm2,DWORD PTR [ecx+0x24]
 jae z_nonnegative
 xorps xmm2,xmm4
z_nonnegative:
 movss xmm0,DWORD PTR [edx]
 comiss xmm0,xmm3
 movss xmm1,DWORD PTR [ecx+0x20]
 jae y_nonnegative
 xorps xmm1,xmm4
y_nonnegative:
 movss xmm0,DWORD PTR [edx-4]
 comiss xmm0,xmm3
 movss xmm0,DWORD PTR [ecx+0x1c]
 jae x_nonnegative
 xorps xmm0,xmm4
x_nonnegative:
 movss DWORD PTR [esi-0xc],xmm0
 movss DWORD PTR [eax+edx],xmm1
 add edx,0x10
 movss DWORD PTR [esi-4],xmm2
 mov DWORD PTR [esi],0
 add esi,0x10
 dec edi
 jne loop_support
 pop esi
done:
 pop edi
 pop ebp
 ret 0xc
.equ sign_mask,0xa071e0
.section .note.GNU-stack,"",@progbits
