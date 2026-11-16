.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x55dd90,0x55ddcd); all three returns / four origin paths; INT3 padding excluded.
# cdecl: (state*, signed displacement, origin), EAX = resulting position.
.global original_audio_memory_seek_callback
original_audio_memory_seek_callback:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+0x10]
    sub eax,0
    je .Labsolute
    dec eax
    je .Lrelative
    dec eax
    mov eax,DWORD PTR [ebp+8]
    jne .Lreturn_position
    mov ecx,DWORD PTR [eax+0x30]
    add ecx,DWORD PTR [ebp+0xc]
    mov DWORD PTR [eax+0x34],ecx
    mov.s eax,ecx
    pop ebp
    ret
.Lrelative:
    mov eax,DWORD PTR [ebp+8]
    mov ecx,DWORD PTR [ebp+0xc]
    add DWORD PTR [eax+0x34],ecx
    mov eax,DWORD PTR [eax+0x34]
    pop ebp
    ret
.Labsolute:
    mov eax,DWORD PTR [ebp+8]
    mov ecx,DWORD PTR [ebp+0xc]
    mov DWORD PTR [eax+0x34],ecx
.Lreturn_position:
    mov eax,DWORD PTR [eax+0x34]
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
