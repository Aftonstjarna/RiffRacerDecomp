# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4f4bb0,0x4f4c3c), excludes following INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_script_prototype_dispose
.equ REALLOCATE,0x4f7d10
original_script_prototype_dispose:
 push esi
 mov.s esi,edx
 push edi
 push 0
 mov.s edi,ecx
 mov eax,DWORD PTR [esi+0x2c]
 mov edx,DWORD PTR [esi+0xc]
 shl eax,2
 push eax
 call REALLOCATE
 mov eax,DWORD PTR [esi+0x34]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+0x10]
 shl eax,2
 push 0
 push eax
 call REALLOCATE
 mov eax,DWORD PTR [esi+0x28]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+8]
 shl eax,3
 push 0
 push eax
 call REALLOCATE
 mov eax,DWORD PTR [esi+0x30]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+0x14]
 shl eax,2
 push 0
 push eax
 call REALLOCATE
 mov eax,DWORD PTR [esi+0x38]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+0x18]
 push 0
 lea eax,[eax+eax*2]
 shl eax,2
 push eax
 call REALLOCATE
 mov eax,DWORD PTR [esi+0x24]
 mov.s ecx,edi
 mov edx,DWORD PTR [esi+0x1c]
 shl eax,2
 push 0
 push eax
 call REALLOCATE
 push 0
 push 0x4c
 mov.s edx,esi
 mov.s ecx,edi
 call REALLOCATE
 add esp,0x38
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
