# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x51ff50,0x51ffd9).
.intel_syntax noprefix
.code32
.text
.global original_worker_record84_reallocate
.equ move_records,0x520bb0
original_worker_record84_reallocate:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 push edi
 mov edi,[ebp+8]
 xor.s esi,esi
 mov.s ebx,ecx
 test.s edi,edi
 je .allocated
 cmp edi,0x30c30c3
 ja .failure
 imul eax,edi,0x54
 push eax
 call DWORD PTR ds:0x92d4b4
 mov.s esi,eax
 add esp,4
 test.s esi,esi
 jne .allocated
.failure:
 call DWORD PTR ds:0x92d164
.allocated:
 push DWORD PTR [ebp+8]
 mov edx,[ebx+4]
 mov ecx,[ebx]
 sub esp,8
 push esi
 call move_records
 mov ecx,[ebx+4]
 mov eax,0x30c30c31
 sub ecx,[ebx]
 add esp,0x10
 imul ecx
 sar edx,4
 mov.s eax,edx
 shr eax,0x1f
 add.s eax,edx
 mov [ebp+8],eax
 mov eax,[ebx]
 test.s eax,eax
 je .released
 push eax
 call DWORD PTR ds:0x92d4b0
 add esp,4
.released:
 imul eax,edi,0x54
 pop edi
 mov [ebx],esi
 add.s eax,esi
 mov [ebx+8],eax
 imul eax,DWORD PTR [ebp+8],0x54
 add.s eax,esi
 pop esi
 mov [ebx+4],eax
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
