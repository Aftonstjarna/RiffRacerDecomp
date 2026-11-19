.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x455010.
.equ pool_get,0x417540
.equ pool_remove,0x41c090
.equ mark_dirty,0x453580
.global original_ui_visual_handle_update_1c
original_ui_visual_handle_update_1c:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi,ecx
 mov esi,DWORD PTR [edi+0x1c]
 cmp esi,DWORD PTR [ebx]
 je .Ldirty
 test esi,esi
 js .Lassign
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 dec DWORD PTR [eax+ecx*8+4]
 jne .Lassign
 mov esi,DWORD PTR [edi+0x1c]
 call pool_get
 push esi
 lea ecx,[eax+4]
 call pool_remove
.Lassign:
 mov esi,DWORD PTR [ebx]
 mov DWORD PTR [edi+0x1c],esi
 test esi,esi
 js .Ldirty
 call pool_get
 mov ecx,DWORD PTR [eax+4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 inc DWORD PTR [eax+ecx*8+4]
.Ldirty:
 or DWORD PTR [edi+0x170],0x1000
 push edi
 call mark_dirty
 add esp,4
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
