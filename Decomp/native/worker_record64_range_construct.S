.intel_syntax noprefix
.code32
.text
.global original_worker_record64_range_construct
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x520b60..0x520ba1 exclusive.
.equ record_tail_construct,0x427010
original_worker_record64_range_construct:
 push ebp
 mov.s ebp,esp
 push ebx
 push edi
 mov.s ebx,edx
 mov.s edi,ecx
 cmp.s edi,ebx
 je .Lempty
 push esi
 mov esi,DWORD PTR [ebp+8]
.Lloop:
 test esi,esi
 je .Lnext
 movdqu xmm0,XMMWORD PTR [edi]
 lea eax,[edi+0x10]
 push eax
 lea ecx,[esi+0x10]
 movdqu XMMWORD PTR [esi],xmm0
 call record_tail_construct
.Lnext:
 add edi,0x40
 add esi,0x40
 cmp.s edi,ebx
 jne .Lloop
 mov.s eax,esi
 pop esi
 pop edi
 pop ebx
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop edi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
