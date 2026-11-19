.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x43f140.
.equ pool_get,0x417420
.equ pool_remove,0x41c090
.equ update_resource,0x453580
.global original_worker_resource_handle_set
original_worker_resource_handle_set:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi,ecx
 mov esi,DWORD PTR [edi+0x24]
 cmp esi,DWORD PTR [ebx]
 je .Lupdate
 test esi,esi
 js .Lassign
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 dec DWORD PTR [eax+ecx*8+4]
 jne .Lassign
 mov esi,DWORD PTR [edi+0x24]
 call pool_get
 push esi
 lea ecx,[eax+4]
 call pool_remove
.Lassign:
 mov esi,DWORD PTR [ebx]
 mov DWORD PTR [edi+0x24],esi
 test esi,esi
 js .Lupdate
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 inc DWORD PTR [eax+ecx*8+4]
.Lupdate:
 push edi
 call update_resource
 add esp,4
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
