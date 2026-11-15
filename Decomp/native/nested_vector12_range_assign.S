# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x43e7d0,0x43e7fa); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_nested_vector12_range_assign
.equ ASSIGN_U32_VECTOR,0x43e240
original_nested_vector12_range_assign:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov.s ebx,edx
 mov.s esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 cmp.s esi,ebx
 je done
next_record:
 push esi
 mov.s ecx,edi
 call ASSIGN_U32_VECTOR
 add esi,0xc
 add edi,0xc
 cmp.s esi,ebx
 jne next_record
done:
 mov.s eax,edi
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
