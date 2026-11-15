# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4270a0, complete 16-byte function; next entry 0x4270b0.
# ECX=this; stack argument=index; EAX=pointer; callee pops 4 bytes.
.intel_syntax noprefix
.code32
.text
.global original_dispatcher_manifold_index
original_dispatcher_manifold_index:
    push ebp
    {load} mov ebp, esp
    mov ecx, DWORD PTR [ecx+0x14]
    mov eax, DWORD PTR [ebp+0x8]
    mov eax, DWORD PTR [ecx+eax*4]
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
