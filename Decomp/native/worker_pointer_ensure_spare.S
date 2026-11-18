.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x429ce0,0x429d45), including both returns.
.global original_worker_pointer_ensure_spare
.equ vector_reallocate,0x426800
original_worker_pointer_ensure_spare:
 mov edx,DWORD PTR [ecx+8]
 mov.s eax,edx
 push esi
 mov esi,DWORD PTR [ecx+4]
 sub.s eax,esi
 sar eax,2
 cmp eax,1
 jae .done
 sub esi,DWORD PTR [ecx]
 push edi
 mov edi,0x3fffffff
 sar esi,2
 mov.s eax,edi
 sub.s eax,esi
 cmp eax,1
 jae .capacity
 push 0x999938
 call DWORD PTR [0x92d168]
.capacity:
 sub edx,DWORD PTR [ecx]
 inc esi
 sar edx,2
 mov.s eax,edx
 shr eax,1
 sub.s edi,eax
 cmp.s edi,edx
 pop edi
 jae .grow
 xor.s edx,edx
 cmp.s edx,esi
 cmovb edx,esi
 push edx
 call vector_reallocate
 pop esi
 ret 4
.grow:
 add.s edx,eax
 cmp.s edx,esi
 cmovb edx,esi
 push edx
 call vector_reallocate
.done:
 pop esi
 ret 4
.section .note.GNU-stack,"",@progbits
