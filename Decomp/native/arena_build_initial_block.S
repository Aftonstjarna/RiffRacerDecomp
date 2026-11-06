# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA span [0x4b4380,0x4b4408).
.intel_syntax noprefix
.code32
.text
.equ ARENA_BASE,0xbfcbec
.equ LIST_HEADS,0xc00b7c
.equ SIZE_A,0xc00d04
.equ SIZE_B,0xc00d08
.equ RAW_BASE,0xc00b70
.equ BASE_COPY,0xc00d0c
.equ SIZE_C,0xc00d10
.equ ALIGNED_BASE,0xc00b78
.equ FREE_SIZE,0xc00b6c
.equ FREE_BLOCK,0xc00d18
.global original_arena_build_initial_block
original_arena_build_initial_block:
    push esi
    mov esi,DWORD PTR [ARENA_BASE]
    mov ecx,LIST_HEADS
    mov DWORD PTR [SIZE_A],0x20000000
    mov edx,0x20
    mov DWORD PTR [SIZE_B],0x20000000
    mov DWORD PTR [RAW_BASE],esi
    mov DWORD PTR [BASE_COPY],esi
    mov DWORD PTR [SIZE_C],0x20000000
    jmp initialize_head
    {disp8} lea ecx,[ecx+0]
initialize_head:
    mov DWORD PTR [ecx+0xc],ecx
    mov DWORD PTR [ecx+8],ecx
    add ecx,8
    dec edx
    jne initialize_head
    {load} mov eax,esi
    and eax,7
    je aligned
    neg eax
    and eax,7
aligned:
    lea edx,[eax+esi]
    mov ecx,0x1fffffe0
    {load} sub ecx,eax
    mov DWORD PTR [ALIGNED_BASE],edx
    {load} mov eax,ecx
    mov DWORD PTR [FREE_SIZE],ecx
    or eax,1
    mov DWORD PTR [edx+4],eax
    mov DWORD PTR [FREE_BLOCK],edx
    mov DWORD PTR [edx+ecx+4],0x20
    pop esi
    ret 8
.section .note.GNU-stack,"",@progbits
