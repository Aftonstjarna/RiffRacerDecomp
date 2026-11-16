.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x58e7e0,0x58e813); both returns included; INT3 padding excluded.
.equ callback_table,0x9eea10
.equ callback_table_end,0x9eea50
.global original_audio_callback_table_contains
original_audio_callback_table_contains:
    push esi
    mov esi,callback_table
.Lrow:
    xor.s edx,edx
    mov.s eax,esi
    {disp32} lea ebx,[ebx+0x0]
.Lentry:
    cmp ecx,DWORD PTR [eax]
    je .Lfound
    inc edx
    add eax,4
    cmp edx,4
    jl .Lentry
    add esi,0x10
    cmp esi,callback_table_end
    jl .Lrow
    xor.s eax,eax
    pop esi
    ret
.Lfound:
    mov eax,1
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
