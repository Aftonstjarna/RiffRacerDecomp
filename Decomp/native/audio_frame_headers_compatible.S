.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58f460,0x58f499); both returns included, INT3 padding excluded.
.global original_audio_frame_headers_compatible
original_audio_frame_headers_compatible:
push ebx
mov.s ebx,edx
mov.s eax,ecx
xor.s eax,ebx
test eax,0xfffe0c00
jne .Lreject
and ecx,0xc0
xor.s edx,edx
cmp cl,0xc0
sete dl
and ebx,0xc0
xor.s eax,eax
cmp bl,0xc0
sete al
cmp.s edx,eax
jne .Lreject
mov eax,1
pop ebx
ret
.Lreject:
xor.s eax,eax
pop ebx
ret
.section .note.GNU-stack,"",@progbits
