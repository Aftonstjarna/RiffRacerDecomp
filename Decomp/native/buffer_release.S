# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x542a40..0x542a9b exclusive. Following five INT3 bytes are padding.
# ECX points to seven writable DWORDs. Virtual slot +8 consumes its pushed object.
.intel_syntax noprefix
.code32
.text
.global original_buffer_release
original_buffer_release:
 push esi
 mov.s esi,ecx
 mov ecx,DWORD PTR [esi+0x8]
 test ecx,ecx
 je .Lsecond
 mov eax,DWORD PTR [ecx]
 push ecx
 call DWORD PTR [eax+0x8]
.Lsecond:
 mov ecx,DWORD PTR [esi+0x4]
 mov DWORD PTR [esi+0x8],0x0
 test ecx,ecx
 je .Lfirst
 mov eax,DWORD PTR [ecx]
 push ecx
 call DWORD PTR [eax+0x8]
.Lfirst:
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [esi+0x4],0x0
 test ecx,ecx
 je .Lclear
 mov eax,DWORD PTR [ecx]
 push ecx
 call DWORD PTR [eax+0x8]
.Lclear:
 mov DWORD PTR [esi],0x0
 mov DWORD PTR [esi+0xc],0x0
 mov DWORD PTR [esi+0x10],0x0
 mov DWORD PTR [esi+0x14],0x0
 mov DWORD PTR [esi+0x18],0x0
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
