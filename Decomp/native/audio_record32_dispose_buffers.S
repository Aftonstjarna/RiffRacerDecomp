.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA span [0x58b300,0x58b351); following INT3 padding excluded.
.equ free_iat,0x92d3a4
.global original_audio_record32_dispose_buffers
original_audio_record32_dispose_buffers:
 push esi
 {load} mov esi,ecx
 mov eax,DWORD PTR [esi+0x14]
 test eax,eax
 je clear_second_fields
 push eax
 call DWORD PTR [free_iat]
 add esp,4
clear_second_fields:
 mov DWORD PTR [esi+0x14],0
 mov DWORD PTR [esi+0x18],0
 mov DWORD PTR [esi+0x1c],0
 mov eax,DWORD PTR [esi+0x8]
 test eax,eax
 je clear_first_fields
 push eax
 call DWORD PTR [free_iat]
 add esp,4
clear_first_fields:
 mov DWORD PTR [esi+0x8],0
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+0x10],0
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
