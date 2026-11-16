.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x55d1c0, exclusive end 0x55d202; INT3 padding excluded.
.global original_buffer_pack_high_three_bytes
original_buffer_pack_high_three_bytes:
    push esi
    push edi
    mov.s edi,ecx
    mov esi,DWORD PTR [edi]
    mov.s eax,esi
    mov.s edx,eax
    sub.s edx,esi
    add edx,4
    cmp edx,DWORD PTR [edi+8]
    ja .Lfinish
.Lpack:
    movzx ecx,BYTE PTR [eax+1]
    mov BYTE PTR [esi],cl
    movzx ecx,BYTE PTR [eax+2]
    mov BYTE PTR [esi+1],cl
    movzx ecx,BYTE PTR [eax+3]
    add eax,4
    mov BYTE PTR [esi+2],cl
    mov.s ecx,eax
    sub ecx,DWORD PTR [edi]
    add esi,3
    add ecx,4
    cmp ecx,DWORD PTR [edi+8]
    jbe .Lpack
.Lfinish:
    sub esi,DWORD PTR [edi]
    mov DWORD PTR [edi+8],esi
    pop edi
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
