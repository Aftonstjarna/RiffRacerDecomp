.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58b6b0,0x58b720); both returns included.
.equ DISPOSE_RECORD,0x58b360
.equ MALLOC_IAT,0x92d39c
.equ REALLOC_IAT,0x92d398
.equ FREE_IAT,0x92d3a4
.global original_audio_record36_remove_last
original_audio_record36_remove_last:
 push ebx
 push edi
 {load} mov edi,edx
 {load} mov ebx,ecx
 mov eax,DWORD PTR [edi]
 cmp eax,1
 jb done
 push esi
 lea esi,[eax+eax*8]
 mov eax,DWORD PTR [ebx]
 lea esi,[esi-9]
 lea ecx,[eax+esi*4]
 call DISPOSE_RECORD
 mov eax,DWORD PTR [edi]
 pop esi
 cmp eax,1
 jbe release_array
 mov ecx,DWORD PTR [ebx]
 lea eax,[eax+eax*8]
 add eax,-9
 shl eax,2
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
 mov DWORD PTR [ebx],eax
 dec DWORD PTR [edi]
 pop edi
 pop ebx
 ret
release_array:
 push DWORD PTR [ebx]
 call DWORD PTR [FREE_IAT]
 mov DWORD PTR [ebx],0
 add esp,4
 mov DWORD PTR [edi],0
done:
 pop edi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
