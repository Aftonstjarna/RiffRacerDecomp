# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438ab0,0x438b35); excludes INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ BOX_VTABLE,0x9f98d0
.global original_box_shape_construct
original_box_shape_construct:
 push ebp
 mov.s ebp,esp
 sub esp,0x10
 mov eax,DWORD PTR [ebp+8]
 mov DWORD PTR [ecx+8],0
 mov DWORD PTR [ecx+0xc],0x3f800000
 mov DWORD PTR [ecx+0x10],0x3f800000
 mov DWORD PTR [ecx+0x14],0x3f800000
 mov DWORD PTR [ecx+0x18],0
 mov DWORD PTR [ecx+0x2c],0x3d23d70a
 mov DWORD PTR [ecx],BOX_VTABLE
 mov DWORD PTR [ecx+4],0
 movss xmm0,DWORD PTR [eax]
 mulss xmm0,DWORD PTR [ecx+0xc]
 mov DWORD PTR [ebp-4],0
 movss DWORD PTR [ebp-0x10],xmm0
 movss xmm0,DWORD PTR [eax+4]
 mulss xmm0,DWORD PTR [ecx+0x10]
 movss DWORD PTR [ebp-0xc],xmm0
 movss xmm0,DWORD PTR [eax+8]
 mov.s eax,ecx
 mulss xmm0,DWORD PTR [ecx+0x14]
 movss DWORD PTR [ebp-8],xmm0
 movdqu xmm0,XMMWORD PTR [ebp-0x10]
 movdqu XMMWORD PTR [ecx+0x1c],xmm0
 mov.s esp,ebp
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
