# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4ef9f0,0x4efaa4); all three returns included; padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_string_parse_number
original_script_string_parse_number:
L_4ef9f0:
    push   ebp
L_4ef9f1:
    mov.s    ebp,esp
L_4ef9f3:
    sub    esp,0x8
L_4ef9f6:
    push   esi
L_4ef9f7:
    push   edi
L_4ef9f8:
    lea    eax,[ebp-0x4]
L_4ef9fb:
    mov.s    esi,ecx
L_4ef9fd:
    push   eax
L_4ef9fe:
    push   esi
L_4ef9ff:
    mov.s    edi,edx
L_4efa01:
    call   DWORD PTR ds:0x92d430
L_4efa07:
    mov    eax,DWORD PTR [ebp-0x4]
L_4efa0a:
    add    esp,0x8
L_4efa0d:
    fstp   DWORD PTR [ebp-0x8]
L_4efa10:
    fld    DWORD PTR [ebp-0x8]
L_4efa13:
    fstp   DWORD PTR [edi]
L_4efa15:
    cmp.s    eax,esi
L_4efa17:
    jne L_4efa21
L_4efa19:
    pop    edi
L_4efa1a:
    xor.s    eax,eax
L_4efa1c:
    pop    esi
L_4efa1d:
    mov.s    esp,ebp
L_4efa1f:
    pop    ebp
L_4efa20:
    ret
L_4efa21:
    mov    cl,BYTE PTR [eax]
L_4efa23:
    cmp    cl,0x78
L_4efa26:
    je L_4efa2d
L_4efa28:
    cmp    cl,0x58
L_4efa2b:
    jne L_4efa5c
L_4efa2d:
    push   0x10
L_4efa2f:
    lea    eax,[ebp-0x4]
L_4efa32:
    push   eax
L_4efa33:
    push   esi
L_4efa34:
    call   DWORD PTR ds:0x92d380
L_4efa3a:
    add    esp,0xc
L_4efa3d:
    movd   xmm0,eax
L_4efa41:
    cvtdq2pd xmm0,xmm0
L_4efa45:
    shr    eax,0x1f
L_4efa48:
    addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
L_4efa51:
    mov    eax,DWORD PTR [ebp-0x4]
L_4efa54:
    cvtpd2ps xmm0,xmm0
L_4efa58:
    movss  DWORD PTR [edi],xmm0
L_4efa5c:
    mov    al,BYTE PTR [eax]
L_4efa5e:
    test   al,al
L_4efa60:
    jne L_4efa6d
L_4efa62:
    pop    edi
L_4efa63:
    mov    eax,0x1
L_4efa68:
    pop    esi
L_4efa69:
    mov.s    esp,ebp
L_4efa6b:
    pop    ebp
L_4efa6c:
    ret
L_4efa6d:
    mov    esi,DWORD PTR ds:0x92d388
L_4efa73:
    movzx  eax,al
L_4efa76:
    push   eax
L_4efa77:
    call   esi
L_4efa79:
    add    esp,0x4
L_4efa7c:
    test   eax,eax
L_4efa7e:
    je L_4efa94
L_4efa80:
    mov    eax,DWORD PTR [ebp-0x4]
L_4efa83:
    inc    eax
L_4efa84:
    mov    DWORD PTR [ebp-0x4],eax
L_4efa87:
    movzx  eax,BYTE PTR [eax]
L_4efa8a:
    push   eax
L_4efa8b:
    call   esi
L_4efa8d:
    add    esp,0x4
L_4efa90:
    test   eax,eax
L_4efa92:
    jne L_4efa80
L_4efa94:
    mov    ecx,DWORD PTR [ebp-0x4]
L_4efa97:
    xor.s    eax,eax
L_4efa99:
    pop    edi
L_4efa9a:
    pop    esi
L_4efa9b:
    cmp    BYTE PTR [ecx],al
L_4efa9d:
    sete   al
L_4efaa0:
    mov.s    esp,ebp
L_4efaa2:
    pop    ebp
L_4efaa3:
    ret
.section .note.GNU-stack,"",@progbits
