# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f0370, exclusive end 0x4f03d8.
.intel_syntax noprefix
.code32
.text
.global original_script_table_choose_array_capacity
original_script_table_choose_array_capacity:
# ECX: signed histogram buckets; EDX: in/out total-count pointer.
# EAX returns the count assigned to the selected power-of-two array capacity.
    push   ebp
    mov.s ebp,esp
    sub    esp,0x8
    push   ebx
    mov.s eax,edx
    mov    DWORD PTR [ebp-0x4],ecx
    push   esi
    xor.s esi,esi
    mov    DWORD PTR [ebp-0x8],eax
    mov.s edx,ecx
    xor.s ebx,ebx
    xor.s ecx,ecx
    push   edi
    lea    edi,[esi+0x1]
    cmp    DWORD PTR [eax],ecx
    jle    store_capacity
scan_bucket:
    # Accumulate positive buckets; retain a capacity when more than half full.
    mov    eax,DWORD PTR [edx]
    test   eax,eax
    jle    check_completion
    add.s esi,eax
    mov.s eax,edi
    cdq
    sub.s eax,edx
    mov    edx,DWORD PTR [ebp-0x4]
    sar    eax,1
    cmp.s esi,eax
    jle    check_completion
    mov.s ebx,edi
    mov.s ecx,esi
check_completion:
    mov    eax,DWORD PTR [ebp-0x8]
    cmp    esi,DWORD PTR [eax]
    je     store_capacity
    add    edx,0x4
    add.s edi,edi
    mov    DWORD PTR [ebp-0x4],edx
    mov.s eax,edi
    cdq
    sub.s eax,edx
    mov    edx,DWORD PTR [ebp-0x8]
    sar    eax,1
    cmp    eax,DWORD PTR [edx]
    mov    edx,DWORD PTR [ebp-0x4]
    jl     scan_bucket
    mov    eax,DWORD PTR [ebp-0x8]
store_capacity:
    # All exits write the chosen capacity (zero if no qualifying bucket).
    pop    edi
    mov    DWORD PTR [eax],ebx
    mov.s eax,ecx
    pop    esi
    pop    ebx
    mov.s esp,ebp
    pop    ebp
    ret
