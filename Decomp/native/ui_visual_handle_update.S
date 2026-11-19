.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x454f90.
.equ pool_get,0x417540
.equ pool_remove,0x41c090
.equ visual_update,0x453580
.global original_ui_visual_handle_update
original_ui_visual_handle_update:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi,ecx
 mov esi,DWORD PTR [edi+0x18]
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
 mov esi,DWORD PTR [edi+0x18]
 call pool_get
 push esi
 lea ecx,[eax+4]
 call pool_remove
.Lassign:
 mov esi,DWORD PTR [ebx]
 mov DWORD PTR [edi+0x18],esi
 test esi,esi
 js .Lupdate
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 inc DWORD PTR [eax+ecx*8+4]
.Lupdate:
 or DWORD PTR [edi+0x170],0x800
 push edi
 call visual_update
 add esp,4
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
