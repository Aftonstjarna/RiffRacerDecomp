# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4ef0,0x4f4f4f); INT3 separator excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_stack_resize
.equ script_reallocate,0x4f7d10
.equ script_allocation_too_large,0x4f7cf0
.equ script_stack_relocate_pointers,0x4f4e60
original_script_stack_resize:
# ECX state; EDX requested usable slots. Preserve old base across allocation.
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 mov.s ebx,edx
 push esi
 push edi
 mov.s esi,ecx
 lea edi,[ebx+6]
 lea eax,[edi+1]
 mov ecx,DWORD PTR [esi+0x20]
 mov DWORD PTR [ebp-4],ecx
 cmp eax,0x1fffffff
 ja too_large
 lea eax,[edi*8+0]
 mov.s edx,ecx
 push eax
 mov eax,DWORD PTR [esi+0x2c]
 mov.s ecx,esi
 shl eax,3
 push eax
 call script_reallocate
 add esp,8
 jmp update_stack
too_large:
 mov.s ecx,esi
 call script_allocation_too_large
update_stack:
 mov edx,DWORD PTR [ebp-4]
 mov.s ecx,esi
 mov DWORD PTR [esi+0x20],eax
 lea eax,[eax+ebx*8]
 mov DWORD PTR [esi+0x2c],edi
 mov DWORD PTR [esi+0x1c],eax
 call script_stack_relocate_pointers
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
