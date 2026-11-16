.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x546130; exclusive end 0x54623d.
.global original_simplex_solver_reduce_vertices
original_simplex_solver_reduce_vertices:
push   ebp
mov.s    ebp,esp
mov    eax,DWORD PTR [ecx]
mov    edx,DWORD PTR [ebp+0x8]
cmp    eax,0x4
jl .L546179
test   BYTE PTR [edx],0x8
jne .L546179
dec    eax
mov    DWORD PTR [ecx],eax
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x4]
movdqu XMMWORD PTR [ecx+0x34],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x54]
movdqu XMMWORD PTR [ecx+0x84],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0xa4]
movdqu XMMWORD PTR [ecx+0xd4],xmm0
.L546179:
mov    eax,DWORD PTR [ecx]
cmp    eax,0x3
jl .L5461b9
test   BYTE PTR [edx],0x4
jne .L5461b9
dec    eax
mov    DWORD PTR [ecx],eax
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x4]
movdqu XMMWORD PTR [ecx+0x24],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x54]
movdqu XMMWORD PTR [ecx+0x74],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0xa4]
movdqu XMMWORD PTR [ecx+0xc4],xmm0
.L5461b9:
mov    eax,DWORD PTR [ecx]
cmp    eax,0x2
jl .L5461f9
test   BYTE PTR [edx],0x2
jne .L5461f9
dec    eax
mov    DWORD PTR [ecx],eax
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x4]
movdqu XMMWORD PTR [ecx+0x14],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x54]
movdqu XMMWORD PTR [ecx+0x64],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0xa4]
movdqu XMMWORD PTR [ecx+0xb4],xmm0
.L5461f9:
mov    eax,DWORD PTR [ecx]
cmp    eax,0x1
jl .L546239
test   BYTE PTR [edx],0x1
jne .L546239
dec    eax
mov    DWORD PTR [ecx],eax
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x4]
movdqu XMMWORD PTR [ecx+0x4],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0x54]
movdqu XMMWORD PTR [ecx+0x54],xmm0
mov    eax,DWORD PTR [ecx]
add.s    eax,eax
movdqu xmm0,XMMWORD PTR [ecx+eax*8+0xa4]
movdqu XMMWORD PTR [ecx+0xa4],xmm0
.L546239:
pop    ebp
ret    0x4
.section .note.GNU-stack,"",@progbits
