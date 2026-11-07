# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA span [0x510ee0,0x510f28).
.intel_syntax noprefix
.code32
.text
.equ CALLBACK,0x510ec0
.equ DESCRIPTOR,0xbbd4c0
.equ FLAGS,0xbbd4c4
.equ SELF_FIELD,0xbbd4cc
.equ CALLBACK_FIELD,0xbbd4d0
.equ REGISTER_SLOT,0xbc9138
.equ REMOVE_SLOT,0xbc9140
.global original_shader_boolean_register
original_shader_boolean_register:
    mov eax,CALLBACK
    test eax,eax
    je done
    test BYTE PTR [FLAGS],1
    je register_callback
    push DESCRIPTOR
    call DWORD PTR [REMOVE_SLOT]
    add esp,4
register_callback:
    push 0x14b
    push DESCRIPTOR
    mov DWORD PTR [SELF_FIELD],DESCRIPTOR
    mov DWORD PTR [CALLBACK_FIELD],CALLBACK
    call DWORD PTR [REGISTER_SLOT]
    add esp,8
done:
    ret
.section .note.GNU-stack,"",@progbits
