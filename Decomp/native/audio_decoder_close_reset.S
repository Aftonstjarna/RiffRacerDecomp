.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x55c990, exclusive end 0x55c9e5.
.equ audio_reset,0x58a500
.global original_audio_decoder_close_reset
original_audio_decoder_close_reset:
    push esi
    {load} mov esi, ecx
    test esi, esi
    jne nonnull
    or eax, -1
    pop esi
    ret
nonnull:
    mov eax, DWORD PTR [esi+0x6d3c]
    mov eax, DWORD PTR [eax+4]
    test eax, eax
    je after_callback
    push esi
    call eax
    add esp, 4
 after_callback:
    cmp DWORD PTR [esi+4], 0
    je reset
    mov DWORD PTR [esi+0x6cec], 0
    mov DWORD PTR [esi+0x6cf8], 0
    mov DWORD PTR [esi+0x6cf4], 0
    mov DWORD PTR [esi+4], 0
reset:
    {load} mov ecx, esi
    call audio_reset
    {load} xor eax, eax
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
