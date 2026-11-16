.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4c40,0x4f4c83); complete leaf, both returns retained.
.global original_script_prototype_local_name
original_script_prototype_local_name:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 push edi
 mov edi,DWORD PTR [ecx+0x38]
 xor.s eax,eax
 test edi,edi
 jle .Lmissing
 mov ebx,DWORD PTR [ecx+0x18]
 xor.s ecx,ecx
 mov esi,DWORD PTR [ebp+8]
.Lscan:
 cmp DWORD PTR [ecx+ebx+4],esi
 jg .Lmissing
 cmp esi,DWORD PTR [ecx+ebx+8]
 jge .Lnext
 dec edx
 je .Lfound
.Lnext:
 inc eax
 add ecx,0xc
 cmp.s eax,edi
 jl .Lscan
.Lmissing:
 pop edi
 pop esi
 xor.s eax,eax
 pop ebx
 pop ebp
 ret
.Lfound:
 lea eax,[eax+eax*2]
 mov eax,DWORD PTR [ebx+eax*4]
 pop edi
 pop esi
 add eax,0x10
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
