# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0900,0x4f0971); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_construct
.equ script_reallocate,0x4f7d10
.equ resize_array,0x4f0520
.equ initialize_hash_storage,0x4f0580
.equ empty_hash_node,0x99a424
original_script_table_construct:
    push ebp
    mov.s ebp,esp
    push ebx
    push esi
    push edi
    mov.s esi,edx
    mov.s ebx,ecx
    push 0x20
    push 0
    xor.s edx,edx
    call script_reallocate
    mov edx,DWORD PTR [ebx+0x10]
    mov.s edi,eax
    push esi
    mov ecx,DWORD PTR [edx+0x1c]
    mov DWORD PTR [edi],ecx
    mov cl,BYTE PTR [edx+0x14]
    mov DWORD PTR [edx+0x1c],edi
    and cl,3
    mov BYTE PTR [edi+5],cl
    mov.s edx,edi
    mov.s ecx,ebx
    mov BYTE PTR [edi+4],5
    mov DWORD PTR [edi+8],0
    mov WORD PTR [edi+6],0xff
    mov DWORD PTR [edi+0xc],0
    mov DWORD PTR [edi+0x1c],0
    mov DWORD PTR [edi+0x10],empty_hash_node
    call resize_array
    push DWORD PTR [ebp+8]
    mov.s edx,edi
    mov.s ecx,ebx
    call initialize_hash_storage
    add esp,0x10
    mov.s eax,edi
    pop edi
    pop esi
    pop ebx
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
