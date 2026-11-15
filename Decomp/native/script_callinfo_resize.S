# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4f50,0x4f4fca); excludes INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_script_callinfo_resize
.equ REALLOCATE,0x4f7d10
.equ TOO_LARGE,0x4f7cf0
original_script_callinfo_resize:
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 push esi
 push edi
 mov.s edi,edx
 mov.s esi,ecx
 mov ecx,DWORD PTR [esi+0x28]
 lea eax,[edi+1]
 mov DWORD PTR [ebp-4],ecx
 cmp eax,0x0aaaaaaa
 ja .Ltoo_large
 lea eax,[edi+edi*2]
 mov.s edx,ecx
 shl eax,3
 mov.s ecx,esi
 push eax
 mov eax,DWORD PTR [esi+0x30]
 lea eax,[eax+eax*2]
 shl eax,3
 push eax
 call REALLOCATE
 add esp,8
 jmp .Lrelocate
.Ltoo_large:
 mov.s ecx,esi
 call TOO_LARGE
.Lrelocate:
 mov ecx,DWORD PTR [esi+0x14]
 mov.s ebx,eax
 sub ecx,DWORD PTR [ebp-4]
 mov eax,0x2aaaaaab
 imul ecx
 mov DWORD PTR [esi+0x30],edi
 sar edx,2
 mov.s eax,edx
 mov DWORD PTR [esi+0x28],ebx
 shr eax,31
 add.s eax,edx
 dec edi
 lea eax,[eax+eax*2]
 lea eax,[ebx+eax*8]
 mov DWORD PTR [esi+0x14],eax
 lea eax,[edi+edi*2]
 lea eax,[ebx+eax*8]
 pop edi
 mov DWORD PTR [esi+0x24],eax
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
