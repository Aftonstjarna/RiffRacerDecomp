# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41c560,0x41c5da); excludes INT3 padding before next function.
.intel_syntax noprefix
.code32
.text
.global original_u16_vector_reallocate
.equ iat_operator_new,0x92d4b4
.equ iat_bad_alloc,0x92d164
.equ iat_memmove,0x92d4a4
.equ iat_operator_delete,0x92d4b0
original_u16_vector_reallocate:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 {load} xor esi,esi
 push edi
 {load} mov edi,ecx
 test ebx,ebx
 je .Lcopy
 cmp ebx,0x7fffffff
 ja .Lfailure
 lea eax,[ebx+ebx]
 push eax
 call DWORD PTR [iat_operator_new]
 {load} mov esi,eax
 add esp,4
 test esi,esi
 jne .Lcopy
.Lfailure:
 call DWORD PTR [iat_bad_alloc]
.Lcopy:
 mov ecx,DWORD PTR [edi]
 mov eax,DWORD PTR [edi+4]
 {load} sub eax,ecx
 and eax,0xfffffffe
 push eax
 push ecx
 push esi
 call DWORD PTR [iat_memmove]
 mov ecx,DWORD PTR [edi]
 add esp,12
 mov eax,DWORD PTR [edi+4]
 {load} sub eax,ecx
 sar eax,1
 mov DWORD PTR [ebp+8],eax
 test ecx,ecx
 je .Lcommit
 push ecx
 call DWORD PTR [iat_operator_delete]
 add esp,4
.Lcommit:
 lea eax,[esi+ebx*2]
 mov DWORD PTR [edi],esi
 mov DWORD PTR [edi+8],eax
 mov eax,DWORD PTR [ebp+8]
 lea eax,[esi+eax*2]
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
