# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x5a9680; complete function ends at 0x5a96c6.
.intel_syntax noprefix
.code32
.text
.global original_record6_capacity_growth
original_record6_capacity_growth:
 push ebp
 mov.s ebp,esp
 mov edx,DWORD PTR [ecx+8]
 mov eax,0x2aaaaaab
 sub edx,DWORD PTR [ecx]
 imul edx
 push esi
 mov.s esi,edx
 mov eax,0x2aaaaaaa
 shr esi,31
 add.s esi,edx
 mov.s ecx,esi
 shr ecx,1
 sub.s eax,ecx
 cmp.s eax,esi
 jae .growth
 xor.s esi,esi
 cmp esi,DWORD PTR [ebp+8]
 cmovb esi,DWORD PTR [ebp+8]
 mov.s eax,esi
 pop esi
 pop ebp
 ret 4
.growth:
 add.s esi,ecx
 cmp esi,DWORD PTR [ebp+8]
 cmovb esi,DWORD PTR [ebp+8]
 mov.s eax,esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
