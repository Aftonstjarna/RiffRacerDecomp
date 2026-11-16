.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x55c9f0,0x55ca1a); excludes INT3 padding.
.equ sample_rates,0x9ee8f0
.global original_audio_sample_rate_index
original_audio_sample_rate_index:
xor.s eax,eax
.Lscan:
cmp DWORD PTR [eax*4+sample_rates],edx
je .Lreturn
inc eax
cmp eax,9
jl .Lscan
test ecx,ecx
je .Lmissing
mov eax,DWORD PTR [ecx+8]
test eax,eax
je .Lmissing
cmp.s eax,edx
jne .Lmissing
mov eax,9
ret
.Lmissing:
or eax,-1
.Lreturn:
ret
.section .note.GNU-stack,"",@progbits
