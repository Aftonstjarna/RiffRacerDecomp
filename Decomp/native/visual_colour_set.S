.intel_syntax noprefix
.code32
.text
.global original_visual_colour_set
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x442f50.
original_visual_colour_set:
 push ebp
 {load} mov ebp,esp
 mov edx,DWORD PTR [ebp+8]
 movss xmm0,DWORD PTR [ecx+0x90]
 movss xmm1,DWORD PTR [edx]
 ucomiss xmm0,xmm1
 lahf
 test ah,0x44
 jp .Lcopy
 movss xmm0,DWORD PTR [ecx+0x94]
 ucomiss xmm0,DWORD PTR [edx+4]
 lahf
 test ah,0x44
 jp .Lcopy
 movss xmm0,DWORD PTR [ecx+0x98]
 ucomiss xmm0,DWORD PTR [edx+8]
 lahf
 test ah,0x44
 jp .Lcopy
 movss xmm0,DWORD PTR [ecx+0x9c]
 ucomiss xmm0,DWORD PTR [edx+12]
 lahf
 test ah,0x44
 jnp .Ldone
.Lcopy:
 movss DWORD PTR [ecx+0x90],xmm1
 mov eax,DWORD PTR [edx+4]
 mov DWORD PTR [ecx+0x94],eax
 mov eax,DWORD PTR [edx+8]
 mov DWORD PTR [ecx+0x98],eax
 mov eax,DWORD PTR [edx+12]
 mov DWORD PTR [ecx+0x9c],eax
 or DWORD PTR [ecx+0x170],0x100
.Ldone:
 pop ebp
 ret 4
