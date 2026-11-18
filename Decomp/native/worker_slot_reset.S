# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x490d30.
.intel_syntax noprefix
.code32
.text
.global original_worker_slot_reset
original_worker_slot_reset:
 mov eax,DWORD PTR [ecx]
 mov DWORD PTR [ecx+4],eax
 mov eax,DWORD PTR [ecx+0xc]
 mov DWORD PTR [ecx+0x10],eax
 mov eax,DWORD PTR [ecx+0x18]
 mov DWORD PTR [ecx+0x1c],eax
 mov eax,DWORD PTR [ecx+0x24]
 mov DWORD PTR [ecx+0x28],eax
 mov eax,DWORD PTR [ecx+0x30]
 mov DWORD PTR [ecx+0x34],eax
 mov eax,DWORD PTR [ecx+0x3c]
 mov DWORD PTR [ecx+0x40],eax
 mov eax,DWORD PTR [ecx+0x48]
 mov DWORD PTR [ecx+0x4c],eax
 mov eax,DWORD PTR [ecx+0x54]
 mov DWORD PTR [ecx+0x60],0x3f800000
 mov DWORD PTR [ecx+0x64],0x3f800000
 mov DWORD PTR [ecx+0x68],0x3f800000
 mov DWORD PTR [ecx+0x6c],0
 mov DWORD PTR [ecx+0x58],eax
 mov DWORD PTR [ecx+0x70],0
 mov DWORD PTR [ecx+0x78],0
 mov DWORD PTR [ecx+0x74],0
 mov DWORD PTR [ecx+0x7c],0
 mov DWORD PTR [ecx+0x80],0
 mov DWORD PTR [ecx+0x84],0
 mov DWORD PTR [ecx+0x94],0
 mov DWORD PTR [ecx+0x88],0
 mov DWORD PTR [ecx+0x8c],0
 mov DWORD PTR [ecx+0x90],0
 mov DWORD PTR [ecx+0x98],0
 mov DWORD PTR [ecx+0x19c],0
 mov DWORD PTR [ecx+0x1a0],0
 mov BYTE PTR [ecx+0x1a4],0
 mov DWORD PTR [ecx+0x1a8],0
 ret
.section .note.GNU-stack,"",@progbits
