.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f0c50, complete 97-byte function through 0x4f0cb0.
.equ lookup,0x4f0bb0
.equ new_key,0x4f09e0
.equ runtime_error,0x486ab0
.global original_script_table_ensure_value_slot
original_script_table_ensure_value_slot:
 push ebp
 {load} mov ebp,esp
 push ebx
 push esi
 {load} mov ebx,edx
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 {load} mov ecx,ebx
 {load} mov edx,edi
 call lookup
 mov BYTE PTR [ebx+6],0
 cmp eax,0x99a41c
 jne done
 mov eax,DWORD PTR [edi+4]
 test eax,eax
 jne nonnil
 push 0x9fd750
 jmp error
nonnil:
 cmp eax,3
 jne insert
 movss xmm0,DWORD PTR [edi]
 ucomiss xmm0,xmm0
 lahf
 test ah,0x44
 jnp insert
 push 0x9fd714
error:
 push esi
 call runtime_error
 add esp,8
insert:
 push edi
 {load} mov edx,ebx
 {load} mov ecx,esi
 call new_key
 add esp,4
done:
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
