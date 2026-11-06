# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x510ec0,0x510ed3). Registered callback from 0x510ee0.
.intel_syntax noprefix
.code32
.text
.global original_shader_boolean_callback
original_shader_boolean_callback:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+8]
    cmp BYTE PTR [eax],0
    setne al
    mov BYTE PTR [ecx+0x14],al
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
