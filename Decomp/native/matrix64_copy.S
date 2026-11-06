# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426fd0,0x427002). INT3 padding excluded.
# ECX=destination, [entry ESP+4]=source; EAX=destination; callee pops 4.
# Four ordered unaligned 16-byte transfers; overlapping copies retain this order.
.intel_syntax noprefix
.code32
.text
.global original_matrix64_copy
original_matrix64_copy:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 movdqu xmm0,XMMWORD PTR [eax]
 movdqu XMMWORD PTR [ecx],xmm0
 movdqu xmm0,XMMWORD PTR [eax+0x10]
 movdqu XMMWORD PTR [ecx+0x10],xmm0
 movdqu xmm0,XMMWORD PTR [eax+0x20]
 movdqu XMMWORD PTR [ecx+0x20],xmm0
 movdqu xmm0,XMMWORD PTR [eax+0x30]
 {load} mov eax,ecx
 movdqu XMMWORD PTR [ecx+0x30],xmm0
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
