.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x423240; complete 30-byte leaf, ending at 0x42325e.
.global original_tree_rightmost
original_tree_rightmost:
    mov eax, DWORD PTR [ecx+8]
    cmp BYTE PTR [eax+13], 0
    jne done
    {disp32} lea esp, [esp+0x00000000]
loop_right:
    {load} mov ecx, eax
    mov eax, DWORD PTR [ecx+8]
    cmp BYTE PTR [eax+13], 0
    je loop_right
done:
    {load} mov eax, ecx
    ret
.section .note.GNU-stack,"",@progbits
