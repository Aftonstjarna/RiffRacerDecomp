.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e2d0,0x58e323); all three returns, no padding.
.global original_audio_buffer_advance_position
original_audio_buffer_advance_position:
    push ebp
    mov.s ebp,esp
    mov ecx,DWORD PTR [ebp+0xc]
    mov edx,DWORD PTR [ebp+0x8]
    push esi
    test ecx,ecx
    js .Lnegative
    mov eax,DWORD PTR [edx+0x6d84]
    mov esi,DWORD PTR [edx+0x6d88]
    sub.s eax,esi
    cmp.s eax,ecx
    jge .Ladvance
    # Insufficient bytes: restore checkpoint and return -10.
    mov eax,DWORD PTR [edx+0x6d8c]
    mov ecx,0xfffffff6
    mov DWORD PTR [edx+0x6d88],eax
    mov.s eax,ecx
    pop esi
    pop ebp
    ret
.Ladvance:
    add.s ecx,esi
    mov DWORD PTR [edx+0x6d88],ecx
    js .Lreturn_ecx
    mov eax,DWORD PTR [edx+0x6d90]
    add.s eax,ecx
    pop esi
    pop ebp
    ret
.Lnegative:
    or ecx,0xffffffff
.Lreturn_ecx:
    mov.s eax,ecx
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
