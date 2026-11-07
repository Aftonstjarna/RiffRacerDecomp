# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original span [0x426f30,0x426f95), 101 bytes.
# ECX destination; nine stack pointers; EAX returns destination; RET 36.
# Preserve the sequential loads/stores, including potential input aliasing.
.intel_syntax noprefix
.code32
.text
.global original_matrix3_construct_refs
original_matrix3_construct_refs:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+8]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx],eax
    mov eax,DWORD PTR [ebp+12]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+4],eax
    mov eax,DWORD PTR [ebp+16]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+8],eax
    mov eax,DWORD PTR [ebp+20]
    mov DWORD PTR [ecx+12],0
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+16],eax
    mov eax,DWORD PTR [ebp+24]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+20],eax
    mov eax,DWORD PTR [ebp+28]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+24],eax
    mov eax,DWORD PTR [ebp+32]
    mov DWORD PTR [ecx+28],0
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+32],eax
    mov eax,DWORD PTR [ebp+36]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+36],eax
    mov eax,DWORD PTR [ebp+40]
    mov eax,DWORD PTR [eax]
    mov DWORD PTR [ecx+40],eax
    mov.s eax,ecx
    mov DWORD PTR [ecx+44],0
    pop ebp
    ret 36
.section .note.GNU-stack,"",@progbits
