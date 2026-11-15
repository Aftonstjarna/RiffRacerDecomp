# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d840,0x47d8a6); INT3 padding excluded.
# ECX=source transform, stack argument=destination; callee pops 4 bytes.
.intel_syntax noprefix
.code32
.text
.global original_transform64_serialize_copy
original_transform64_serialize_copy:
 push ebp
 {load} mov ebp,esp
 push ecx
 push ebx
 push esi
 push edi
 mov edi,DWORD PTR [ebp+8]
 lea esi,[ecx+12]
 {load} mov eax,ecx
 mov ebx,3
 {load} sub eax,edi
 lea edx,[edi+4]
 {load} mov edi,eax
 jmp row
 {disp8} lea ecx,[ecx+0]
row:
 mov eax,DWORD PTR [esi-12]
 lea edx,[edx+16]
 mov DWORD PTR [edx-20],eax
 lea esi,[esi+16]
 mov eax,DWORD PTR [edi+edx-16]
 mov DWORD PTR [edx-16],eax
 mov eax,DWORD PTR [esi-20]
 mov DWORD PTR [edx-12],eax
 mov eax,DWORD PTR [esi-16]
 mov DWORD PTR [edx-8],eax
 dec ebx
 jne row
 mov edi,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [ecx+48]
 mov DWORD PTR [edi+48],eax
 mov eax,DWORD PTR [ecx+52]
 mov DWORD PTR [edi+52],eax
 mov eax,DWORD PTR [ecx+56]
 mov DWORD PTR [edi+56],eax
 mov eax,DWORD PTR [ecx+60]
 mov DWORD PTR [edi+60],eax
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
