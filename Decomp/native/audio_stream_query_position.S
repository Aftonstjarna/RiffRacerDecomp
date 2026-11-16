.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x58dc90,0x58dcb9); adjacent INT3 padding excluded.
# cdecl: one stream pointer on stack, position returned in EAX.
.global original_audio_stream_query_position
original_audio_stream_query_position:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+0x8]
    test BYTE PTR [eax+0x6d50],0x8
    je .Lcached
    mov ecx,DWORD PTR [eax+0x6d90]
    add ecx,DWORD PTR [eax+0x6d88]
    mov DWORD PTR [eax+0x6d44],ecx
.Lcached:
    mov eax,DWORD PTR [eax+0x6d44]
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
