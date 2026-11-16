.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58df50,0x58dfc0); next function begins immediately.
# ECX=buffer; no stack arguments. Preserves EBX/ESI/EDI/EBP.
.equ crt_free_iat,0x92d3a4
.equ rebalance_cache,0x58deb0
.global original_audio_buffer_reset
original_audio_buffer_reset:
 push esi
 mov.s esi,ecx
 cmp DWORD PTR [esi],0
 je .Lreset
 push ebx
 mov ebx,DWORD PTR [crt_free_iat]
 push edi
.Ldrain:
 mov edi,DWORD PTR [esi]
 mov eax,DWORD PTR [edi+0xc]
 mov DWORD PTR [esi],eax
 mov eax,DWORD PTR [esi+0x20]
 cmp eax,DWORD PTR [esi+0x1c]
 jae .Lfree
 # Cache a detached active node while below the unsigned cache limit.
 mov eax,DWORD PTR [esi+0x24]
 mov DWORD PTR [edi+0xc],eax
 inc DWORD PTR [esi+0x20]
 mov DWORD PTR [esi+0x24],edi
 jmp .Lnext
.Lfree:
 push DWORD PTR [edi]
 call ebx
 push edi
 call ebx
 add esp,8
.Lnext:
 cmp DWORD PTR [esi],0
 jne .Ldrain
 pop edi
 pop ebx
.Lreset:
 mov.s ecx,esi
 call rebalance_cache
 # Rebalance failure is not checked; its EAX value survives these stores.
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+0x10],0
 mov DWORD PTR [esi+0x14],0
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
