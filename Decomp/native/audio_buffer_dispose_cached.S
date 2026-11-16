.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58de70,0x58dead); excludes following INT3 padding.
# ECX=audio buffer; preserves EBX/ESI/EDI; no stack arguments, no defined result.
.equ crt_free_iat,0x92d3a4
.global original_audio_buffer_dispose_cached
original_audio_buffer_dispose_cached:
 push ebx
 mov.s ebx,ecx
 push edi
 mov edi,DWORD PTR [ebx+0x24]
 test edi,edi
 je .Lclear
 push esi
 {disp8} lea esp,[esp+0]
.Lfree:
 push DWORD PTR [edi]
 mov esi,DWORD PTR [edi+0xc]
 call DWORD PTR [crt_free_iat]
 push edi
 call DWORD PTR [crt_free_iat]
 add esp,8
 mov.s edi,esi
 test esi,esi
 jne .Lfree
 pop esi
.Lclear:
 pop edi
 mov DWORD PTR [ebx+0x20],0
 mov DWORD PTR [ebx+0x24],0
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
