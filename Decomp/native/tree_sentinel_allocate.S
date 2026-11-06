# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x423260,0x423290), including failure tail transfer.
.intel_syntax noprefix
.code32
.text
.global original_tree_sentinel_allocate
original_tree_sentinel_allocate:
 push 0x2c
 call DWORD PTR [allocate_iat]
 add esp,4
 test eax,eax
 jne .Linitialize
 jmp DWORD PTR [failure_iat]
.Linitialize:
 lea ecx,[eax+4]
 mov DWORD PTR [eax],eax
 test ecx,ecx
 je .Lright
 mov DWORD PTR [ecx],eax
.Lright:
 lea ecx,[eax+8]
 test ecx,ecx
 je .Lflags
 mov DWORD PTR [ecx],eax
.Lflags:
 mov WORD PTR [eax+0xc],0x101
 ret
.equ allocate_iat,0x92d4b4
.equ failure_iat,0x92d164
.section .note.GNU-stack,"",@progbits
