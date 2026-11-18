# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x51fd40.
.intel_syntax noprefix
.code32
.text
.global original_worker_record56_reallocate
.equ move_records,0x520ad0
original_worker_record56_reallocate:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov.s ebx,ecx
 push edi
 xor.s edi,edi
 test.s esi,esi
 je .Lallocated
 cmp esi,0x4924924
 ja .Lfailure
 lea eax,[esi*8]
 sub.s eax,esi
 shl eax,3
 push eax
 call DWORD PTR [0x92d4b4]
 mov.s edi,eax
 add esp,4
 test.s edi,edi
 jne .Lallocated
.Lfailure:
 call DWORD PTR [0x92d164]
.Lallocated:
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 mov ecx,DWORD PTR [ebx]
 sub esp,8
 push edi
 call move_records
 mov ecx,DWORD PTR [ebx+4]
 mov eax,0x92492493
 sub ecx,DWORD PTR [ebx]
 add esp,0x10
 imul ecx
 mov eax,DWORD PTR [ebx]
 add.s edx,ecx
 sar edx,5
 mov.s ecx,edx
 shr ecx,0x1f
 add.s ecx,edx
 mov DWORD PTR [ebp+8],ecx
 test.s eax,eax
 je .Lupdate
 push eax
 call DWORD PTR [0x92d4b0]
 mov ecx,DWORD PTR [ebp+8]
 add esp,4
.Lupdate:
 lea eax,[esi*8]
 mov DWORD PTR [ebx],edi
 sub.s eax,esi
 lea eax,[edi+eax*8]
 mov DWORD PTR [ebx+8],eax
 lea eax,[ecx*8]
 sub.s eax,ecx
 lea eax,[edi+eax*8]
 pop edi
 pop esi
 mov DWORD PTR [ebx+4],eax
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
