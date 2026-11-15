.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, NOT high-level source recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4580a0, complete span through second ret at 0x4580f7.
.global original_reference_slot_vector_remove_tail
original_reference_slot_vector_remove_tail:
 push ebp
 {load} mov ebp,esp
 push ecx
 mov eax,DWORD PTR [ebp+8]
 push ebx
 push esi
 push edi
 mov edi,DWORD PTR [ecx+4]
 {load} mov ebx,edi
 shl eax,2
 {load} sub ebx,eax
 mov DWORD PTR [ebp-4],ecx
 {load} mov esi,ebx
 {load} cmp ebx,edi
 je empty_range
 {disp8} lea ecx,[ecx+0]
release_loop:
 mov edx,DWORD PTR [esi]
 test edx,edx
 je next_slot
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 {load} add ecx,edx
 dec DWORD PTR [ecx+4]
 jne next_slot
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
next_slot:
 add esi,4
 {load} cmp esi,edi
 jne release_loop
 mov eax,DWORD PTR [ebp-4]
 pop edi
 pop esi
 mov DWORD PTR [eax+4],ebx
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
empty_range:
 pop edi
 pop esi
 mov DWORD PTR [ecx+4],ebx
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
