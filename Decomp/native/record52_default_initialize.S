# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x568200,0x56825d). No branches/calls; sole RET at 0x56825c.
# ECX points to writable 52-byte record; EAX returns ECX. No stack arguments.
.intel_syntax noprefix
.code32
.text
.global original_record52_default_initialize
original_record52_default_initialize:
 mov DWORD PTR [ecx],0xbf800000
 mov.s eax,ecx
 mov DWORD PTR [ecx+0x4],0
 mov DWORD PTR [ecx+0x8],0
 mov DWORD PTR [ecx+0xc],0
 mov DWORD PTR [ecx+0x10],0
 mov DWORD PTR [ecx+0x14],0
 mov DWORD PTR [ecx+0x18],0
 mov DWORD PTR [ecx+0x1c],0xffffffff
 mov DWORD PTR [ecx+0x20],0
 mov DWORD PTR [ecx+0x24],0x3f800000
 mov DWORD PTR [ecx+0x28],0x3f800000
 mov DWORD PTR [ecx+0x2c],0x3f800000
 mov DWORD PTR [ecx+0x30],0x3f800000
 ret
.section .note.GNU-stack,"",@progbits
