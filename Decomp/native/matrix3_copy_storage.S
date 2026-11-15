# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x467e10,0x467e4d); adjacent INT3 padding excluded.
# ECX destination, [entry ESP+4] source; callee pops 4 bytes.
# Three rows of four sequential DWORD transfers; row padding is copied.
# One backward branch, exactly three iterations. No calls or global data.
.intel_syntax noprefix
.code32
.text
.global original_matrix3_copy_storage
original_matrix3_copy_storage:
    push ebp
    mov.s ebp,esp
    push esi
    push edi
    mov edi,DWORD PTR [ebp+8]
    lea edx,[ecx+4]
    lea esi,[edi+12]
    sub.s edi,ecx
    mov ecx,3
L_row:
    mov eax,DWORD PTR [esi-12]
    lea edx,[edx+16]
    mov DWORD PTR [edx-20],eax
    lea esi,[esi+16]
    mov eax,DWORD PTR [edi+edx-16]
    mov DWORD PTR [edx-16],eax
    mov eax,DWORD PTR [esi-20]
    mov DWORD PTR [edx-12],eax
    mov eax,DWORD PTR [esi-16]
    mov DWORD PTR [edx-8],eax
    dec ecx
    jne L_row
    pop edi
    pop esi
    pop ebp
    ret 4
.section .note.GNU-stack,"",@progbits
