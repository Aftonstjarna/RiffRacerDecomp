.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5963d0,0x596431). One loop branch and sole ret at 0x596430.
# INT3 padding through 0x59643f is excluded; next entry is 0x596440.
.equ pow_precise_thunk,0x8f8f2e
.global original_audio_coefficient_row_generate
original_audio_coefficient_row_generate:
 push ebp
 mov.s ebp,esp
 and esp,-8
 push ecx
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+0x10]
 mov ebx,3
 push edi
 mov edi,DWORD PTR [ebp+0xc]
 mov DWORD PTR [esp+0xc],0x3f
 {disp8} lea ecx,[ecx+0]
.Lcoefficient:
 movd xmm1,ebx
 cvtdq2pd xmm1,xmm1
 movsd xmm0,QWORD PTR ds:0xa06620
 divsd xmm1,QWORD PTR ds:0xa06638
 call pow_precise_thunk
 mulsd xmm0,QWORD PTR [esi*8+0x9f10d0]
 dec ebx
 cvtsd2ss xmm0,xmm0
 movss DWORD PTR [edi],xmm0
 add edi,4
 dec DWORD PTR [esp+0xc]
 jne .Lcoefficient
 mov.s eax,edi
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
