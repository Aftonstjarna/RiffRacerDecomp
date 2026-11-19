.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41f7e0.
.global original_ui_sprite_set_handle_134
original_ui_sprite_set_handle_134:
 push ebp
 {load} mov ebp,esp
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov eax,0x9998bc
 push edi
 {load} mov edi,ecx
 mov ebx,DWORD PTR [esi]
 test ebx,ebx
 js .Lscan
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+ebx*2]
 mov ecx,DWORD PTR [eax+ecx*8]
 mov eax,DWORD PTR [0xbfcb38]
 add eax,4
 {load} add eax,ecx
.Lscan:
 lea edx,[eax+1]
.Lloop:
 mov cl,BYTE PTR [eax]
 inc eax
 test cl,cl
 jne .Lloop
 {load} sub eax,edx
 jne .Lassign
 mov esi,DWORD PTR [edi+0x134]
 test esi,esi
 js .Lreturn
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 dec DWORD PTR [eax+ecx*8+4]
 jne .Lclear
 mov esi,DWORD PTR [edi+0x134]
 call pool_get
 push esi
 lea ecx,[eax+4]
 call pool_remove
.Lclear:
 mov DWORD PTR [edi+0x134],0xffffffff
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.Lassign:
 push esi
 lea ecx,[edi+0x134]
 call handle_assign
.Lreturn:
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
.equ pool_get,0x417390
.equ pool_remove,0x41c090
.equ handle_assign,0x4183c0
.section .note.GNU-stack,"",@progbits
