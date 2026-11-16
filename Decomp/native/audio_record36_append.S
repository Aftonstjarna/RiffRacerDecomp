.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x58b5a0..0x58b632 exclusive; both returns, no INT3 padding.
.equ CRT_MALLOC_IAT,0x92d39c
.equ CRT_REALLOC_IAT,0x92d398
.global original_audio_record36_append
original_audio_record36_append:
 push ebx
 push edi
 {load} mov edi,edx
 {load} mov ebx,ecx
 mov eax,DWORD PTR [edi]
 inc eax
 lea eax,[eax+eax*8]
 shl eax,2
 cmp DWORD PTR [ebx],0
 push eax
 jne reallocate
 call DWORD PTR [CRT_MALLOC_IAT]
 add esp,4
 jmp allocation_result
reallocate:
 push DWORD PTR [ebx]
 call DWORD PTR [CRT_REALLOC_IAT]
 add esp,8
allocation_result:
 test eax,eax
 jne initialize_record
 pop edi
 pop ebx
 ret
initialize_record:
 mov DWORD PTR [ebx],eax
 inc DWORD PTR [edi]
 mov eax,DWORD PTR [edi]
 lea ecx,[eax+eax*8]
 mov eax,DWORD PTR [ebx]
 mov DWORD PTR [eax+ecx*4-0x14],0
 mov DWORD PTR [eax+ecx*4-0x10],0
 mov DWORD PTR [eax+ecx*4-0xc],0
 mov DWORD PTR [eax+ecx*4-0x20],0
 mov DWORD PTR [eax+ecx*4-0x1c],0
 mov DWORD PTR [eax+ecx*4-0x18],0
 mov BYTE PTR [eax+ecx*4-0x24],0
 mov DWORD PTR [eax+ecx*4-8],0
 mov DWORD PTR [eax+ecx*4-4],0
 mov eax,DWORD PTR [edi]
 pop edi
 lea ecx,[eax+eax*8]
 mov eax,DWORD PTR [ebx]
 pop ebx
 lea eax,[eax+ecx*4]
 add eax,-0x24
 ret
.section .note.GNU-stack,"",@progbits
