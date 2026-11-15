# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x486ab0,0x486ae1); surrounding INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_runtime_error_variadic_bridge
.equ FORMAT_ENGINE,0x4efb10
.equ ADD_LOCATION,0x4869a0
.equ RAISE_ERROR,0x486a30
original_script_runtime_error_variadic_bridge:
    push ebp
    mov.s ebp,esp
    and esp,0xfffffff8
    push ecx
    mov edx,DWORD PTR [ebp+0xc]
    lea eax,[ebp+0x10]
    push esi
    mov esi,DWORD PTR [ebp+0x8]
    mov.s ecx,esi
    push eax
    call FORMAT_ENGINE
    add esp,0x4
    mov.s edx,eax
    mov.s ecx,esi
    call ADD_LOCATION
    mov.s ecx,esi
    call RAISE_ERROR
    pop esi
    mov.s esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
