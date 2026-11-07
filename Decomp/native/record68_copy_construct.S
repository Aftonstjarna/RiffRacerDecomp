# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x509ef0,0x509f52); 98 bytes, no padding.
.intel_syntax noprefix
.code32
.text
.global original_record68_copy_construct
original_record68_copy_construct:
 push   ebp
 mov.s    ebp,esp
 mov    edx,DWORD PTR [ebp+0x8]
 mov    eax,DWORD PTR [edx]
 mov    DWORD PTR [ecx],eax
 mov    eax,DWORD PTR [edx+0x4]
 mov    DWORD PTR [ecx+0x4],eax
 mov    eax,DWORD PTR [edx+0x8]
 mov    DWORD PTR [ecx+0x8],eax
 mov    eax,DWORD PTR [edx+0xc]
 mov    DWORD PTR [ecx+0xc],eax
 mov    eax,DWORD PTR [edx+0x10]
 mov    DWORD PTR [ecx+0x10],eax
 mov    eax,DWORD PTR [edx+0x14]
 mov    DWORD PTR [ecx+0x14],eax
 mov    eax,DWORD PTR [edx+0x18]
 mov    DWORD PTR [ecx+0x18],eax
 mov    eax,DWORD PTR [edx+0x1c]
 mov    DWORD PTR [ecx+0x1c],eax
 mov    eax,DWORD PTR [edx+0x20]
 mov    DWORD PTR [ecx+0x20],eax
 mov    eax,DWORD PTR [edx+0x24]
 mov    DWORD PTR [ecx+0x24],eax
 mov    eax,DWORD PTR [edx+0x28]
 mov    DWORD PTR [ecx+0x28],eax
 mov    eax,DWORD PTR [edx+0x2c]
 mov    DWORD PTR [ecx+0x2c],eax
 mov    eax,DWORD PTR [edx+0x30]
 mov    DWORD PTR [ecx+0x30],eax
 mov.s    eax,ecx
 movdqu xmm0,XMMWORD PTR [edx+0x34]
 movdqu XMMWORD PTR [ecx+0x34],xmm0
 pop    ebp
 ret    0x4
.section .note.GNU-stack,"",@progbits
