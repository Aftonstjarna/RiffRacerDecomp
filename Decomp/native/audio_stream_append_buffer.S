.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x58e250,0x58e299), 73 bytes; sole return 0x58e298.
# ECX=stream, EDX=input bytes, stack=count, caller pops count.
# EAX=0 on append success, -1 on failure. ESI/EBP preserved.
.equ buffer_append,0x58dfc0
.equ diagnostic_format,0xa03c98
.equ iob_iat,0x92d390
.equ fprintf_iat,0x92d38c
.global original_audio_stream_append_buffer
original_audio_stream_append_buffer:
    push ebp
    mov.s ebp,esp
    push esi
    push DWORD PTR [ebp+8]
    mov.s esi,ecx
    lea ecx,[esi+0x6d7c]
    call buffer_append
    add esp,4
    test eax,eax
    je .Ldone
    # Quiet flag suppresses logging, but still reports failure.
    test BYTE PTR [esi+0x6dac],0x20
    jne .Lfailure
    push -1
    push 0x301
    push diagnostic_format
    call DWORD PTR [iob_iat]
    add eax,0x40
    push eax
    call DWORD PTR [fprintf_iat]
    add esp,0x10
.Lfailure:
    or eax,-1
.Ldone:
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
