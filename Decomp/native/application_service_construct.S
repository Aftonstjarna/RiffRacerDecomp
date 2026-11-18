# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x48ce90.
.intel_syntax noprefix
.code32
.text
.global original_application_service_construct
.equ memset_helper,0x8f8d7e
original_application_service_construct:
 push esi
 mov.s esi,ecx
 mov DWORD PTR [0xc0d410],esi
 push 0x100
 push 0
 mov DWORD PTR [esi],0x9fbdc4
 lea eax,[esi+0x40]
 mov DWORD PTR [esi+0x14],1
 mov BYTE PTR [esi+0x140],0
 mov DWORD PTR [esi+0x144],0
 mov DWORD PTR [esi+0x4],0
 mov DWORD PTR [esi+0x8],0
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+0x10],0
 mov DWORD PTR [esi+0x18],0
 mov DWORD PTR [esi+0x1c],0
 mov DWORD PTR [esi+0x20],0
 mov DWORD PTR [esi+0x24],0
 mov DWORD PTR [esi+0x28],0
 mov DWORD PTR [esi+0x2c],0
 mov DWORD PTR [esi+0x34],0
 mov DWORD PTR [esi+0x30],0
 mov DWORD PTR [esi+0x38],0
 push eax
 mov DWORD PTR [esi+0x3c],0xfffffffe
 call memset_helper
 add esp,0xc
 mov.s eax,esi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
