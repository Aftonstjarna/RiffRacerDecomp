# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47c220,0x47c263); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ COLLISION_SHAPE_DATA_NAME,0x9fb09c
.global original_collision_shape_serialize
original_collision_shape_serialize:
    push ebp
    mov.s ebp,esp
    push ebx
    push esi
    mov esi,DWORD PTR [ebp+0xc]
    push edi
    mov.s edi,ecx
    mov.s ecx,esi
    push edi
    mov eax,DWORD PTR [esi]
    call DWORD PTR [eax+0x24]
    mov edx,DWORD PTR [esi]
    mov.s ecx,esi
    push eax
    mov DWORD PTR [ebp+0xc],eax
    call DWORD PTR [edx+0x18]
    mov ebx,DWORD PTR [ebp+0x8]
    mov DWORD PTR [ebx],eax
    test eax,eax
    je name_done
    mov eax,DWORD PTR [esi]
    mov.s ecx,esi
    push DWORD PTR [ebp+0xc]
    call DWORD PTR [eax+0x2c]
name_done:
    mov eax,DWORD PTR [edi+0x4]
    pop edi
    mov DWORD PTR [ebx+0x4],eax
    mov eax,COLLISION_SHAPE_DATA_NAME
    pop esi
    pop ebx
    pop ebp
    ret 8
.section .note.GNU-stack,"",@progbits
