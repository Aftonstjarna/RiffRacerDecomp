.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58b510,0x58b59d); both returns included, INT3 padding excluded.
.equ CRT_MALLOC_IAT,0x92d39c
.equ CRT_REALLOC_IAT,0x92d398
.global original_audio_record32_append
original_audio_record32_append:
 push esi
 {load} mov esi,edx
 push edi
 {load} mov edi,ecx
 mov eax,DWORD PTR [esi]
 inc eax
 mov edx,DWORD PTR [edi]
 shl eax,5
 push eax
 test edx,edx
 jne reallocate
 call DWORD PTR [CRT_MALLOC_IAT]
 add esp,4
 jmp allocation_result
reallocate:
 push edx
 call DWORD PTR [CRT_REALLOC_IAT]
 add esp,8
allocation_result:
 test eax,eax
 jne initialize_record
 pop edi
 pop esi
 ret
initialize_record:
 mov DWORD PTR [edi],eax
 inc DWORD PTR [esi]
 mov ecx,DWORD PTR [esi]
 mov eax,DWORD PTR [edi]
 shl ecx,5
 mov DWORD PTR [ecx+eax-0xc],0
 mov DWORD PTR [ecx+eax-8],0
 mov DWORD PTR [ecx+eax-4],0
 mov DWORD PTR [ecx+eax-0x18],0
 mov DWORD PTR [ecx+eax-0x14],0
 mov DWORD PTR [ecx+eax-0x10],0
 mov DWORD PTR [ecx+eax-0x1d],0
 mov WORD PTR [ecx+eax-0x20],0
 mov BYTE PTR [ecx+eax-0x1e],0
 mov ecx,DWORD PTR [esi]
 mov eax,DWORD PTR [edi]
 shl ecx,5
 add eax,-0x20
 pop edi
 {load} add eax,ecx
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
