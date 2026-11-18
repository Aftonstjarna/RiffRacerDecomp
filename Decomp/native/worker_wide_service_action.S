# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x44f5b0.
.intel_syntax noprefix
.code32
.text
.global original_worker_wide_service_action
.equ service,0x6d86bb
.equ make_wide,0x44f490
.equ cookie_check,0x8f8958
original_worker_wide_service_action:
 push ebp
 mov.s ebp,esp
 sub esp,0x1c
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 mov DWORD PTR [ebp-4],eax
 push esi
 mov.s esi,ecx
 call service
 push 1
 mov.s ecx,eax
 mov edx,DWORD PTR [eax]
 call DWORD PTR [edx+0xc]
 mov.s edx,eax
 lea ecx,[ebp-0x1c]
 call make_wide
 cmp DWORD PTR [ebp-8],8
 lea eax,[ebp-0x1c]
 cmovae eax,DWORD PTR [ebp-0x1c]
 cmp DWORD PTR [esi+0x14],8
 jb .Linline
 mov esi,DWORD PTR [esi]
.Linline:
 push 0x10
 push eax
 push esi
 push 0
 call DWORD PTR [0x92d594]
 cmp DWORD PTR [ebp-8],8
 jb .Ldone
 push DWORD PTR [ebp-0x1c]
 call DWORD PTR [0x92d4b0]
 add esp,4
.Ldone:
 mov ecx,DWORD PTR [ebp-4]
 xor.s ecx,ebp
 pop esi
 call cookie_check
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
