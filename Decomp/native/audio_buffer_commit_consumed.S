.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e180,0x58e1ee); INT3 padding excluded.
.equ crt_free_iat,0x92d3a4
.global original_audio_buffer_commit_consumed
original_audio_buffer_commit_consumed:
 push esi
 mov.s esi,ecx
 push edi
 mov edi,DWORD PTR [esi]
 test edi,edi
 je finish
 push ebx
 jmp next_block
 {disp8} lea ecx,[ecx+0]
next_block:
 mov ecx,DWORD PTR [esi+0xc]
 cmp ecx,DWORD PTR [edi+4]
 jl done_blocks
 mov ebx,DWORD PTR [edi+0xc]
 test ebx,ebx
 jne account
 mov DWORD PTR [esi+4],ebx
account:
 mov eax,DWORD PTR [edi+4]
 add DWORD PTR [esi+0x14],eax
 sub.s ecx,DWORD PTR [edi+4]
 mov DWORD PTR [esi+0xc],ecx
 mov eax,DWORD PTR [edi+4]
 sub DWORD PTR [esi+8],eax
 mov eax,DWORD PTR [esi+0x20]
 cmp eax,DWORD PTR [esi+0x1c]
 jae release_block
 mov eax,DWORD PTR [esi+0x24]
 mov DWORD PTR [edi+0xc],eax
 inc DWORD PTR [esi+0x20]
 mov DWORD PTR [esi+0x24],edi
 jmp advance
release_block:
 push DWORD PTR [edi]
 call DWORD PTR [crt_free_iat]
 push edi
 call DWORD PTR [crt_free_iat]
 add esp,8
advance:
 mov.s edi,ebx
 test ebx,ebx
 jne next_block
done_blocks:
 pop ebx
finish:
 mov eax,DWORD PTR [esi+0xc]
 mov DWORD PTR [esi],edi
 pop edi
 mov DWORD PTR [esi+0x10],eax
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
