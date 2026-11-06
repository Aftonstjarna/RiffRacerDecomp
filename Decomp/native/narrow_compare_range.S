# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x422be0,0x422c44); both returns included, INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_narrow_compare_range
.equ byte_range_compare,0x4225c0
.equ range_error_text,0x99995c
.equ throw_out_of_range_iat,0x92d16c
original_narrow_compare_range:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ecx+0x10]
 mov edx,DWORD PTR [ebp+8]
 cmp.s eax,edx
 jae .valid
 push range_error_text
 call DWORD PTR [throw_out_of_range_iat]
.valid:
 push esi
 mov esi,DWORD PTR [ebp+0xc]
 sub.s eax,edx
 cmp.s eax,esi
 push edi
 cmovb esi,eax
 cmp DWORD PTR [ecx+0x14],0x10
 jb .inline
 mov ecx,DWORD PTR [ecx]
.inline:
 mov edi,DWORD PTR [ebp+0x14]
 cmp.s esi,edi
 mov.s eax,edi
 cmovb eax,esi
 push eax
 push DWORD PTR [ebp+0x10]
 lea eax,[ecx+edx]
 push eax
 call byte_range_compare
 add esp,0xc
 test eax,eax
 jne .done
 cmp.s esi,edi
 jae .not_shorter
 pop edi
 or eax,-1
 pop esi
 pop ebp
 ret 0x10
.not_shorter:
 xor.s eax,eax
 cmp.s esi,edi
 setne al
.done:
 pop edi
 pop esi
 pop ebp
 ret 0x10
.section .note.GNU-stack,"",@progbits
