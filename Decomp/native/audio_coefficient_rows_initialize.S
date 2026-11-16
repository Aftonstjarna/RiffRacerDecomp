.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x596390,0x5963c1); sole ret at 0x5963c0; INT3 padding excluded.
# ECX=audio state, no stack arguments; preserves EBX/ESI/EDI/EBP.
.equ generate_coefficients,0x5963d0
.global original_audio_coefficient_rows_initialize
original_audio_coefficient_rows_initialize:
 push ebx
 mov.s ebx,ecx
 push esi
 push edi
 xor.s esi,esi
 lea edi,[ebx+0x3098]
 {disp8} lea ecx,[ecx+0x0]
.Lrow:
 push esi
 push edi
 push ebx
 call generate_coefficients
 inc esi
 add esp,0xc
 add edi,0x100
 mov DWORD PTR [eax],0
 cmp esi,0x1b
 jl .Lrow
 pop edi
 pop esi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
