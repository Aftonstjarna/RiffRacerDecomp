# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0ae0,0x4f0b6c); three returns, INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_get_integer
.equ FLOAT_ZERO,0xa063ec
.equ NIL_VALUE,0x99a41c
original_script_table_get_integer:
 push ebp
 mov.s ebp,esp
 push ecx
 push edi
 mov.s edi,ecx
 lea eax,[edx-1]
 cmp eax,DWORD PTR [edi+0x1c]
 jae .Lhash
 mov eax,DWORD PTR [edi+0xc]
 pop edi
 lea eax,[eax+edx*8]
 add eax,-8
 mov.s esp,ebp
 pop ebp
 ret
.Lhash:
 movd xmm1,edx
 cvtdq2ps xmm1,xmm1
 ucomiss xmm1,DWORD PTR [FLOAT_ZERO]
 movss DWORD PTR [ebp-4],xmm1
 lahf
 test ah,0x44
 jp .Lbucket
 mov ecx,DWORD PTR [edi+0x10]
 jmp .Lprobe
.Lbucket:
 mov cl,BYTE PTR [edi+7]
 xor.s edx,edx
 mov eax,DWORD PTR [ebp-4]
 push esi
 mov esi,1
 shl esi,cl
 dec esi
 or esi,1
 div esi
 mov eax,DWORD PTR [edi+0x10]
 pop esi
 lea ecx,[edx+edx*4]
 lea ecx,[eax+ecx*4]
 jmp .Lprobe
 {disp8} lea ecx,[ecx+0]
.Lprobe:
 cmp DWORD PTR [ecx+0xc],3
 jne .Lnext
 movss xmm0,DWORD PTR [ecx+8]
 ucomiss xmm0,xmm1
 lahf
 test ah,0x44
 jnp .Lfound
.Lnext:
 mov ecx,DWORD PTR [ecx+0x10]
 test ecx,ecx
 jne .Lprobe
 mov eax,NIL_VALUE
 pop edi
 mov.s esp,ebp
 pop ebp
 ret
.Lfound:
 mov.s eax,ecx
 pop edi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
