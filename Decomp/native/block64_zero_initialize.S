.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41e770,0x41e7e2); excludes INT3 padding.
.global original_block64_zero_initialize
original_block64_zero_initialize:
mov DWORD PTR [ecx],0
mov.s eax,ecx
mov DWORD PTR [ecx+0x4],0
mov DWORD PTR [ecx+0x8],0
mov DWORD PTR [ecx+0xc],0
mov DWORD PTR [ecx+0x10],0
mov DWORD PTR [ecx+0x14],0
mov DWORD PTR [ecx+0x18],0
mov DWORD PTR [ecx+0x1c],0
mov DWORD PTR [ecx+0x20],0
mov DWORD PTR [ecx+0x24],0
mov DWORD PTR [ecx+0x28],0
mov DWORD PTR [ecx+0x2c],0
mov DWORD PTR [ecx+0x30],0
mov DWORD PTR [ecx+0x34],0
mov DWORD PTR [ecx+0x38],0
mov DWORD PTR [ecx+0x3c],0
ret
.section .note.GNU-stack,"",@progbits
