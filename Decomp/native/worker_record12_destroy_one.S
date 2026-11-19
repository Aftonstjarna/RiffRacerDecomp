.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x41dde0..0x41de7a, exclusive.
.equ exception_handler,0x8fdbdb
.equ security_cookie,0xbaabc0
.equ pool_get,0x4171e0
.equ handle_remove,0x41c090
.global original_worker_record12_destroy_one
original_worker_record12_destroy_one:
 push ebp
 mov.s ebp,esp
 push -1
 push exception_handler
 mov eax,DWORD PTR fs:0
 push eax
 push ecx
 push esi
 push edi
 mov eax,DWORD PTR [security_cookie]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov DWORD PTR fs:0,eax
 mov.s edi,ecx
 mov DWORD PTR [ebp-0x10],edi
 mov DWORD PTR [ebp-0x4],0
 mov ecx,DWORD PTR [edi+0x8]
 test ecx,ecx
 je .Lrelease_handle
 mov eax,DWORD PTR [ecx+0x4]
 add ecx,0x4
 mov eax,DWORD PTR [eax+0x4]
 add.s ecx,eax
 dec DWORD PTR [ecx+0x4]
 jne .Lrelease_handle
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lrelease_handle:
 mov DWORD PTR [ebp-0x4],-1
 mov esi,DWORD PTR [edi+0x4]
 test esi,esi
 js .Ldone
 call pool_get
 mov ecx,DWORD PTR [eax+0x4]
 mov eax,DWORD PTR [eax+0x28]
 movsx ecx,WORD PTR [ecx+esi*2]
 dec DWORD PTR [eax+ecx*8+0x4]
 jne .Lclear
 mov esi,DWORD PTR [edi+0x4]
 call pool_get
 push esi
 lea ecx,[eax+0x4]
 call handle_remove
.Lclear:
 mov DWORD PTR [edi+0x4],-1
.Ldone:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
