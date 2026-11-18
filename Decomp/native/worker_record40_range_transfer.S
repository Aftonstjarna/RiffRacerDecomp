# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x520a60.
.intel_syntax noprefix
.code32
.text
.global original_worker_record40_range_transfer
original_worker_record40_range_transfer:
 push ebp
 mov.s ebp,esp
 push ebx
 mov.s ebx,edx
 cmp.s ecx,ebx
 je .Lempty
 mov edx,DWORD PTR [ebp+8]
 push esi
 push edi
 lea esi,[ecx+0x18]
 lea edi,[edx+0x18]
.Lloop:
 test edx,edx
 je .Ladvance
 movdqu xmm0,XMMWORD PTR [esi-0x18]
 movdqu XMMWORD PTR [edx],xmm0
 mov eax,DWORD PTR [esi-8]
 mov DWORD PTR [edi-8],eax
 mov eax,DWORD PTR [esi-4]
 mov DWORD PTR [edi-4],eax
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [edi],eax
 mov eax,DWORD PTR [esi+4]
 mov DWORD PTR [edi+4],eax
 mov eax,DWORD PTR [esi+8]
 mov DWORD PTR [edi+8],eax
 mov eax,DWORD PTR [esi+0xc]
 mov DWORD PTR [edi+0xc],eax
.Ladvance:
 add esi,0x28
 add edx,0x28
 add edi,0x28
 lea ecx,[esi-0x18]
 cmp.s ecx,ebx
 jne .Lloop
 pop edi
 pop esi
 mov.s eax,edx
 pop ebx
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
