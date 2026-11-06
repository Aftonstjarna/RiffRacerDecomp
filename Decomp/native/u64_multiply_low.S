.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8fc1f0,0x8fc224), both return paths included.
.global original_u64_multiply_low
original_u64_multiply_low:
 mov eax,DWORD PTR [esp+8]
 mov ecx,DWORD PTR [esp+16]
 {load} or ecx,eax
 mov ecx,DWORD PTR [esp+12]
 jne high_words
 mov eax,DWORD PTR [esp+4]
 mul ecx
 ret 16
high_words:
 push ebx
 mul ecx
 {load} mov ebx,eax
 mov eax,DWORD PTR [esp+8]
 mul DWORD PTR [esp+20]
 {load} add ebx,eax
 mov eax,DWORD PTR [esp+8]
 mul ecx
 {load} add edx,ebx
 pop ebx
 ret 16
.section .note.GNU-stack,"",@progbits
