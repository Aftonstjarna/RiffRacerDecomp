.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x58d830,0x58d87a); all three returns included; INT3 padding excluded.
.global original_audio_input_read_dispatch
original_audio_input_read_dispatch:
push ebp
mov.s ebp,esp
mov eax,DWORD PTR [ebp+8]
test BYTE PTR [eax+0x6d50],0x40
je .Ldefault
mov ecx,DWORD PTR [eax+0x6d64]
test ecx,ecx
je .Lmissing
push DWORD PTR [ebp+0x10]
push DWORD PTR [ebp+0xc]
push DWORD PTR [eax+0x6d4c]
call ecx
add esp,0xc
pop ebp
ret
.Lmissing:
or eax,-1
pop ebp
ret
.Ldefault:
push DWORD PTR [ebp+0x10]
push DWORD PTR [ebp+0xc]
push DWORD PTR [eax+0x6d48]
mov eax,DWORD PTR [eax+0x6d70]
call eax
add esp,0xc
pop ebp
ret
.section .note.GNU-stack,"",@progbits
