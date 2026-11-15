# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f0460, exclusive end 0x4f051e.
.intel_syntax noprefix
.code32
.text
.global original_script_table_count_hash_histogram
original_script_table_count_hash_histogram:
    push   ebp
    {load} mov    ebp,esp
    sub    esp,0x8
    {load} mov    eax,ecx
    mov    DWORD PTR [ebp-0x4],edx
    push   ebx
    push   esi
    mov    esi,0x1
    mov    DWORD PTR [ebp-0x8],eax
    mov    cl,BYTE PTR [eax+0x7]
    {load} xor    ebx,ebx
    push   edi
    shl    esi,cl
    {load} xor    edi,edi
    test   esi,esi
    je     zero_iteration_exit
    lea    edx,[esi+esi*4]
    shl    edx,0x2
    {disp8} lea    ecx,[ecx+0x0]
scan_node:
# Traverse 20-byte hash nodes in reverse; +4 is the value tag.
    {load} mov    eax,DWORD PTR [eax+0x10]
    sub    edx,0x14
    {load} add    eax,edx
    dec    esi
    cmp    DWORD PTR [eax+0x4],0x0
    je     next_node
    cmp    DWORD PTR [eax+0xc],0x3
    jne    not_array_key
# Numeric key: preserve original SSE conversion, unordered/equality test.
    cvttss2si ecx,DWORD PTR [eax+0x8]
    movd   xmm0,ecx
    cvtdq2ps xmm0,xmm0
    ucomiss xmm0,DWORD PTR [eax+0x8]
    lahf
    test   ah,0x44
    jp     not_array_key
    lea    eax,[ecx-0x1]
    cmp    eax,0x3ffffff
    ja     not_array_key
    lea    eax,[ecx-0x1]
    or     ecx,0xffffffff
    cmp    eax,0x100
    jb     lookup_bit_length
reduce_key:
    shr    eax,0x8
    add    ecx,0x8
    cmp    eax,0x100
    jae    reduce_key
lookup_bit_length:
# Original .rdata dependency: 256 byte bit-length lookup table.
    movzx  eax,BYTE PTR [eax+0x99a438]
    {load} add    eax,ecx
    {load} mov    ecx,DWORD PTR [ebp-0x4]
    inc    DWORD PTR [ecx+eax*4+0x4]
    mov    eax,0x1
    jmp    accumulate_key
not_array_key:
    {load} xor    eax,eax
accumulate_key:
    {load} add    ebx,eax
    inc    edi
next_node:
    {load} mov    eax,DWORD PTR [ebp-0x8]
    test   esi,esi
    jne    scan_node
# Caller removes the one stack argument; add eligible keys to *count.
    {load} mov    ecx,DWORD PTR [ebp+0x8]
    {load} mov    eax,edi
    pop    edi
    pop    esi
    add    DWORD PTR [ecx],ebx
    pop    ebx
    {load} mov    esp,ebp
    pop    ebp
    ret
zero_iteration_exit:
    {load} mov    eax,DWORD PTR [ebp+0x8]
    add    DWORD PTR [eax],ebx
    {load} mov    eax,edi
    pop    edi
    pop    esi
    pop    ebx
    {load} mov    esp,ebp
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
