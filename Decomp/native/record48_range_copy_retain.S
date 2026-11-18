# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4b3eb0.
.intel_syntax noprefix
.code32
.text
.global original_record48_range_copy_retain
.equ copy_record,0x4b4310
original_record48_range_copy_retain:
 push ebp
 mov.s ebp,esp
 push ebx
 push edi
 mov.s ebx,edx
 mov.s edi,ecx
 cmp.s edi,ebx
 je .Lempty
 push esi
 mov esi,DWORD PTR [ebp+8]
.Lloop:
 test esi,esi
 je .Lnext
 push edi
 mov.s ecx,esi
 call copy_record
.Lnext:
 add edi,0x30
 add esi,0x30
 cmp.s edi,ebx
 jne .Lloop
 mov.s eax,esi
 pop esi
 pop edi
 pop ebx
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop edi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
