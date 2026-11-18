# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5c2140.
.intel_syntax noprefix
.code32
.text
.global original_worker_narrow_range_replace
.equ erase_range,0x416660
.equ replace_range,0x440ea0
original_worker_narrow_range_replace:
 push ebp
 mov.s ebp,esp
 mov edx,[ebp+0x14]
 push esi
 push edi
 mov edi,[ebp+0x10]
 mov.s esi,ecx
 cmp.s edi,edx
 jne .Lreplace
 cmp DWORD PTR [esi+0x14],0x10
 jb .Linline1
 mov edx,[esi]
 jmp .Lbase1
.Linline1:
 mov.s edx,esi
.Lbase1:
 mov ecx,[ebp+0xc]
 mov eax,[ebp+8]
 test ecx,ecx
 jne .Ldiff1
 xor.s ecx,ecx
 jmp .Lcount1
.Ldiff1:
 sub.s ecx,eax
.Lcount1:
 test eax,eax
 jne .Loffset1
 push ecx
 push eax
 mov.s ecx,esi
 call erase_range
 pop edi
 mov.s eax,esi
 pop esi
 pop ebp
 ret 0x10
.Loffset1:
 push ecx
 sub.s eax,edx
 mov.s ecx,esi
 push eax
 call erase_range
 pop edi
 mov.s eax,esi
 pop esi
 pop ebp
 ret 0x10
.Lreplace:
 cmp DWORD PTR [esi+0x14],0x10
 push ebx
 jb .Linline2
 mov ebx,[esi]
 jmp .Lbase2
.Linline2:
 mov.s ebx,esi
.Lbase2:
 mov ecx,[ebp+0xc]
 mov eax,[ebp+8]
 test ecx,ecx
 jne .Ldiff2
 xor.s ecx,ecx
 jmp .Lcount2
.Ldiff2:
 sub.s ecx,eax
.Lcount2:
 test eax,eax
 je .Loffset2
 sub.s eax,ebx
.Loffset2:
 sub.s edx,edi
 push edx
 push edi
 push ecx
 push eax
 mov.s ecx,esi
 call replace_range
 pop ebx
 pop edi
 mov.s eax,esi
 pop esi
 pop ebp
 ret 0x10
