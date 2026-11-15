# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x486650,0x486675). Lua diagnostic constant-string lookup.
.intel_syntax noprefix
.code32
.text
.global original_lua_constant_string_name
.equ unknown_name,0x9f99d0
original_lua_constant_string_name:
    test edx,0x100
    je .Lunknown
    mov eax,DWORD PTR [ecx+0x8]
    and edx,0xfffffeff
    cmp DWORD PTR [eax+edx*8+0x4],0x4
    jne .Lunknown
    mov eax,DWORD PTR [eax+edx*8]
    add eax,0x10
    ret
.Lunknown:
    mov eax,unknown_name
    ret
.section .note.GNU-stack,"",@progbits
