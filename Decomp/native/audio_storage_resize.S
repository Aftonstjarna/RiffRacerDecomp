.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5ae020,0x5ae092); all three returns included.
.equ FREE_IAT,0x92d3a4
.equ MALLOC_IAT,0x92d39c
.equ REALLOC_IAT,0x92d398
.global original_audio_storage_resize
original_audio_storage_resize:
 push esi
 push edi
 {load} mov edi,edx
 {load} mov esi,ecx
 test edi,edi
 jne nonzero
 cmp DWORD PTR [esi+4],edx
 je clear
 mov eax,DWORD PTR [esi]
 test eax,eax
 je clear
 push eax
 call DWORD PTR [FREE_IAT]
 add esp,4
clear:
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
success_existing:
 pop edi
 mov eax,1
 pop esi
 ret
nonzero:
 cmp DWORD PTR [esi+4],edi
 je success_existing
 mov eax,DWORD PTR [esi]
 push edi
 test eax,eax
 jne reallocate
 call DWORD PTR [MALLOC_IAT]
 add esp,4
 jmp allocated
reallocate:
 push eax
 call DWORD PTR [REALLOC_IAT]
 add esp,8
allocated:
 test eax,eax
 je failed
 mov DWORD PTR [esi+4],edi
 mov DWORD PTR [esi],eax
 mov eax,1
 pop edi
 pop esi
 ret
failed:
 pop edi
 {load} xor eax,eax
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
