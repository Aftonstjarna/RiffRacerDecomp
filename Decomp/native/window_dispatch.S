.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x48c6e0.
.equ object_handler,0x48c740
.global original_window_dispatch
original_window_dispatch:
 push ebp
 {load} mov ebp,esp
 push ebx
 mov ebx,DWORD PTR [ebp+12]
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 cmp ebx,0x81
 jne get_object
 mov edi,DWORD PTR [ebp+20]
 mov edi,DWORD PTR [edi]
 push edi
 push -21
 push esi
 call DWORD PTR [0x92d560]
dispatch:
 push DWORD PTR [ebp+20]
 {load} mov ecx,edi
 push DWORD PTR [ebp+16]
 push ebx
 push esi
 call object_handler
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 16
get_object:
 push -21
 push esi
 call DWORD PTR [0x92d5b4]
 {load} mov edi,eax
 test edi,edi
 jne dispatch
 push DWORD PTR [ebp+20]
 push DWORD PTR [ebp+16]
 push ebx
 push esi
 call DWORD PTR [0x92d590]
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret 16
.section .note.GNU-stack,"",@progbits
