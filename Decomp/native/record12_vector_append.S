# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4295d0.
.intel_syntax noprefix
.code32
.text
.global original_record12_vector_append
.equ grow_vector,0x429be0
original_record12_vector_append:
 push ebp
 mov.s ebp,esp
 push esi
 mov.s esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 mov ecx,DWORD PTR [esi+4]
 cmp.s edi,ecx
 jae external
 mov eax,DWORD PTR [esi]
 cmp.s eax,edi
 ja external
 sub.s edi,eax
 mov eax,0x2aaaaaab
 imul edi
 sar edx,1
 mov.s edi,edx
 shr edi,0x1f
 add.s edi,edx
 cmp ecx,DWORD PTR [esi+8]
 jne internal_ready
 push ecx
 mov.s ecx,esi
 call grow_vector
internal_ready:
 mov eax,DWORD PTR [esi]
 lea ecx,[edi+edi*2]
 lea eax,[eax+ecx*4]
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je finish
 movq xmm0,QWORD PTR [eax]
 movq QWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [eax+8]
 mov DWORD PTR [ecx+8],eax
 add DWORD PTR [esi+4],0xc
 pop edi
 pop esi
 pop ebp
 ret 4
external:
 cmp ecx,DWORD PTR [esi+8]
 jne external_ready
 push ecx
 mov.s ecx,esi
 call grow_vector
external_ready:
 mov ecx,DWORD PTR [esi+4]
 test ecx,ecx
 je finish
 movq xmm0,QWORD PTR [edi]
 movq QWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [edi+8]
 mov DWORD PTR [ecx+8],eax
finish:
 add DWORD PTR [esi+4],0xc
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
