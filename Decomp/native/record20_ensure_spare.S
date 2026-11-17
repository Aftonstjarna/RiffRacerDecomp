.intel_syntax noprefix
.code32
.text
.global original_record20_ensure_spare
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x52c7e0.
.equ record20_reallocate,0x52c750
original_record20_ensure_spare:
 push esi
 mov esi,DWORD PTR [ecx+4]
 mov eax,0x66666667
 push edi
 mov edi,DWORD PTR [ecx+8]
 mov.s edx,edi
 sub.s edx,esi
 imul edx
 sar edx,3
 mov.s eax,edx
 shr eax,0x1f
 add.s eax,edx
 cmp eax,1
 jae done
 sub esi,DWORD PTR [ecx]
 mov eax,0x66666667
 imul esi
 push ebx
 sar edx,3
 mov ebx,0x0ccccccc
 mov.s esi,edx
 mov.s eax,ebx
 shr esi,0x1f
 add.s esi,edx
 sub.s eax,esi
 cmp eax,1
 jae capacity
 push 0x999938
 call DWORD PTR ds:0x92d168
capacity:
 sub edi,DWORD PTR [ecx]
 mov eax,0x66666667
 imul edi
 inc esi
 sar edx,3
 mov.s eax,edx
 shr eax,0x1f
 add.s eax,edx
 mov.s edx,eax
 shr edx,1
 sub.s ebx,edx
 cmp.s ebx,eax
 pop ebx
 jae geometric
 xor.s eax,eax
 cmp.s eax,esi
 cmovb eax,esi
 push eax
 call record20_reallocate
 pop edi
 pop esi
 ret 4
geometric:
 add.s eax,edx
 cmp.s eax,esi
 cmovb eax,esi
 push eax
 call record20_reallocate
done:
 pop edi
 pop esi
 ret 4
.section .note.GNU-stack,"",@progbits
