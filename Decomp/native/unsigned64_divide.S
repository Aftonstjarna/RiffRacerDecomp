# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc290,0x8fc2f8). Unsigned 64-bit division leaf.
.intel_syntax noprefix
.code32
.text
.global original_unsigned64_divide
original_unsigned64_divide:
 push ebx
 push esi
 mov eax,DWORD PTR [esp+0x18]
 {load} or eax,eax
 jne .Lwide
 mov ecx,DWORD PTR [esp+0x14]
 mov eax,DWORD PTR [esp+0x10]
 {load} xor edx,edx
 div ecx
 {load} mov ebx,eax
 mov eax,DWORD PTR [esp+0xc]
 div ecx
 {load} mov edx,ebx
 jmp .Ldone
.Lwide:
 {load} mov ecx,eax
 mov ebx,DWORD PTR [esp+0x14]
 mov edx,DWORD PTR [esp+0x10]
 mov eax,DWORD PTR [esp+0xc]
.Lnormalize:
 shr ecx,1
 rcr ebx,1
 shr edx,1
 rcr eax,1
 {load} or ecx,ecx
 jne .Lnormalize
 div ebx
 {load} mov esi,eax
 mul DWORD PTR [esp+0x18]
 {load} mov ecx,eax
 mov eax,DWORD PTR [esp+0x14]
 mul esi
 {load} add edx,ecx
 jb .Ldecrement
 cmp edx,DWORD PTR [esp+0x10]
 ja .Ldecrement
 jb .Lresult
 cmp eax,DWORD PTR [esp+0xc]
 jbe .Lresult
.Ldecrement:
 dec esi
.Lresult:
 {load} xor edx,edx
 {load} mov eax,esi
.Ldone:
 pop esi
 pop ebx
 ret 16
.section .note.GNU-stack,"",@progbits
