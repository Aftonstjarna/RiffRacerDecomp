# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x4f0110, code span 123 bytes. External jump table at 0x4f018c is not included.
.intel_syntax noprefix
.code32
.text
.equ numeric_bucket,0x4f00c0
.equ dispatch_table,0x4f018c
.global original_script_table_main_bucket
original_script_table_main_bucket:
    push   ebx
    mov.s    ebx,edx
    push   esi
    push   edi
    mov.s    edi,ecx
    mov    eax,DWORD PTR [ebx+0x4]
    dec    eax
    cmp    eax,0x3
    ja L_4f016a
    jmp    DWORD PTR [eax*4+dispatch_table]
L_4f0127:
    movss  xmm1,DWORD PTR [ebx]
    pop    edi
    pop    esi
    pop    ebx
    jmp numeric_bucket
L_4f0133:
    mov    cl,BYTE PTR [edi+0x7]
    mov    edx,0x1
    mov    eax,DWORD PTR [ebx]
    shl    edx,cl
    dec    edx
    and    edx,DWORD PTR [eax+0x8]
    mov    eax,DWORD PTR [edi+0x10]
    pop    edi
    pop    esi
    lea    ecx,[edx+edx*4]
    lea    eax,[eax+ecx*4]
    pop    ebx
    ret
L_4f0150:
    mov    cl,BYTE PTR [edi+0x7]
    mov    eax,0x1
    shl    eax,cl
    dec    eax
    and    eax,DWORD PTR [ebx]
    lea    ecx,[eax+eax*4]
    mov    eax,DWORD PTR [edi+0x10]
    pop    edi
    pop    esi
    pop    ebx
    lea    eax,[eax+ecx*4]
    ret
L_4f016a:
    mov    cl,BYTE PTR [edi+0x7]
    mov    esi,0x1
    mov    eax,DWORD PTR [ebx]
    xor.s    edx,edx
    shl    esi,cl
    dec    esi
    or     esi,0x1
    div    esi
    mov    eax,DWORD PTR [edi+0x10]
    pop    edi
    pop    esi
    pop    ebx
    lea    ecx,[edx+edx*4]
    lea    eax,[eax+ecx*4]
    ret
