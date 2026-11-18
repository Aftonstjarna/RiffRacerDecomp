.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x42c310.
.global original_worker_view_pointer_sort
original_worker_view_pointer_sort:
 push ebp
 {load} mov ebp,esp
 and esp,0xfffffff8
 sub esp,0xc
 push ebx
 push esi
 push edi
 {load} mov edi,edx
 {load} mov ebx,ecx
 {load} mov esi,edi
 {load} sub esi,ebx
 sar esi,2
 cmp esi,0x20
 jle .Lsmall
 {disp8} lea esp,[esp+0]
.Lloop:
 cmp DWORD PTR [ebp+8],0
 jle .Lfallback
 push DWORD PTR [ebp+0xc]
 {load} mov edx,ebx
 lea ecx,[esp+0x14]
 push edi
 call partition
 mov eax,DWORD PTR [ebp+8]
 add esp,8
 cdq
 {load} mov ecx,edi
 sub ecx,DWORD PTR [esp+0x14]
 {load} sub eax,edx
 {load} mov esi,eax
 and ecx,0xfffffffc
 push DWORD PTR [ebp+0xc]
 sar esi,1
 {load} mov eax,esi
 cdq
 {load} sub eax,edx
 mov edx,DWORD PTR [esp+0x14]
 sar eax,1
 {load} add esi,eax
 {load} mov eax,edx
 {load} sub eax,ebx
 mov DWORD PTR [ebp+8],esi
 and eax,0xfffffffc
 push esi
 {load} cmp eax,ecx
 jge .Lright
 {load} mov ecx,ebx
 call original_worker_view_pointer_sort
 mov ecx,DWORD PTR [esp+0x1c]
 {load} mov ebx,ecx
 jmp .Lcontinue
.Lright:
 mov ecx,DWORD PTR [esp+0x1c]
 {load} mov edx,edi
 call original_worker_view_pointer_sort
 mov edi,DWORD PTR [esp+0x18]
.Lcontinue:
 {load} mov esi,edi
 add esp,8
 {load} sub esi,ebx
 sar esi,2
 cmp esi,0x20
 jg .Lloop
.Lsmall:
 cmp esi,1
 jle .Lreturn
 push ecx
 push DWORD PTR [ebp+0xc]
 {load} mov edx,edi
 {load} mov ecx,ebx
 call small_sort
 add esp,8
.Lreturn:
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.Lfallback:
 cmp esi,0x20
 jle .Lsmall
 {load} mov eax,edi
 {load} sub eax,ebx
 and eax,0xfffffffc
 cmp eax,4
 jle .Lfinish
 sub esp,8
 {load} mov edx,edi
 {load} mov ecx,ebx
 push DWORD PTR [ebp+0xc]
 call heap_prepare
 add esp,0xc
.Lfinish:
 push DWORD PTR [ebp+0xc]
 {load} mov edx,edi
 {load} mov ecx,ebx
 call heap_finish
 add esp,4
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.equ partition,0x42c400
.equ small_sort,0x42c920
.equ heap_prepare,0x42c7d0
.equ heap_finish,0x42c8c0
.section .note.GNU-stack,"",@progbits
