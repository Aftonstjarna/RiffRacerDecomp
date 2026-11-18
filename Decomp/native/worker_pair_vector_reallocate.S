.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41c5e0.
.global original_worker_pair_vector_reallocate
original_worker_pair_vector_reallocate:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fd980
 mov eax,fs:0
 push eax
 sub esp,0xc
 push ebx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov DWORD PTR [ebp-0x10],esp
 {load} mov ebx,ecx
 mov eax,DWORD PTR [ebp+8]
 {load} xor edi,edi
 mov DWORD PTR [ebp-0x14],edi
 test eax,eax
 je .Lallocated
 cmp eax,0x1fffffff
 ja .Lfailure
 shl eax,3
 push eax
 call DWORD PTR [0x92d4b4]
 {load} mov edi,eax
 add esp,4
 mov DWORD PTR [ebp-0x14],edi
 test edi,edi
 jne .Lallocated
.Lfailure:
 call DWORD PTR [0x92d164]
.Lallocated:
 mov DWORD PTR [ebp-4],0
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 mov ecx,DWORD PTR [ebx]
 sub esp,8
 push edi
 call copy_pairs
 mov eax,DWORD PTR [ebx+4]
 add esp,0x10
 mov esi,DWORD PTR [ebx]
 {load} mov ecx,eax
 {load} sub ecx,esi
 mov DWORD PTR [ebp-0x14],eax
 sar ecx,3
 mov DWORD PTR [ebp-0x18],ecx
 test esi,esi
 je .Lstore
 {load} cmp esi,eax
 je .Ldelete
.Lloop:
 {load} mov ecx,esi
 call destroy_pair
 add esi,8
 cmp esi,DWORD PTR [ebp-0x14]
 jne .Lloop
.Ldelete:
 push DWORD PTR [ebx]
 call DWORD PTR [0x92d4b0]
 mov ecx,DWORD PTR [ebp-0x18]
 add esp,4
.Lstore:
 mov eax,DWORD PTR [ebp+8]
 mov DWORD PTR [ebx],edi
 lea eax,[edi+eax*8]
 mov DWORD PTR [ebx+8],eax
 lea eax,[edi+ecx*8]
 mov DWORD PTR [ebx+4],eax
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
.Lcleanup:
 push DWORD PTR [ebp-0x14]
 call DWORD PTR [0x92d4b0]
 add esp,4
 push 0
 push 0
 call unwind_resume
.equ copy_pairs,0x41c7c0
.equ destroy_pair,0x426be0
.equ unwind_resume,0x8f8d5a
.section .note.GNU-stack,"",@progbits
