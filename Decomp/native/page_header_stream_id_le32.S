.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x59b370 through 0x59b391 inclusive.
.global original_page_header_stream_id_le32
original_page_header_stream_id_le32:
    mov edx, DWORD PTR [ecx]
    movzx eax, BYTE PTR [edx+0x11]
    movzx ecx, BYTE PTR [edx+0x10]
    shl eax, 8
    {load} or eax, ecx
    movzx ecx, BYTE PTR [edx+0xf]
    shl eax, 8
    {load} or eax, ecx
    movzx ecx, BYTE PTR [edx+0xe]
    shl eax, 8
    {load} or eax, ecx
    ret
.section .note.GNU-stack,"",@progbits
