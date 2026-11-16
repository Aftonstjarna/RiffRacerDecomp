.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x546a30,0x546aec); excludes following INT3 padding.
.global original_simplex_solver_contains_vertex
original_simplex_solver_contains_vertex:
push   ebp
mov.s    ebp,esp
mov    edx,DWORD PTR [ebp+0x8]
push   ebx
push   esi
mov    esi,DWORD PTR [ecx]
xor.s    bl,bl
push   edi
test   esi,esi
jle .L546a9a
movss  xmm3,DWORD PTR [edx]
lea    eax,[ecx+0xc]
movss  xmm4,DWORD PTR [edx+0x4]
mov    edi,0x1
movss  xmm5,DWORD PTR [edx+0x8]
movss  xmm6,DWORD PTR [ecx+0x134]
nop
.L546a60:
movaps xmm1,xmm3
movzx  ebx,bl
subss  xmm1,DWORD PTR [eax-0x8]
movaps xmm2,xmm4
movaps xmm0,xmm5
subss  xmm2,DWORD PTR [eax-0x4]
subss  xmm0,DWORD PTR [eax]
mulss  xmm1,xmm1
mulss  xmm2,xmm2
mulss  xmm0,xmm0
addss  xmm2,xmm1
addss  xmm2,xmm0
comiss xmm6,xmm2
cmovae ebx,edi
add    eax,0x10
dec    esi
jne .L546a60
.L546a9a:
movss  xmm0,DWORD PTR [edx+0xc]
ucomiss xmm0,DWORD PTR [ecx+0x130]
lahf
test   ah,0x44
jp .L546ae3
movss  xmm0,DWORD PTR [edx+0x8]
ucomiss xmm0,DWORD PTR [ecx+0x12c]
lahf
test   ah,0x44
jp .L546ae3
movss  xmm0,DWORD PTR [edx+0x4]
ucomiss xmm0,DWORD PTR [ecx+0x128]
lahf
test   ah,0x44
jp .L546ae3
movss  xmm0,DWORD PTR [edx]
mov    al,0x1
ucomiss xmm0,DWORD PTR [ecx+0x124]
lahf
test   ah,0x44
jnp .L546ae5
.L546ae3:
mov.s    al,bl
.L546ae5:
pop    edi
pop    esi
pop    ebx
pop    ebp
ret    0x4
.section .note.GNU-stack,"",@progbits
