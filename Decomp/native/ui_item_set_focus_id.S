.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x448180.
.global original_ui_item_set_focus_id
original_ui_item_set_focus_id:
 push ebp
 {load} mov ebp, esp
 push edi
 {load} mov edi, ecx
 mov al, BYTE PTR [edi+0x174]
 test al, 0x2
 je .Lalternate
 test al, 0x4
 jne .Leligible
.Lalternate:
 cmp BYTE PTR [edi+0x190], 0
 jne .Leligible
 {load} xor al, al
 pop edi
 pop ebp
 ret 4
.Leligible:
 push ebx
 mov ebx, DWORD PTR [ebp+0x8]
 cmp DWORD PTR [edi+0x8], ebx
 jne .Lchildren
 cmp DWORD PTR [edi+0x10], 3
 je .Lmatched
 mov eax, DWORD PTR [edi]
 push -1
 push 1
 call DWORD PTR [eax+0x54]
.Lmatched:
 pop ebx
 mov al, 1
 pop edi
 pop ebp
 ret 4
.Lchildren:
 push esi
 mov esi, DWORD PTR [edi+0x178]
 cmp esi, DWORD PTR [edi+0x17c]
 je .Lfailed
.Lloop:
 mov ecx, DWORD PTR [esi]
 push ebx
 call original_ui_item_set_focus_id
 test al, al
 jne .Lsuccess
 add esi, 4
 cmp esi, DWORD PTR [edi+0x17c]
 jne .Lloop
.Lfailed:
 pop esi
 pop ebx
 {load} xor al, al
 pop edi
 pop ebp
 ret 4
.Lsuccess:
 pop esi
 pop ebx
 mov al, 1
 pop edi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
