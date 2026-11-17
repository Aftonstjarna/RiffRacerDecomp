# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x491f50,0x491fb7).
.intel_syntax noprefix
.code32
.text
.global original_application_worker_stop
.equ helper_stop,0x498e00
.equ helper_notify,0x4a1870
.equ cookie_check,0x8f8958
original_application_worker_stop:
 push ebp
 mov.s ebp,esp
 sub esp,0x28
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 mov DWORD PTR [ebp-4],eax
 push esi
 mov.s esi,ecx
 push DWORD PTR [esi+0xc0]
 mov BYTE PTR [esi+0xd0],1
 call DWORD PTR [0x92d120]
 push -1
 push DWORD PTR [esi+0xb4]
 call DWORD PTR [0x92d124]
 mov.s ecx,esi
 call helper_stop
 mov eax,DWORD PTR [esi]
 mov.s ecx,esi
 call DWORD PTR [eax+0x74]
 mov ecx,DWORD PTR [0xbfcc44]
 lea eax,[ebp-0x28]
 push eax
 mov DWORD PTR [ebp-0x28],6
 call helper_notify
 mov ecx,DWORD PTR [ebp-4]
 xor.s ecx,ebp
 pop esi
 call cookie_check
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
