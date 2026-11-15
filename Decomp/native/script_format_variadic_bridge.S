# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4eff40; exclusive end 0x4eff57.
.intel_syntax noprefix
.code32
.text
.global original_script_format_variadic_bridge
.equ format_engine,0x4efb10
original_script_format_variadic_bridge:
    push ebp
    {load} mov ebp,esp
    mov edx,DWORD PTR [ebp+0xc]
    lea eax,[ebp+0x10]
    mov ecx,DWORD PTR [ebp+0x8]
    push eax
    call format_engine
    add esp,0x4
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
