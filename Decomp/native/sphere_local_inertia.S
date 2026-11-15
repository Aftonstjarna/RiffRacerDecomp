# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x47d7e0,0x47d836); adjacent INT3 padding excluded.
# Sphere vtable 0x9f987c +0x1c; thiscall ECX=this, float mass, vector* output.
# Two virtual +0x28 margin calls intentionally retained, including rounding stores.
.intel_syntax noprefix
.code32
.text
.equ INERTIA_FACTOR,0xa064fc
.global original_sphere_local_inertia
original_sphere_local_inertia:
 push ebp
 mov.s ebp,esp
 push esi
 mov.s esi,ecx
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+0x28]
 call eax
 movss xmm0,DWORD PTR [ebp+8]
 mov.s ecx,esi
 mulss xmm0,DWORD PTR [INERTIA_FACTOR]
 mov eax,DWORD PTR [esi]
 movss DWORD PTR [ebp+8],xmm0
 fmul DWORD PTR [ebp+8]
 mov eax,DWORD PTR [eax+0x28]
 fstp DWORD PTR [ebp+8]
 call eax
 fmul DWORD PTR [ebp+8]
 mov eax,DWORD PTR [ebp+12]
 pop esi
 fstp DWORD PTR [ebp+8]
 movss xmm0,DWORD PTR [ebp+8]
 movss DWORD PTR [eax],xmm0
 movss DWORD PTR [eax+4],xmm0
 movss DWORD PTR [eax+8],xmm0
 mov DWORD PTR [eax+12],0
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
