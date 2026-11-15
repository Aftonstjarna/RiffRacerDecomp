# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416a20,0x416a52); adjacent INT3 padding excluded.
# Register ABI: ECX first, EDX last, [ESP+4] destination; caller cleanup.
.intel_syntax noprefix
.code32
.text
.global original_record520_range_copy
original_record520_range_copy:
 push ebp
 mov.s ebp,esp
 push ebx
 mov.s ebx,edx
 mov.s eax,ecx
 mov edx,DWORD PTR [ebp+8]
 cmp.s eax,ebx
 je .Ldone
 push esi
 push edi
.Lcopy:
 mov.s esi,eax
 mov.s edi,edx
 add eax,0x208
 mov ecx,0x82
 add edx,0x208
 rep movsd
 cmp.s eax,ebx
 jne .Lcopy
 pop edi
 pop esi
.Ldone:
 mov.s eax,edx
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
