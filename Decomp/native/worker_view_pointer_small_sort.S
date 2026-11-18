.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x42c920.
.global original_worker_view_pointer_small_sort
original_worker_view_pointer_small_sort:
 push ebp
 {load} mov ebp,esp
 sub esp,0xc
 {load} mov eax,edx
 {load} mov edx,ecx
 mov DWORD PTR [ebp-0xc],eax
 mov DWORD PTR [ebp-4],edx
 {load} cmp edx,eax
 je .Lend
 push esi
 lea esi,[edx+4]
 {load} cmp esi,eax
 je .Lpopesi
 mov eax,4
 {load} sub eax,edx
 push ebx
 mov DWORD PTR [ebp-8],eax
 push edi
.Lloop:
 mov edi,DWORD PTR [esi]
 {load} mov ebx,esi
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [edi+0x188]
 cmp ecx,DWORD PTR [eax+0x188]
 jge .Linsert
 mov eax,DWORD PTR [ebp-8]
 add eax,-4
 {load} add eax,esi
 sar eax,2
 lea ecx,[eax*4+0]
 {load} mov eax,esi
 push ecx
 {load} sub eax,ecx
 push edx
 add eax,4
 push eax
 call DWORD PTR [memmove_slot]
 mov edx,DWORD PTR [ebp-4]
 add esp,0xc
 mov DWORD PTR [edx],edi
 jmp .Lnext
.Linsert:
 mov edx,DWORD PTR [esi-4]
 lea eax,[esi-4]
 cmp ecx,DWORD PTR [edx+0x188]
 jge .Lplace
 {load} mov edi,edi
.Lshift:
 mov DWORD PTR [ebx],edx
 {load} mov ebx,eax
 mov edx,DWORD PTR [eax-4]
 sub eax,4
 mov ecx,DWORD PTR [edi+0x188]
 cmp ecx,DWORD PTR [edx+0x188]
 jl .Lshift
.Lplace:
 mov edx,DWORD PTR [ebp-4]
 mov DWORD PTR [ebx],edi
.Lnext:
 add esi,4
 cmp esi,DWORD PTR [ebp-0xc]
 jne .Lloop
 pop edi
 pop ebx
.Lpopesi:
 pop esi
.Lend:
 {load} mov esp,ebp
 pop ebp
 ret
.equ memmove_slot,0x92d4a4
.section .note.GNU-stack,"",@progbits
