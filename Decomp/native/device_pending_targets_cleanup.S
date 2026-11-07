# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4a4ea0.
.intel_syntax noprefix
.code32
.text
.global original_device_pending_targets_cleanup
original_device_pending_targets_cleanup:
    push   esi
    {load} mov esi,ecx  # Preserve the original register-load encoding.
    # Conditional COM-style releases, descending object fields 0x18 through 0x04.
    mov    ecx,DWORD PTR [esi+0x18]
    test   ecx,ecx
    je     L_4a4eb7
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0x18],0x0
L_4a4eb7:
    mov    ecx,DWORD PTR [esi+0x14]
    test   ecx,ecx
    je     L_4a4ecb
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0x14],0x0
L_4a4ecb:
    mov    ecx,DWORD PTR [esi+0x10]
    test   ecx,ecx
    je     L_4a4edf
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0x10],0x0
L_4a4edf:
    mov    ecx,DWORD PTR [esi+0xc]
    test   ecx,ecx
    je     L_4a4ef3
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0xc],0x0
L_4a4ef3:
    mov    ecx,DWORD PTR [esi+0x8]
    test   ecx,ecx
    je     L_4a4f07
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0x8],0x0
L_4a4f07:
    mov    ecx,DWORD PTR [esi+0x4]
    test   ecx,ecx
    je     L_4a4f1b
    mov    eax,DWORD PTR [ecx]
    push   ecx
    call   DWORD PTR [eax+0x8]
    mov    DWORD PTR [esi+0x4],0x0
L_4a4f1b:
    # Clear all 24 bytes of state at object offsets 0x1c..0x33.
    xorps  xmm0,xmm0
    movdqu XMMWORD PTR [esi+0x1c],xmm0
    movq   QWORD PTR [esi+0x2c],xmm0
    pop    esi
    ret
