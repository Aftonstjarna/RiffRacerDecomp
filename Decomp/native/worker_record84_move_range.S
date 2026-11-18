# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x520bb0,0x520c37).
.intel_syntax noprefix
.code32
.text
.global original_worker_record84_move_range
original_worker_record84_move_range:
 push ebp
 mov.s ebp,esp
 push ebx
 mov.s ebx,edx
 cmp.s ecx,ebx
 je .empty
 mov edx,[ebp+8]
 push esi
 push edi
 lea esi,[ecx+0x38]
 lea edi,[edx+0x38]
 .check:
 test.s edx,edx
 je .advance
 movdqu xmm0,[esi-0x38]
 movdqu [edx],xmm0
 movdqu xmm0,[esi-0x28]
 movdqu [edi-0x28],xmm0
 movdqu xmm0,[esi-0x18]
 movdqu [edi-0x18],xmm0
 mov eax,[esi-8]
 mov [edi-8],eax
 mov eax,[esi-4]
 mov [edi-4],eax
 mov eax,[esi]
 mov [edi],eax
 mov eax,[esi+4]
 mov [edi+4],eax
 mov eax,[esi+8]
 mov [edi+8],eax
 mov eax,[esi+0xc]
 mov [edi+0xc],eax
 mov eax,[esi+0x10]
 mov [edi+0x10],eax
 mov eax,[esi+0x14]
 mov [edi+0x14],eax
 mov eax,[esi+0x18]
 mov [edi+0x18],eax
.advance:
 add esi,0x54
 add edx,0x54
 add edi,0x54
 lea ecx,[esi-0x38]
 cmp.s ecx,ebx
 jne .check
 pop edi
 pop esi
 mov.s eax,edx
 pop ebx
 pop ebp
 ret
.empty:
 mov eax,[ebp+8]
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
