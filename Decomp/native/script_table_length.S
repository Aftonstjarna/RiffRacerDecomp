.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x4f0e90..0x4f0ee2; both returns and final tail jump included.
.global original_script_table_length
.equ EMPTY_HASH,0x99a424
.equ HASH_BOUNDARY,0x4f0d80
original_script_table_length:
 mov edx,DWORD PTR [ecx+0x1c]
 push esi
 test edx,edx
 je .Ltail
 mov esi,DWORD PTR [ecx+0xc]
 cmp DWORD PTR [esi+edx*8-4],0
 jne .Ltail
 xor.s ecx,ecx
 cmp edx,1
 jbe .Larray_return
 {disp32} lea esp,[esp+0]
.Lbisect:
 lea eax,[ecx+edx]
 shr eax,1
 cmp DWORD PTR [esi+eax*8-4],0
 jne .Loccupied
 mov.s edx,eax
 jmp .Lcontinue
.Loccupied:
 mov.s ecx,eax
.Lcontinue:
 mov.s eax,edx
 sub.s eax,ecx
 cmp eax,1
 ja .Lbisect
.Larray_return:
 mov.s eax,ecx
 pop esi
 ret
.Ltail:
 cmp DWORD PTR [ecx+0x10],EMPTY_HASH
 jne .Lhash
 mov.s eax,edx
 pop esi
 ret
.Lhash:
 pop esi
 jmp HASH_BOUNDARY
.section .note.GNU-stack,"",@progbits
