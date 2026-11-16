.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58a120,0x58a158); includes skipped instruction padding.
.global original_audio_unity_arrays_initialize
original_audio_unity_arrays_initialize:
    mov DWORD PTR [ecx+0x2448],0
    mov eax,0x20
    add ecx,0x244c
    jmp .Lloop
    {disp32} lea esp,[esp+0]
    mov.s edi,edi
.Lloop:
    mov DWORD PTR [ecx+0x80],0x3f800000
    lea ecx,[ecx+4]
    mov DWORD PTR [ecx-4],0x3f800000
    dec eax
    jne .Lloop
    ret
.section .note.GNU-stack,"",@progbits
