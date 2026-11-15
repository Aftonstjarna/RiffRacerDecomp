# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f0520, exclusive end 0x4f0577.
.intel_syntax noprefix
.code32
.text
.global original_script_table_resize_array
.equ script_reallocate,0x4f7d10
.equ script_allocation_too_large,0x4f7cf0
original_script_table_resize_array:
    push ebp
    {load} mov ebp,esp
    push esi
    push edi
    mov edi,DWORD PTR [ebp+8]
    {load} mov esi,edx
    lea eax,[edi+1]
    cmp eax,0x1fffffff
    ja allocation_too_large
    mov edx,DWORD PTR [esi+0xc]
    lea eax,[edi*8+0]
    push eax
    mov eax,DWORD PTR [esi+0x1c]
    shl eax,3
    push eax
    call script_reallocate
    add esp,8
    jmp store_array
allocation_too_large:
    call script_allocation_too_large
store_array:
    mov DWORD PTR [esi+0xc],eax
    mov eax,DWORD PTR [esi+0x1c]
    {load} cmp eax,edi
    jge store_size
    nop
initialize_new_tags:
    mov ecx,DWORD PTR [esi+0xc]
    mov DWORD PTR [ecx+eax*8+4],0
    inc eax
    {load} cmp eax,edi
    jl initialize_new_tags
store_size:
    mov DWORD PTR [esi+0x1c],edi
    pop edi
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
