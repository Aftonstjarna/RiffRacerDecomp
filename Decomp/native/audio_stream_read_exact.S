.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58dc60,0x58dc88); following INT3 padding excluded.
# cdecl (stream, destination, count); delegates through stream backend +8.
.global original_audio_stream_read_exact
original_audio_stream_read_exact:
push ebp
mov.s ebp,esp
mov eax,DWORD PTR [ebp+8]
push DWORD PTR [ebp+0x10]
push DWORD PTR [ebp+0xc]
mov ecx,DWORD PTR [eax+0x6d3c]
push eax
mov eax,DWORD PTR [ecx+8]
call eax
add esp,0xc
mov ecx,-10
cmp eax,DWORD PTR [ebp+0x10]
cmovne eax,ecx
pop ebp
ret
.section .note.GNU-stack,"",@progbits
