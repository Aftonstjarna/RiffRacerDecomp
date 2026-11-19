.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4222c0.
.equ sprite_helper,0x422030
.global original_ui_create_button_sprite
original_ui_create_button_sprite:
    push ebp
    {load} mov ebp, esp
    push DWORD PTR [ebp+0xc]
    push DWORD PTR [ebp+0x18]
    push DWORD PTR [ebp+0x14]
    push DWORD PTR [ebp+0x8]
    call sprite_helper
    mov ecx, DWORD PTR [ebp+0x10]
    or BYTE PTR [eax+0x174], 6
    mov DWORD PTR [eax+0x40], ecx
    pop ebp
    ret 0x14
.section .note.GNU-stack,"",@progbits
