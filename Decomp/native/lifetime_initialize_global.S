# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x44ebe0.
.intel_syntax noprefix
.code32
.text
.global original_lifetime_initialize_global
.equ constructor,0x44e5d0
original_lifetime_initialize_global:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8fdfcc
 mov eax,fs:0
 push eax
 push ecx
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 cmp DWORD PTR [0xbfcbbc],0
 jne .Ldone
 push 0x390
 call DWORD PTR [0x92d4b4]
 add esp,4
 mov DWORD PTR [ebp-0x10],eax
 mov DWORD PTR [ebp-4],0
 test.s eax,eax
 je .Lnull
 mov.s ecx,eax
 call constructor
 mov DWORD PTR [0xbfcbbc],eax
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 mov.s esp,ebp
 pop ebp
 ret
.Lnull:
 xor.s eax,eax
 mov DWORD PTR [0xbfcbbc],eax
.Ldone:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
