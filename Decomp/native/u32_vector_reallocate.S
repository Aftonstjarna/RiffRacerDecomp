# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426800,0x42687f). Excludes surrounding INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ ALLOCATE_SLOT,0x92d4b4
.equ FAILURE_SLOT,0x92d164
.equ MOVE_SLOT,0x92d4a4
.equ DELETE_SLOT,0x92d4b0
.global original_u32_vector_reallocate
original_u32_vector_reallocate:
 push ebp
 mov.s ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 xor.s esi,esi
 push edi
 mov.s edi,ecx
 test ebx,ebx
 je transfer
 cmp ebx,0x3fffffff
 ja failure
 lea eax,[ebx*4+0]
 push eax
 call DWORD PTR [ALLOCATE_SLOT]
 mov.s esi,eax
 add esp,4
 test esi,esi
 jne transfer
failure:
 call DWORD PTR [FAILURE_SLOT]
transfer:
 mov ecx,DWORD PTR [edi]
 mov eax,DWORD PTR [edi+4]
 sub.s eax,ecx
 and eax,0xfffffffc
 push eax
 push ecx
 push esi
 call DWORD PTR [MOVE_SLOT]
 mov ecx,DWORD PTR [edi]
 add esp,12
 mov eax,DWORD PTR [edi+4]
 sub.s eax,ecx
 sar eax,2
 mov DWORD PTR [ebp+8],eax
 test ecx,ecx
 je publish
 push ecx
 call DWORD PTR [DELETE_SLOT]
 add esp,4
publish:
 lea eax,[esi+ebx*4]
 mov DWORD PTR [edi],esi
 mov DWORD PTR [edi+8],eax
 mov eax,DWORD PTR [ebp+8]
 lea eax,[esi+eax*4]
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
