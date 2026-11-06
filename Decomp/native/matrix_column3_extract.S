# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA span [0x426fa0,0x426fcb); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_matrix_column3_extract
original_matrix_column3_extract:
    push ebp
    {load} mov ebp,esp
    mov eax,DWORD PTR [ebp+8]
    push esi
    {load} mov esi,ecx
    mov ecx,DWORD PTR [ebp+12]
    mov DWORD PTR [eax+12],0
    mov edx,DWORD PTR [esi+ecx*4]
    mov DWORD PTR [eax],edx
    mov edx,DWORD PTR [esi+ecx*4+16]
    mov ecx,DWORD PTR [esi+ecx*4+32]
    mov DWORD PTR [eax+4],edx
    mov DWORD PTR [eax+8],ecx
    pop esi
    pop ebp
    ret 8
.section .note.GNU-stack,"",@progbits
