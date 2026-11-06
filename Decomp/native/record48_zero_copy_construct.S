# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x427010..0x42708b (exclusive); padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_record48_zero_copy_construct
original_record48_zero_copy_construct:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 # Preserve original initialization order, including aliasing side effects.
 mov DWORD PTR [ecx],0
 mov DWORD PTR [ecx+4],0
 mov DWORD PTR [ecx+8],0
 mov DWORD PTR [ecx+12],0
 mov DWORD PTR [ecx+16],0
 mov DWORD PTR [ecx+20],0
 mov DWORD PTR [ecx+24],0
 mov DWORD PTR [ecx+28],0
 mov DWORD PTR [ecx+32],0
 mov DWORD PTR [ecx+36],0
 mov DWORD PTR [ecx+40],0
 mov DWORD PTR [ecx+44],0
 movdqu xmm0,XMMWORD PTR [eax]
 movdqu XMMWORD PTR [ecx],xmm0
 movdqu xmm0,XMMWORD PTR [eax+16]
 movdqu XMMWORD PTR [ecx+16],xmm0
 movdqu xmm0,XMMWORD PTR [eax+32]
 {load} mov eax,ecx
 movdqu XMMWORD PTR [ecx+32],xmm0
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
