.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x417300 through 0x417383 inclusive.
.global original_worker_resource_singleton_417300_get
original_worker_resource_singleton_417300_get:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fd7ac
 mov eax, DWORD PTR fs:0
 push eax
 push ecx
 push esi
 mov eax,DWORD PTR [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov DWORD PTR fs:0,eax
 mov eax,DWORD PTR [0xc0d400]
 test eax,eax
 jne .Ldone
 push 0x58
 call DWORD PTR [0x92d4b4]
 {load} mov esi,eax
 add esp,4
 mov DWORD PTR [ebp-0x10],esi
 mov DWORD PTR [ebp-4],0
 test esi,esi
 je .Lnull
 push 0xbaac18
 lea ecx,[esi+4]
 mov WORD PTR [esi],0x100
 mov BYTE PTR [esi+2],0x5c
 call constructor
 mov WORD PTR [esi+0x54],0x100
 mov BYTE PTR [esi+0x56],0x5c
 jmp .Lstore
.Lnull:
 {load} xor esi,esi
.Lstore:
 mov DWORD PTR [0xc0d400],esi
 {load} mov eax,esi
.Ldone:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret
.equ constructor,0x417810
.section .note.GNU-stack,"",@progbits
