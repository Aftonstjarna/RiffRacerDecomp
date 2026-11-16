.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58b360,0x58b3be); following two INT3 bytes excluded.
.equ CRT_FREE_IAT,0x92d3a4
.global original_audio_record36_dispose_buffers
original_audio_record36_dispose_buffers:
 push esi
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [CRT_FREE_IAT]
 mov eax,DWORD PTR [esi+0x10]
 test eax,eax
 je clear_second
 push eax
 call edi
 add esp,4
clear_second:
 mov DWORD PTR [esi+0x10],0
 mov DWORD PTR [esi+0x14],0
 mov DWORD PTR [esi+0x18],0
 mov eax,DWORD PTR [esi+4]
 test eax,eax
 je clear_first
 push eax
 call edi
 add esp,4
clear_first:
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
 mov DWORD PTR [esi+0xc],0
 mov eax,DWORD PTR [esi+0x20]
 test eax,eax
 je done
 push eax
 call edi
 add esp,4
done:
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
