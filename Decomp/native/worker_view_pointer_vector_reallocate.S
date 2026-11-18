.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x43ee60.
.global original_worker_view_pointer_vector_reallocate
original_worker_view_pointer_vector_reallocate:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8feed0
 mov eax,fs:0
 push eax
 sub esp,8
 push ebx
 push esi
 push edi
 mov eax,dword ptr [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-12]
 mov fs:0,eax
 mov [ebp-16],esp
 {load} mov edi,ecx
 mov ebx,[ebp+8]
 {load} xor esi,esi
 mov [ebp-20],esi
 test ebx,ebx
 je alloc_done
 cmp ebx,0x3fffffff
 ja alloc_fail
 lea eax,[ebx*4]
 push eax
 call dword ptr [0x92d4b4]
 {load} mov esi,eax
 add esp,4
 mov [ebp-20],esi
 test esi,esi
 jne alloc_done
alloc_fail:
 call dword ptr [0x92d164]
alloc_done:
 mov dword ptr [ebp-4],0
 push dword ptr [ebp+8]
 mov edx,[edi+4]
 mov ecx,[edi]
 sub esp,8
 push esi
 call copy_range
 mov dword ptr [ebp-4],-1
 add esp,16
 mov edx,[edi+4]
 {load} mov eax,edx
 mov ecx,[edi]
 {load} sub eax,ecx
 sar eax,2
 mov [ebp+8],eax
 test ecx,ecx
 je old_done
 push edx
 push ecx
 call destroy_range
 push dword ptr [edi]
 call dword ptr [0x92d4b0]
 add esp,4
old_done:
 lea eax,[esi+ebx*4]
 mov [edi],esi
 mov [edi+8],eax
 mov eax,[ebp+8]
 lea eax,[esi+eax*4]
 mov [edi+4],eax
 mov ecx,[ebp-12]
 mov dword ptr fs:0,ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
cleanup:
 push dword ptr [ebp-20]
 call dword ptr [0x92d4b0]
 add esp,4
 push 0
 push 0
 call unwind_resume
.equ copy_range,0x43f030
.equ destroy_range,0x43ee20
.equ unwind_resume,0x8f8d5a
.section .note.GNU-stack,"",@progbits
