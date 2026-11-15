# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x43e630,0x43e698): two RET 4 exits and terminal _Xbad_alloc call.
.intel_syntax noprefix
.code32
.text
.global original_u32_vector_initialize_capacity
.equ LENGTH_MESSAGE,0x999938
.equ X_LENGTH_ERROR,0x92d168
.equ OPERATOR_NEW,0x92d4b4
.equ X_BAD_ALLOC,0x92d164
original_u32_vector_initialize_capacity:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push esi
 mov.s esi,ecx
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
 test eax,eax
 jne nonzero
 xor.s al,al
 pop esi
 pop ebp
 ret 4
nonzero:
 cmp eax,0x3fffffff
 jbe allocate
 push LENGTH_MESSAGE
 call DWORD PTR [X_LENGTH_ERROR]
allocate:
 push edi
 lea edi,[eax*4+0]
 push edi
 call DWORD PTR [OPERATOR_NEW]
 add esp,4
 test eax,eax
 je allocation_failed
 mov DWORD PTR [esi],eax
 mov DWORD PTR [esi+4],eax
 add.s eax,edi
 mov DWORD PTR [esi+8],eax
 mov al,1
 pop edi
 pop esi
 pop ebp
 ret 4
allocation_failed:
 call DWORD PTR [X_BAD_ALLOC]
.section .note.GNU-stack,"",@progbits
