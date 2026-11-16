.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58f4a0, complete 149-byte function ending at 0x58f535.
.equ memcpy_import,0x8f8d66
.equ audio_bitstream_read16,0x58eab0
.global original_audio_frame_reuse_buffered
original_audio_frame_reuse_buffered:
    push esi
    {load} mov esi,ecx
    mov eax,DWORD PTR [esi+0x6dbc]
    test eax,eax
    je no_frame
    mov ecx,DWORD PTR [esi+0x2570]
    test ecx,ecx
    je seed_count
    cmp DWORD PTR [esi+0x4ce8],0x3
    lea eax,[ecx-0x1]
    mov ecx,DWORD PTR [esi+0x6ca8]
    mov DWORD PTR [esi+0x6d08],0x1
    mov DWORD PTR [esi+0x6d04],0x1
    mov DWORD PTR [esi+0x2570],eax
    mov DWORD PTR [esi+0x4d4c],0x0
    mov DWORD PTR [esi+0x4d50],ecx
    jne after_copy
    push DWORD PTR [esi+0x4da0]
    lea eax,[esi+0x254c]
    push eax
    push ecx
    call memcpy_import
    add esp,0xc
 after_copy:
    cmp DWORD PTR [esi+0x4cf4],0x0
    je frame_ready
    {load} mov ecx,esi
    call audio_bitstream_read16
    mov DWORD PTR [esi+0x6d38],eax
 frame_ready:
    mov eax,0x1
    pop esi
    ret
 seed_count:
    dec eax
    mov DWORD PTR [esi+0x2570],eax
 no_frame:
    {load} xor eax,eax
    pop esi
    ret
