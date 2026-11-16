.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x546240, exclusive end 0x54629f.
.equ reset_vector,0xa06c00
.global original_simplex_solver_reset
original_simplex_solver_reset:
movaps xmm0,XMMWORD PTR [reset_vector]
mov eax,0xfff0
mov BYTE PTR [ecx+0x138],0
mov DWORD PTR [ecx],0
mov BYTE PTR [ecx+0x164],1
movdqu XMMWORD PTR [ecx+0x124],xmm0
mov BYTE PTR [ecx+0x160],0
mov DWORD PTR [ecx+0x150],0
mov DWORD PTR [ecx+0x154],0
mov DWORD PTR [ecx+0x158],0
mov DWORD PTR [ecx+0x15c],0
and WORD PTR [ecx+0x14c],ax
ret
.section .note.GNU-stack,"",@progbits
