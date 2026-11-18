.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x4248e0..0x4249c0.
.global original_worker_resource_parameter_update
original_worker_resource_parameter_update:
 push ebp
 {load} mov ebp,esp
 push ecx
 mov eax,DWORD PTR [ebp+0x18]
 mov DWORD PTR [ebp-4],ecx
 push esi
 push edi
 cmp eax,2
 jne .Lother
 {load} xor eax,eax
 {load} mov esi,eax
 lea edi,[eax+2]
 jmp .Lbegin
.Lother:
 lea edi,[eax+1]
 {load} mov esi,eax
 {load} cmp eax,edi
 jge .Lexit
.Lbegin:
 movss xmm1,DWORD PTR [0xa06558]
 divss xmm1,DWORD PTR [ebp+0xc]
 push ebx
 mov ebx,DWORD PTR [ebp+0x14]
 lea eax,[eax+ebx*2]
 lea eax,[eax+0x48]
 lea edx,[ecx+eax*4]
 movss xmm2,DWORD PTR [ebp+8]
 movss xmm3,DWORD PTR [0xa068ac]
 {load} mov edi,edi
.Lloop:
 movss xmm0,DWORD PTR [edx-0xc0]
 ucomiss xmm0,xmm2
 lahf
 test ah,0x44
 mov eax,DWORD PTR [ebp+0x10]
 jp .Lchange
 cmp eax,DWORD PTR [edx]
 jne .Lchange
 comiss xmm0,xmm2
 movss DWORD PTR [edx-0x60],xmm2
 movss DWORD PTR [edx-0x120],xmm1
 jbe .Lnext
 movaps xmm0,xmm1
 mulss xmm0,xmm3
 movss DWORD PTR [edx-0x120],xmm0
 jmp .Lnext
.Lchange:
 comiss xmm0,xmm2
 mov DWORD PTR [edx],eax
 movss DWORD PTR [edx-0x60],xmm2
 movss DWORD PTR [edx-0x120],xmm1
 jbe .Lmark
 movaps xmm0,xmm1
 mulss xmm0,xmm3
 movss DWORD PTR [edx-0x120],xmm0
.Lmark:
 lea ecx,[ebx+0x80]
 lea eax,[esi+ecx*2]
 {load} add eax,ecx
 mov ecx,DWORD PTR [ebp-4]
 mov BYTE PTR [eax+ecx],1
 lea eax,[ecx+ebx*2]
 mov BYTE PTR [ebx+eax+0x182],1
.Lnext:
 inc esi
 add edx,4
 {load} cmp esi,edi
 jl .Lloop
 pop ebx
.Lexit:
 pop edi
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret 0x14
.section .note.GNU-stack,"",@progbits
