# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9a80,0x8f9b3a); filter and handler after first ret included.
.intel_syntax noprefix
.code32
.text
.global original_crt_callback_storage_validate
.equ image_validate,0x8f9b40
.equ section_lookup,0x8f9a30
original_crt_callback_storage_validate:
L_8f9a80:
    push   ebp
L_8f9a81:
    mov.s    ebp,esp
L_8f9a83:
    push   0xfffffffe
L_8f9a85:
    push   0xb9e680
L_8f9a8a:
    push   0x8f9ce9
L_8f9a8f:
    mov    eax,DWORD PTR fs:[0x0]
L_8f9a95:
    push   eax
L_8f9a96:
    sub    esp,0x8
L_8f9a99:
    push   ebx
L_8f9a9a:
    push   esi
L_8f9a9b:
    push   edi
L_8f9a9c:
    mov    eax,DWORD PTR [0xbaabc0]
L_8f9aa1:
    xor    DWORD PTR [ebp-0x8],eax
L_8f9aa4:
    xor.s    eax,ebp
L_8f9aa6:
    push   eax
L_8f9aa7:
    lea    eax,[ebp-0x10]
L_8f9aaa:
    mov    DWORD PTR fs:[0x0],eax
L_8f9ab0:
    mov    DWORD PTR [ebp-0x18],esp
L_8f9ab3:
    mov    DWORD PTR [ebp-0x4],0x0
L_8f9aba:
    push   0x400000
L_8f9abf:
    call image_validate
L_8f9ac4:
    add    esp,0x4
L_8f9ac7:
    test   eax,eax
L_8f9ac9:
    je L_8f9b1f
L_8f9acb:
    mov    eax,DWORD PTR [ebp+0x8]
L_8f9ace:
    sub    eax,0x400000
L_8f9ad3:
    push   eax
L_8f9ad4:
    push   0x400000
L_8f9ad9:
    call section_lookup
L_8f9ade:
    add    esp,0x8
L_8f9ae1:
    test   eax,eax
L_8f9ae3:
    je L_8f9b1f
L_8f9ae5:
    mov    eax,DWORD PTR [eax+0x24]
L_8f9ae8:
    shr    eax,0x1f
L_8f9aeb:
    not    eax
L_8f9aed:
    and    eax,0x1
L_8f9af0:
    mov    DWORD PTR [ebp-0x4],0xfffffffe
L_8f9af7:
    mov    ecx,DWORD PTR [ebp-0x10]
L_8f9afa:
    mov    DWORD PTR fs:[0x0],ecx
L_8f9b01:
    pop    ecx
L_8f9b02:
    pop    edi
L_8f9b03:
    pop    esi
L_8f9b04:
    pop    ebx
L_8f9b05:
    mov.s    esp,ebp
L_8f9b07:
    pop    ebp
L_8f9b08:
    ret
L_8f9b09:
    mov    eax,DWORD PTR [ebp-0x14]
L_8f9b0c:
    mov    eax,DWORD PTR [eax]
L_8f9b0e:
    xor.s    ecx,ecx
L_8f9b10:
    cmp    DWORD PTR [eax],0xc0000005
L_8f9b16:
    sete   cl
L_8f9b19:
    mov.s    eax,ecx
L_8f9b1b:
    ret
L_8f9b1c:
    mov    esp,DWORD PTR [ebp-0x18]
L_8f9b1f:
    mov    DWORD PTR [ebp-0x4],0xfffffffe
L_8f9b26:
    xor.s    eax,eax
L_8f9b28:
    mov    ecx,DWORD PTR [ebp-0x10]
L_8f9b2b:
    mov    DWORD PTR fs:[0x0],ecx
L_8f9b32:
    pop    ecx
L_8f9b33:
    pop    edi
L_8f9b34:
    pop    esi
L_8f9b35:
    pop    ebx
L_8f9b36:
    mov.s    esp,ebp
L_8f9b38:
    pop    ebp
L_8f9b39:
    ret
.section .note.GNU-stack,"",@progbits
