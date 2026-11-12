# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47c190,0x47c1a1); one indirect call, no conditional branches.
.intel_syntax noprefix
.code32
.text
.global original_collision_shape_contact_threshold
original_collision_shape_contact_threshold:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ecx]
    mov eax,DWORD PTR [eax+0xc]
    call eax
    fmul DWORD PTR [ebp+0x8]
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
