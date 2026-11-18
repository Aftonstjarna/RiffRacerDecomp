.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41c7c0.
.global original_worker_pair_copy_construct_range
original_worker_pair_copy_construct_range:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fd9e1
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
 {load} mov ebx,edx
 {load} mov edi,ecx
 mov esi,DWORD PTR [ebp+8]
 mov DWORD PTR [ebp-0x14],esi
 mov DWORD PTR [ebp-4],0
 {disp8} lea esp,[esp+0]
.Lloop:
 {load} cmp edi,ebx
 je .Ldone
 mov DWORD PTR [ebp-0x18],esi
 mov BYTE PTR [ebp-4],1
 test esi,esi
 je .Ladvance
 mov eax,DWORD PTR [0xbfcb38]
 {load} mov ecx,esi
 add eax,4
 add eax,DWORD PTR [edi]
 push eax
 call construct_handle
 mov eax,DWORD PTR [edi+4]
 mov DWORD PTR [esi+4],eax
.Ladvance:
 add esi,8
 mov BYTE PTR [ebp-4],0
 mov DWORD PTR [ebp+8],esi
 add edi,8
 jmp .Lloop
.Lcleanup:
 mov esi,DWORD PTR [ebp-0x14]
 mov edi,DWORD PTR [ebp+8]
 {load} cmp esi,edi
 je .Lresume
.Ldestroy:
 {load} mov ecx,esi
 call destroy_pair
 add esi,8
 {load} cmp esi,edi
 jne .Ldestroy
.Lresume:
 push 0
 push 0
 call unwind_resume
.Ldone:
 {load} mov eax,esi
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.equ construct_handle,0x426a30
.equ destroy_pair,0x426be0
.equ unwind_resume,0x8f8d5a
.section .note.GNU-stack,"",@progbits
