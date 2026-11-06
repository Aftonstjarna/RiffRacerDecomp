# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc300,0x8fc375); unsigned 64-bit remainder leaf.
.intel_syntax noprefix
.code32
.text
.global original_unsigned64_remainder
original_unsigned64_remainder:
 push ebx
 mov eax,DWORD PTR [esp+0x14]
 {load} or eax,eax
 jne .Lwide
 mov ecx,DWORD PTR [esp+0x10]
 mov eax,DWORD PTR [esp+0xc]
 {load} xor edx,edx
 div ecx
 mov eax,DWORD PTR [esp+8]
 div ecx
 {load} mov eax,edx
 {load} xor edx,edx
 jmp .Ldone
.Lwide:
 {load} mov ecx,eax
 mov ebx,DWORD PTR [esp+0x10]
 mov edx,DWORD PTR [esp+0xc]
 mov eax,DWORD PTR [esp+8]
.Lnormalize:
 shr ecx,1
 rcr ebx,1
 shr edx,1
 rcr eax,1
 {load} or ecx,ecx
 jne .Lnormalize
 div ebx
 {load} mov ecx,eax
 mul DWORD PTR [esp+0x14]
 xchg ecx,eax
 mul DWORD PTR [esp+0x10]
 {load} add edx,ecx
 jb .Lcorrect
 cmp edx,DWORD PTR [esp+0xc]
 ja .Lcorrect
 jb .Lsubtract
 cmp eax,DWORD PTR [esp+8]
 jbe .Lsubtract
.Lcorrect:
 sub eax,DWORD PTR [esp+0x10]
 sbb edx,DWORD PTR [esp+0x14]
.Lsubtract:
 sub eax,DWORD PTR [esp+8]
 sbb edx,DWORD PTR [esp+0xc]
 neg edx
 neg eax
 sbb edx,0
.Ldone:
 pop ebx
 ret 16
.section .note.GNU-stack,"",@progbits
