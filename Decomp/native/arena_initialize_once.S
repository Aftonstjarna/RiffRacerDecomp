# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x452d30, complete span [0x452d30,0x452d7b).
.intel_syntax noprefix
.code32
.text
.equ ARENA_BASE,0xbfcbec
.equ LOCK_A,0xbfcbd0
.equ LOCK_B,0xbfcbf0
.equ ARENA_SIZE,0xbfcc08
.equ INITIALIZE_CRITICAL_SECTION,0x92d02c
.equ VIRTUAL_ALLOC,0x92d0e8
.equ BUILD_ARENA,0x4b4380
.global original_arena_initialize_once
original_arena_initialize_once:
    cmp DWORD PTR [ARENA_BASE],0
    jne initialized
    push LOCK_A
    call DWORD PTR [INITIALIZE_CRITICAL_SECTION]
    push LOCK_B
    call DWORD PTR [INITIALIZE_CRITICAL_SECTION]
    push 4
    push 0x3000
    push 0x20000000
    push 0
    call DWORD PTR [VIRTUAL_ALLOC]
    sub esp,8
    mov DWORD PTR [ARENA_BASE],eax
    mov DWORD PTR [ARENA_SIZE],0x20000000
    call BUILD_ARENA
initialized:
    ret
.section .note.GNU-stack,"",@progbits
