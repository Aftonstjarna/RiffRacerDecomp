.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x425bc0, 33 bytes, exclusive end 0x425be1.
# cdecl uint32 length(const uint16_t *); caller owns argument cleanup.
.global original_utf16_terminated_length
original_utf16_terminated_length:
    push ebp
    {load} mov ebp, esp
    mov eax, DWORD PTR [ebp+8]
    lea edx, [eax+2]
    {disp32} lea esp, [esp+0]
scan:
    mov cx, WORD PTR [eax]
    add eax, 2
    test cx, cx
    jne scan
    {load} sub eax, edx
    sar eax, 1
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
