.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58eb00, complete range [0x58eb00,0x58eb3b).
.global original_audio_frame_header_plausible
original_audio_frame_header_plausible:
mov.s eax,ecx
and eax,0xffe00000
cmp eax,0xffe00000
jne .Lreject
test ecx,0x60000
je .Lreject
mov.s eax,ecx
and eax,0xf000
cmp eax,0xf000
je .Lreject
and ecx,0xc00
cmp ecx,0xc00
je .Lreject
mov eax,1
ret
.Lreject:
xor.s eax,eax
ret
.section .note.GNU-stack,"",@progbits
