.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e820,0x58e88d); both returns included; INT3 padding excluded.
.equ callback_table_contains,0x58e7e0
.equ special_callback,0x5ae540
.equ diagnostic_text,0xa03ed0
.equ iob_func_iat,0x92d390
.equ fprintf_iat,0x92d38c
.global original_audio_selected_callback_validate
original_audio_selected_callback_validate:
    push esi
    mov.s esi,ecx
    mov ecx,DWORD PTR [esi+0x4cb4]
    cmp ecx,special_callback
    jne .Lcheck
    mov ecx,DWORD PTR [esi+0x4ba4]
.Lcheck:
    call callback_table_contains
    test eax,eax
    je .Linvalid
    mov DWORD PTR [esi+0x4ca4],1
    xor.s eax,eax
    mov DWORD PTR [esi+0x4ca8],1
    pop esi
    ret
.Linvalid:
    test BYTE PTR [esi+0x6dac],0x20
    jne .Lerror
    push 0x149
    push diagnostic_text
    call DWORD PTR [iob_func_iat]
    add eax,0x40
    push eax
    call DWORD PTR [fprintf_iat]
    add esp,0xc
.Lerror:
    mov DWORD PTR [esi+0x6ed8],0x25
    or eax,0xffffffff
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
