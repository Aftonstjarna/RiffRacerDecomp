.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x478850, complete instruction span through ret 8 at 0x478887.
.global original_random_range_inclusive
original_random_range_inclusive:
    push ebp
    {load} mov ebp, esp
    imul eax, DWORD PTR [ecx], 0x27
    add eax, 0x27a39e8f
    mov DWORD PTR [ecx], eax
    shl DWORD PTR [ecx], 0xd
    mov edx, DWORD PTR [ecx]
    sar eax, 0x13
    and eax, 0x1fff
    {load} or edx, eax
    mov DWORD PTR [ecx], edx
    and edx, 0x7fffffff
    mov ecx, DWORD PTR [ebp+0xc]
    {load} mov eax, edx
    sub ecx, DWORD PTR [ebp+0x8]
    {load} xor edx, edx
    inc ecx
    div ecx
    add edx, DWORD PTR [ebp+0x8]
    {load} mov eax, edx
    pop ebp
    ret 8
.section .note.GNU-stack,"",@progbits
