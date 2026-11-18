.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42c8c0.
.global original_worker_view_heap_finish
original_worker_view_heap_finish:
 push ebp
 {load} mov ebp,esp
 push ecx
 push edi
 {load} mov edi,ecx
 {load} sub edx,edi
 {load} mov eax,edx
 and eax,0xfffffffc
 cmp eax,4
 jle .Lend
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 jmp .Lloop
 {disp32} lea ebx,[ebx+0]
.Lloop:
 mov eax,DWORD PTR [edi+edx-4]
 lea esi,[edx-4]
 mov DWORD PTR [ebp-4],eax
 {load} mov ecx,edi
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [edi+edx-4],eax
 lea eax,[ebp-4]
 push ebx
 push eax
 {load} mov eax,esi
 {load} xor edx,edx
 sar eax,2
 push eax
 call heap_sift
 {load} mov edx,esi
 add esp,12
 {load} mov eax,edx
 and eax,0xfffffffc
 cmp eax,4
 jg .Lloop
 pop esi
 pop ebx
.Lend:
 pop edi
 {load} mov esp,ebp
 pop ebp
 ret
.equ heap_sift,0x42c9d0
.section .note.GNU-stack,"",@progbits
