# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x422c50,0x422c7b); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_narrow_tree_key_less
.equ narrow_compare_range,0x422be0
original_narrow_tree_key_less:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0xc]
 cmp DWORD PTR [eax+0x14],0x10
 mov ecx,DWORD PTR [eax+0x10]
 jb .inline_right
 mov eax,DWORD PTR [eax]
.inline_right:
 push ecx
 mov ecx,DWORD PTR [ebp+8]
 push eax
 push DWORD PTR [ecx+0x10]
 push 0
 call narrow_compare_range
 xor.s ecx,ecx
 test eax,eax
 sets al
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
