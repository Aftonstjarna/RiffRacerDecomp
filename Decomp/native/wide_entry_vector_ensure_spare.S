.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x561b80.
.equ growth_policy,0x49c050
.equ reallocate,0x561c80
.global original_wide_entry_vector_ensure_spare
original_wide_entry_vector_ensure_spare:
 push ebx
 push esi
 push edi
 {load} mov edi,ecx
 mov eax,0x92492493
 mov esi,[edi+8]
 mov ebx,[edi+4]
 {load} sub esi,ebx
 imul esi
 {load} add edx,esi
 sar edx,4
 {load} mov ecx,edx
 shr ecx,31
 {load} add ecx,edx
 cmp ecx,1
 jae done
 sub ebx,[edi]
 mov eax,0x92492493
 imul ebx
 mov eax,0x09249249
 {load} add edx,ebx
 sar edx,4
 {load} mov ecx,edx
 shr ecx,31
 {load} add ecx,edx
 {load} sub eax,ecx
 cmp eax,1
 jae grow
 push 0x999938
 call DWORD PTR [0x92d168]
grow:
 lea eax,[ecx+1]
 {load} mov ecx,edi
 push eax
 call growth_policy
 push eax
 {load} mov ecx,edi
 call reallocate
done:
 pop edi
 pop esi
 pop ebx
 ret 4
.section .note.GNU-stack,"",@progbits
