# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5280b0,0x52811c); padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_application_worker_initialize_singleton
.equ constructor,0x43f310
original_application_worker_initialize_singleton:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8fd7ac
 mov eax,DWORD PTR fs:0
 push eax
 push ecx
 push esi
 mov eax,DWORD PTR ds:0xbaabc0
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov DWORD PTR fs:0,eax
 mov.s esi,ecx
 cmp DWORD PTR ds:0xbfcbb0,0
 jne .done
 push 0x13c
 call DWORD PTR ds:0x92d4b4
 add esp,4
 mov DWORD PTR [ebp-0x10],eax
 mov DWORD PTR [ebp-4],0
 test.s eax,eax
 je .null
 push esi
 mov.s ecx,eax
 call constructor
 jmp .store
.null:
 xor.s eax,eax
.store:
 mov DWORD PTR ds:0xbfcbb0,eax
.done:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
