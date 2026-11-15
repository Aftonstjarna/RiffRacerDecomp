# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0980,0x4f09d4); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_destroy
.equ EMPTY_HASH,0x99a424
.equ REALLOCATE,0x4f7d10
original_script_table_destroy:
 push esi
 mov.s esi,edx
 push edi
 mov.s edi,ecx
 mov edx,DWORD PTR [esi+0x10]
 cmp edx,EMPTY_HASH
 je .Larray
 mov cl,BYTE PTR [esi+7]
 mov eax,1
 shl eax,cl
 mov.s ecx,edi
 push 0
 lea eax,[eax+eax*4]
 shl eax,2
 push eax
 call REALLOCATE
 add esp,8
.Larray:
 mov eax,DWORD PTR [esi+0x1c]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+0xc]
 shl eax,3
 push 0
 push eax
 call REALLOCATE
 push 0
 push 0x20
 mov.s edx,esi
 mov.s ecx,edi
 call REALLOCATE
 add esp,0x10
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
