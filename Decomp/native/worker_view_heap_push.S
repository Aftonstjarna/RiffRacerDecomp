.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42ca50.
.global original_worker_view_heap_push
original_worker_view_heap_push:
 push ebp
 {load} mov ebp,esp
 push ebx
 {load} mov ebx,edx
 push esi
 {load} mov esi,ecx
 lea eax,[ebx-1]
 cdq
 {load} sub eax,edx
 sar eax,1
 cmp DWORD PTR [ebp+8],ebx
 jge .Ldirect
 push edi
.Lloop:
 mov ecx,DWORD PTR [ebp+12]
 mov edi,DWORD PTR [esi+eax*4]
 mov edx,DWORD PTR [ecx]
 mov ecx,DWORD PTR [edi+0x188]
 cmp ecx,DWORD PTR [edx+0x188]
 jge .Lstore
 mov DWORD PTR [esi+ebx*4],edi
 {load} mov ebx,eax
 dec eax
 cdq
 {load} sub eax,edx
 sar eax,1
 cmp DWORD PTR [ebp+8],ebx
 jl .Lloop
.Lstore:
 mov eax,DWORD PTR [ebp+12]
 pop edi
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [esi+ebx*4],eax
 pop esi
 pop ebx
 pop ebp
 ret
.Ldirect:
 mov eax,DWORD PTR [ebp+12]
 mov eax,DWORD PTR [eax]
 mov DWORD PTR [esi+ebx*4],eax
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
