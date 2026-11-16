.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e330,0x58e3ce); all five returns included; padding excluded.
.global original_audio_buffer_adjust_position
original_audio_buffer_adjust_position:
    push ebp
    mov.s ebp,esp
    mov ecx,DWORD PTR [ebp+0xc]
    # Nonnegative amount rewinds; reject requests beyond current position.
    test ecx,ecx
    js .L58e366
    mov eax,DWORD PTR [ebp+0x8]
    mov edx,DWORD PTR [eax+0x6d88]
    cmp.s ecx,edx
    jg .L58e359
    sub.s edx,ecx
    mov DWORD PTR [eax+0x6d88],edx
    xor.s eax,eax
    test edx,edx
    setns al
    dec eax
    pop ebp
    ret
.L58e359:
    or edx,0xffffffff
    xor.s eax,eax
    test edx,edx
    setns al
    dec eax
    pop ebp
    ret
.L58e366:
    # Negative amount advances. INT_MIN remains negative after NEG and fails.
    neg ecx
    mov edx,DWORD PTR [ebp+0x8]
    push esi
    js .L58e3be
    mov eax,DWORD PTR [edx+0x6d84]
    mov esi,DWORD PTR [edx+0x6d88]
    sub.s eax,esi
    cmp.s eax,ecx
    jge .L58e39e
    # Insufficient buffered data restores the saved checkpoint before failing.
    mov eax,DWORD PTR [edx+0x6d8c]
    mov DWORD PTR [edx+0x6d88],eax
    mov eax,0xfffffff6
    mov.s ecx,eax
    xor.s eax,eax
    test ecx,ecx
    pop esi
    setns al
    dec eax
    pop ebp
    ret
.L58e39e:
    # Commit the advance and test the signed absolute position.
    lea eax,[esi+ecx*1]
    mov DWORD PTR [edx+0x6d88],eax
    test eax,eax
    js .L58e3c1
    mov ecx,DWORD PTR [edx+0x6d90]
    add.s ecx,eax
    xor.s eax,eax
    test ecx,ecx
    pop esi
    setns al
    dec eax
    pop ebp
    ret
.L58e3be:
    or eax,0xffffffff
.L58e3c1:
    mov.s ecx,eax
    xor.s eax,eax
    test ecx,ecx
    pop esi
    setns al
    dec eax
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
