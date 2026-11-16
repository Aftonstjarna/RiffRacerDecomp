.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58deb0,0x58df48); following INT3 padding excluded.
# ECX=buffer; no stack arguments; EAX=0 or -1; preserves EBX/ESI/EDI/EBP.
.equ crt_free_iat,0x92d3a4
.equ crt_malloc_iat,0x92d39c
.global original_audio_buffer_rebalance_cache
original_audio_buffer_rebalance_cache:
 push ebx
 mov ebx,DWORD PTR [crt_free_iat]
 push esi
 mov.s esi,ecx
 push edi
 mov eax,DWORD PTR [esi+0x20]
 cmp eax,DWORD PTR [esi+0x1c]
 jbe .Lgrow_check
.Ltrim:
 mov edi,DWORD PTR [esi+0x24]
 mov eax,DWORD PTR [edi+0xc]
 mov DWORD PTR [esi+0x24],eax
 push DWORD PTR [edi]
 call ebx
 push edi
 call ebx
 dec DWORD PTR [esi+0x20]
 add esp,8
 mov eax,DWORD PTR [esi+0x20]
 cmp eax,DWORD PTR [esi+0x1c]
 ja .Ltrim
.Lgrow_check:
 mov eax,DWORD PTR [esi+0x20]
 cmp eax,DWORD PTR [esi+0x1c]
 jae .Lsuccess
 mov ebx,DWORD PTR [crt_malloc_iat]
 nop
.Lgrow:
 push 0x10
 call ebx
 mov.s edi,eax
 add esp,4
 test edi,edi
 je .Lfailure
 mov ecx,DWORD PTR [esi+0x18]
 push ecx
 mov DWORD PTR [edi+8],ecx
 call ebx
 add esp,4
 mov DWORD PTR [edi],eax
 test eax,eax
 je .Lfree_failed_node
 mov DWORD PTR [edi+0xc],0
 mov DWORD PTR [edi+4],0
 mov eax,DWORD PTR [esi+0x24]
 mov DWORD PTR [edi+0xc],eax
 inc DWORD PTR [esi+0x20]
 mov eax,DWORD PTR [esi+0x20]
 mov DWORD PTR [esi+0x24],edi
 cmp eax,DWORD PTR [esi+0x1c]
 jb .Lgrow
.Lsuccess:
 pop edi
 pop esi
 xor.s eax,eax
 pop ebx
 ret
.Lfree_failed_node:
 push edi
 call DWORD PTR [crt_free_iat]
 add esp,4
.Lfailure:
 pop edi
 pop esi
 or eax,-1
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
