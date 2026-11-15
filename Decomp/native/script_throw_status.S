# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4d80,0x4f4dc5); padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_throw_status
.equ LONGJMP_IAT,0x92d360
.equ RESET_STATE,0x4f4d00
original_script_throw_status:
    push ebp
    mov.s ebp,esp
    and esp,-8
    push ecx
    push esi
    mov.s esi,ecx
    mov eax,DWORD PTR [esi+0x60]
    test eax,eax
    je no_jump_buffer
    mov DWORD PTR [eax+0x44],edx
    mov eax,DWORD PTR [esi+0x60]
    push 1
    add eax,4
    push eax
    call DWORD PTR [LONGJMP_IAT]
no_jump_buffer:
    mov eax,DWORD PTR [esi+0x10]
    mov BYTE PTR [esi+6],dl
    cmp DWORD PTR [eax+0x58],0
    je done
    call RESET_STATE
    mov eax,DWORD PTR [esi+0x10]
    push esi
    mov eax,DWORD PTR [eax+0x58]
    call eax
    add esp,4
done:
    pop esi
    mov.s esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
