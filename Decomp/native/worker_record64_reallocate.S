.intel_syntax noprefix
.code32
.text
.global original_worker_record64_reallocate
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x51fe60..0x51fedf exclusive.
.equ move_records,0x520b60
original_worker_record64_reallocate:
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+0x8]
 xor.s ebx,ebx
 push edi
 mov.s edi,ecx
 mov DWORD PTR [ebp-0x4],edi
 test esi,esi
 je .Lallocated
 cmp esi,0x3ffffff
 ja .Lfailure
 mov.s eax,esi
 shl eax,0x6
 push eax
 call DWORD PTR [0x92d4b4]
 mov.s ebx,eax
 add esp,0x4
 test ebx,ebx
 jne .Lallocated
.Lfailure:
 call DWORD PTR [0x92d164]
.Lallocated:
 push DWORD PTR [ebp+0x8]
 mov edx,DWORD PTR [edi+0x4]
 mov ecx,DWORD PTR [edi]
 sub esp,0x8
 push ebx
 call move_records
 mov eax,DWORD PTR [edi]
 add esp,0x10
 mov edi,DWORD PTR [edi+0x4]
 sub.s edi,eax
 test eax,eax
 je .Lupdate
 push eax
 call DWORD PTR [0x92d4b0]
 add esp,0x4
.Lupdate:
 mov eax,DWORD PTR [ebp-0x4]
 and edi,0xffffffc0
 shl esi,0x6
 add.s esi,ebx
 add.s edi,ebx
 mov DWORD PTR [eax+0x4],edi
 pop edi
 mov DWORD PTR [eax+0x8],esi
 pop esi
 mov DWORD PTR [eax],ebx
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 0x4
.section .note.GNU-stack,"",@progbits
