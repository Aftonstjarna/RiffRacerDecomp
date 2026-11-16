.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x58b640,0x58b6a8); both returns included; INT3 padding excluded.
.equ DISPOSE_RECORD,0x58b300
.equ MALLOC_IAT,0x92d39c
.equ REALLOC_IAT,0x92d398
.equ FREE_IAT,0x92d3a4
.global original_audio_record32_remove_last
original_audio_record32_remove_last:
 push esi
 {load} mov esi,edx
 push edi
 {load} mov edi,ecx
 mov ecx,DWORD PTR [esi]
 cmp ecx,1
 jb done
 mov eax,DWORD PTR [edi]
 shl ecx,5
 add eax,-32
 {load} add ecx,eax
 call DISPOSE_RECORD
 mov eax,DWORD PTR [esi]
 cmp eax,1
 jbe release_array
 mov ecx,DWORD PTR [edi]
 dec eax
 shl eax,5
 push eax
 test ecx,ecx
 jne reallocate
 call DWORD PTR [MALLOC_IAT]
 add esp,4
 jmp allocation_result
reallocate:
 push ecx
 call DWORD PTR [REALLOC_IAT]
 add esp,8
allocation_result:
 test eax,eax
 je done
 mov DWORD PTR [edi],eax
 dec DWORD PTR [esi]
 pop edi
 pop esi
 ret
release_array:
 push DWORD PTR [edi]
 call DWORD PTR [FREE_IAT]
 mov DWORD PTR [edi],0
 add esp,4
 mov DWORD PTR [esi],0
done:
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
