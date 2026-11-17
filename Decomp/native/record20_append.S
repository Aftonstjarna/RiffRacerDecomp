.intel_syntax noprefix
.code32
.text
.global original_record20_append
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x52c610.
.equ grow_record20,0x52c7e0
original_record20_append:
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
 mov eax,0x66666667
 imul edi
 sar edx,3
 mov.s edi,edx
 shr edi,0x1f
 add.s edi,edx
 cmp ecx,DWORD PTR [esi+8]
 jne internal_ready
 push ecx
 mov.s ecx,esi
 call grow_record20
internal_ready:
 mov eax,DWORD PTR [esi]
 lea ecx,[edi+edi*4]
 lea eax,[eax+ecx*4]
 mov ecx,DWORD PTR [esi+4]
 test.s ecx,ecx
 je finish
 movdqu xmm0,XMMWORD PTR [eax]
 pop edi
 movdqu XMMWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [eax+0x10]
 mov DWORD PTR [ecx+0x10],eax
 add DWORD PTR [esi+4],0x14
 pop esi
 pop ebp
 ret 4
external:
 cmp ecx,DWORD PTR [esi+8]
 jne external_ready
 push ecx
 mov.s ecx,esi
 call grow_record20
external_ready:
 mov ecx,DWORD PTR [esi+4]
 test.s ecx,ecx
 je finish
 movdqu xmm0,XMMWORD PTR [edi]
 movdqu XMMWORD PTR [ecx],xmm0
 mov eax,DWORD PTR [edi+0x10]
 mov DWORD PTR [ecx+0x10],eax
finish:
 add DWORD PTR [esi+4],0x14
 pop edi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
