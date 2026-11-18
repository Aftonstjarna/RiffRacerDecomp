.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42c9d0.
.global original_worker_view_heap_sift
original_worker_view_heap_sift:
 push ebp
 {load} mov ebp,esp
 push ecx
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi,edx
 {load} mov esi,ecx
 {load} mov ecx,edi
 mov DWORD PTR [ebp-4],ecx
 lea eax,[edi*2+2]
 {load} cmp eax,ebx
 jge .Lsingle
 {load} mov edi,edi
.Lloop:
 mov ecx,DWORD PTR [esi+eax*4]
 mov edx,DWORD PTR [esi+eax*4-4]
 mov ecx,DWORD PTR [ecx+0x188]
 cmp ecx,DWORD PTR [edx+0x188]
 jge .Lchosen
 dec eax
.Lchosen:
 mov ecx,DWORD PTR [esi+eax*4]
 mov DWORD PTR [esi+edi*4],ecx
 {load} mov edi,eax
 lea eax,[eax*2+2]
 {load} cmp eax,ebx
 jl .Lloop
 mov ecx,DWORD PTR [ebp-4]
.Lsingle:
 jne .Lpush
 mov eax,DWORD PTR [esi+ebx*4-4]
 mov DWORD PTR [esi+edi*4],eax
 lea edi,[ebx-1]
.Lpush:
 push DWORD PTR [ebp+0x10]
 {load} mov edx,edi
 push DWORD PTR [ebp+0xc]
 push ecx
 {load} mov ecx,esi
 call heap_push
 add esp,12
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.equ heap_push,0x42ca50
.section .note.GNU-stack,"",@progbits
