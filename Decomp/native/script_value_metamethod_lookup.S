# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f5d00,0x4f5d6a); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_value_metamethod_lookup
.equ NIL_VALUE,0x99a41c
original_script_value_metamethod_lookup:
    push ebp
    mov.s ebp,esp
    push esi
    mov esi,DWORD PTR [edx+4]
    mov.s eax,esi
    sub eax,5
    je object_metatable
    sub eax,2
    je object_metatable
    mov eax,DWORD PTR [ecx+0x10]
    mov esi,DWORD PTR [eax+esi*4+0x7c]
    jmp have_metatable
object_metatable:
    mov eax,DWORD PTR [edx]
    mov esi,DWORD PTR [eax+8]
have_metatable:
    test esi,esi
    je absent
    mov ecx,DWORD PTR [ecx+0x10]
    mov eax,DWORD PTR [ebp+8]
    mov edx,DWORD PTR [ecx+eax*4+0xa0]
    mov eax,1
    mov cl,BYTE PTR [esi+7]
    shl eax,cl
    dec eax
    and eax,DWORD PTR [edx+8]
    lea ecx,[eax+eax*4]
    mov eax,DWORD PTR [esi+0x10]
    lea eax,[eax+ecx*4]
    {disp32} lea esp,[esp+0]
chain:
    cmp DWORD PTR [eax+0xc],4
    jne next_node
    cmp DWORD PTR [eax+8],edx
    je found
next_node:
    mov eax,DWORD PTR [eax+0x10]
    test eax,eax
    jne chain
absent:
    mov eax,NIL_VALUE
found:
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
