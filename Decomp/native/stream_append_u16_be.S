# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5cc7a0,0x5cc7c4); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_stream_append_u16_be
original_stream_append_u16_be:
    push esi
    push edi
    mov.s edi,ecx
    mov.s ecx,edx
    shr ecx,8
    mov eax,DWORD PTR [edi+0x14]
    mov esi,DWORD PTR [edi+0x8]
    mov BYTE PTR [esi+eax],cl
    inc DWORD PTR [edi+0x14]
    mov ecx,DWORD PTR [edi+0x14]
    mov eax,DWORD PTR [edi+0x8]
    mov BYTE PTR [ecx+eax],dl
    inc DWORD PTR [edi+0x14]
    pop edi
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
