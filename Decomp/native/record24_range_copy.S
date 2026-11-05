# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4b3e40, end exclusive 0x4b3e72.
.intel_syntax noprefix
.code32
.text
.global original_record24_range_copy
original_record24_range_copy:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 {load} cmp ecx,edx
 je .Ldone
 {disp32} lea ebx,[ebx+0]
.Lloop:
 test eax,eax
 je .Ladvance
 movdqu xmm0,XMMWORD PTR [ecx]
 movdqu XMMWORD PTR [eax],xmm0
 movq xmm0,QWORD PTR [ecx+16]
 movq QWORD PTR [eax+16],xmm0
.Ladvance:
 add ecx,24
 add eax,24
 {load} cmp ecx,edx
 jne .Lloop
.Ldone:
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
