.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8fc230, complete 22-byte entry ending in a tail jump.
.equ stack_probe,0x8f9800
.global original_stack_allocate_align16
original_stack_allocate_align16:
    push ecx
    lea ecx,[esp+8]
    {load} sub ecx,eax
    and ecx,15
    {load} add eax,ecx
    {load} sbb ecx,ecx
    {load} or eax,ecx
    pop ecx
    jmp stack_probe
.section .note.GNU-stack,"",@progbits
