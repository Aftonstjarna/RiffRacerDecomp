.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x43efd0,0x43f026); INT3 padding excluded.
# ECX=source begin, EDX=source end, [ESP+4]=destination begin.
# Forward assignment releases old destination before retaining source.
.global original_reference_slot_assign_range
original_reference_slot_assign_range:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov.s ebx,edx
 mov.s esi,ecx
 cmp.s esi,ebx
 je empty_range
 push edi
 mov edi,DWORD PTR [ebp+8]
assign_slot:
 mov edx,DWORD PTR [edi]
 cmp edx,DWORD PTR [esi]
 je next_slot
 test edx,edx
 je store_source
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 add.s ecx,edx
 dec DWORD PTR [ecx+4]
 jne store_source
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
store_source:
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [edi],edx
 test edx,edx
 je next_slot
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 inc DWORD PTR [ecx+edx+4]
next_slot:
 add esi,4
 add edi,4
 cmp.s esi,ebx
 jne assign_slot
 mov.s eax,edi
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
empty_range:
 mov eax,DWORD PTR [ebp+8]
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
