# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4271a0,0x42727a); adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_affine48_to_matrix64
original_affine48_to_matrix64:
 push   ebp
 mov.s    ebp,esp
 sub    esp,0x44
 mov    eax,DWORD PTR [0xbaabc0]
 xor.s    eax,ebp
 mov    DWORD PTR [ebp-0x4],eax
 movss  xmm0,DWORD PTR [edx+0x24]
 mov.s    eax,ecx
 movss  DWORD PTR [ebp-0x44],xmm0
 movss  xmm0,DWORD PTR [edx+0x28]
 movss  DWORD PTR [ebp-0x40],xmm0
 movss  xmm0,DWORD PTR [edx+0x2c]
 movss  DWORD PTR [ebp-0x3c],xmm0
 mov    DWORD PTR [ebp-0x38],0x0
 movdqu xmm0,XMMWORD PTR [ebp-0x44]
 mov    DWORD PTR [ebp-0x28],0x0
 mov    DWORD PTR [ebp-0x18],0x0
 movdqu XMMWORD PTR [ecx+0x30],xmm0
 mov    DWORD PTR [ebp-0x8],0x0
 movss  xmm0,DWORD PTR [edx]
 movss  DWORD PTR [ebp-0x34],xmm0
 movss  xmm0,DWORD PTR [edx+0xc]
 movss  DWORD PTR [ebp-0x30],xmm0
 movss  xmm0,DWORD PTR [edx+0x18]
 movss  DWORD PTR [ebp-0x2c],xmm0
 movss  xmm0,DWORD PTR [edx+0x4]
 movss  DWORD PTR [ebp-0x24],xmm0
 movss  xmm0,DWORD PTR [edx+0x10]
 movss  DWORD PTR [ebp-0x20],xmm0
 movss  xmm0,DWORD PTR [edx+0x1c]
 movss  DWORD PTR [ebp-0x1c],xmm0
 movss  xmm0,DWORD PTR [edx+0x8]
 movss  DWORD PTR [ebp-0x14],xmm0
 movss  xmm0,DWORD PTR [edx+0x14]
 movss  DWORD PTR [ebp-0x10],xmm0
 movss  xmm0,DWORD PTR [edx+0x20]
 movss  DWORD PTR [ebp-0xc],xmm0
 movdqu xmm0,XMMWORD PTR [ebp-0x34]
 movdqu XMMWORD PTR [ecx],xmm0
 movdqu xmm0,XMMWORD PTR [ebp-0x24]
 movdqu XMMWORD PTR [ecx+0x10],xmm0
 movdqu xmm0,XMMWORD PTR [ebp-0x14]
 movdqu XMMWORD PTR [ecx+0x20],xmm0
 mov    ecx,DWORD PTR [ebp-0x4]
 xor.s    ecx,ebp
 call cookie_check
 mov.s    esp,ebp
 pop    ebp
 ret
.equ cookie_check,0x8f8958
.section .note.GNU-stack,"",@progbits
