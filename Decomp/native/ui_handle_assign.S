.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x4183c0.
.equ pool_get, 0x417390
.equ pool_remove, 0x41c090
.global original_ui_handle_assign
original_ui_handle_assign:
 push ebp
 {load} mov ebp, esp
 push ebx
 mov ebx, DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi, ecx
 mov esi, DWORD PTR [edi]
 cmp esi, DWORD PTR [ebx]
 je done
 test esi, esi
 js assign
 call pool_get
 mov ecx, DWORD PTR [eax+4]
 mov eax, DWORD PTR [eax+0x28]
 movsx ecx, WORD PTR [ecx+esi*2]
 dec DWORD PTR [eax+ecx*8+4]
 jne assign
 mov esi, DWORD PTR [edi]
 call pool_get
 push esi
 lea ecx, [eax+4]
 call pool_remove
assign:
 mov esi, DWORD PTR [ebx]
 mov DWORD PTR [edi], esi
 test esi, esi
 js done
 call pool_get
 mov ecx, DWORD PTR [eax+4]
 mov eax, DWORD PTR [eax+0x28]
 movsx ecx, WORD PTR [ecx+esi*2]
 inc DWORD PTR [eax+ecx*8+4]
done:
 {load} mov eax, edi
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 4
