# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47c2b0,0x47c2d3); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ COLLISION_SHAPE_VTABLE,0x9fb0b8
.equ OPERATOR_DELETE_IAT,0x92d4b0
.global original_collision_shape_deleting_destructor
original_collision_shape_deleting_destructor:
    push ebp
    mov.s ebp,esp
    test BYTE PTR [ebp+8],1
    push esi
    mov.s esi,ecx
    mov DWORD PTR [esi],COLLISION_SHAPE_VTABLE
    je keep_storage
    push esi
    call DWORD PTR [OPERATOR_DELETE_IAT]
    add esp,4
keep_storage:
    mov.s eax,esi
    pop esi
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
