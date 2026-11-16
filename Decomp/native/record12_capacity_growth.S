.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5a95f0,0x5a9638), including both ret 4 paths.
# ECX: vector {begin,end,capacity_end}; stack: minimum count. EAX: capacity.
.global original_record12_capacity_growth
original_record12_capacity_growth:
push ebp
mov.s ebp,esp
mov edx,DWORD PTR [ecx+8]
mov eax,0x2aaaaaab
sub edx,DWORD PTR [ecx]
imul edx
push esi
sar edx,1
mov eax,0x15555555
mov.s esi,edx
shr esi,0x1f
add.s esi,edx
mov.s ecx,esi
shr ecx,1
sub.s eax,ecx
cmp.s eax,esi
jae .Lgrow
xor.s esi,esi
cmp esi,DWORD PTR [ebp+8]
cmovb esi,DWORD PTR [ebp+8]
mov.s eax,esi
pop esi
pop ebp
ret 4
.Lgrow:
add.s esi,ecx
cmp esi,DWORD PTR [ebp+8]
cmovb esi,DWORD PTR [ebp+8]
mov.s eax,esi
pop esi
pop ebp
ret 4
.section .note.GNU-stack,"",@progbits
