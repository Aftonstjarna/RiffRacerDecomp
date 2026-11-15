# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x53c7c0,0x53c80b). Four conditional branches; two RET 12 exits.
# Three stack slots: unused, index, pointer-range descriptor. AL Boolean only.
.intel_syntax noprefix
.code32
.text
.global original_pointer_range_has_state_six_or_seven
original_pointer_range_has_state_six_or_seven:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0x10]
 xor.s ecx,ecx
 push esi
 push edi
 mov esi,DWORD PTR [eax+4]
 mov edx,DWORD PTR [eax]
 sub.s esi,edx
 sar esi,2
 test esi,esi
 jle no_match
 imul edi,DWORD PTR [ebp+12],0x64
 {disp8} lea esp,[esp+0]
scan:
 mov eax,DWORD PTR [edx]
 mov eax,DWORD PTR [edi+eax+0xd4]
 cmp eax,6
 je matched
 cmp eax,7
 je matched
 inc ecx
 add edx,4
 cmp.s ecx,esi
 jl scan
no_match:
 pop edi
 xor.s al,al
 pop esi
 pop ebp
 ret 12
matched:
 pop edi
 mov al,1
 pop esi
 pop ebp
 ret 12
.section .note.GNU-stack,"",@progbits
