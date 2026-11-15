# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d710,0x47d7dd); excludes adjacent INT3 padding.
# Sphere vtable 0x9f987c slot +4; three distinct virtual margin calls retained.
.intel_syntax noprefix
.code32
.text
.global original_sphere_aabb
original_sphere_aabb:
 push ebp
 mov.s ebp,esp
 and esp,0xfffffff0
 sub esp,0x28
 push esi
 mov.s esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+0x28]
 call eax
 mov eax,DWORD PTR [esi]
 mov.s ecx,esi
 fstp DWORD PTR [esp+0x1c]
 mov eax,DWORD PTR [eax+0x28]
 call eax
 mov eax,DWORD PTR [esi]
 mov.s ecx,esi
 fstp DWORD PTR [esp+0x18]
 mov eax,DWORD PTR [eax+0x28]
 call eax
 movss xmm0,DWORD PTR [edi+0x30]
 mov eax,DWORD PTR [ebp+0xc]
 fstp DWORD PTR [esp+0x14]
 subss xmm0,DWORD PTR [esp+0x14]
 mov DWORD PTR [esp+0x2c],0
 movss DWORD PTR [esp+0x20],xmm0
 movss xmm0,DWORD PTR [edi+0x34]
 subss xmm0,DWORD PTR [esp+0x18]
 movss DWORD PTR [esp+0x24],xmm0
 movss xmm0,DWORD PTR [edi+0x38]
 subss xmm0,DWORD PTR [esp+0x1c]
 movss DWORD PTR [esp+0x28],xmm0
 movdqu xmm0,XMMWORD PTR [esp+0x20]
 mov DWORD PTR [esp+0x2c],0
 movdqu XMMWORD PTR [eax],xmm0
 mov eax,DWORD PTR [ebp+0x10]
 movss xmm0,DWORD PTR [edi+0x30]
 addss xmm0,DWORD PTR [esp+0x14]
 movss DWORD PTR [esp+0x20],xmm0
 movss xmm0,DWORD PTR [edi+0x34]
 addss xmm0,DWORD PTR [esp+0x18]
 movss DWORD PTR [esp+0x24],xmm0
 movss xmm0,DWORD PTR [edi+0x38]
 addss xmm0,DWORD PTR [esp+0x1c]
 pop edi
 pop esi
 movss DWORD PTR [esp+0x20],xmm0
 movdqu xmm0,XMMWORD PTR [esp+0x18]
 movdqu XMMWORD PTR [eax],xmm0
 mov.s esp,ebp
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
