.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x590c40,0x590d87); complete leaf, both loops and final return.
.global original_audio_synthesis_window_initialize
original_audio_synthesis_window_initialize:
# cdecl(state*); caller owns argument, EBP/ESI/EDI preserved. No calls.
.L590c40:
    push   ebp
.L590c41:
    mov.s    ebp,esp
.L590c43:
    and    esp,0xfffffff8
.L590c46:
    mov    eax,DWORD PTR [ebp+0x8]
.L590c49:
    xorps  xmm0,xmm0
.L590c4c:
    push   esi
.L590c4d:
    xor.s    ecx,ecx
.L590c4f:
    push   edi
.L590c50:
    movsd  xmm1,QWORD PTR [eax+0x4d68]
.L590c58:
    comisd xmm0,xmm1
.L590c5c:
    jbe    .Lscale_selected_gain
.L590c5e:
    movsd  xmm1,QWORD PTR [eax+0x6eb8]
.Lscale_selected_gain:
    mulsd  xmm1,QWORD PTR ds:0xa068c8
.L590c6e:
    xor.s    edx,edx
.L590c70:
    xor.s    edi,edi
.L590c72:
    movsd  xmm2,QWORD PTR ds:0xa071d0
.L590c7a:
    lea    esi,[edx+0x40]
.L590c7d:
    jmp    .Lforward_write_check
.L590c7f:
    nop
.Lforward_loop:
# First 256 iterations walk signed coefficient table upward.
    mov    eax,DWORD PTR [ebp+0x8]
.Lforward_write_check:
    cmp    ecx,0x210
.L590c89:
    jge    .Lforward_index_update
.L590c8b:
    movd   xmm0,DWORD PTR [edi*4+0x9eed90]
.L590c94:
    mov    eax,DWORD PTR [eax+0x2444]
.L590c9a:
    cvtdq2pd xmm0,xmm0
.L590c9e:
    mulsd  xmm0,xmm1
.L590ca2:
    cvtpd2ps xmm0,xmm0
.L590ca6:
    movss  DWORD PTR [eax+ecx*4],xmm0
.L590cab:
    mov    eax,DWORD PTR [ebp+0x8]
.L590cae:
    mov    eax,DWORD PTR [eax+0x2444]
.L590cb4:
    movss  DWORD PTR [esi+eax*1],xmm0
.Lforward_index_update:
    mov.s    eax,edx
.L590cbb:
    and    eax,0x1f
.L590cbe:
    cmp    al,0x1f
.L590cc0:
    jne    .Lforward_sign_check
.L590cc2:
    sub    ecx,0x3ff
.L590cc8:
    sub    esi,0xffc
.Lforward_sign_check:
    mov.s    eax,edx
.L590cd0:
    and    eax,0x3f
.L590cd3:
    cmp    al,0x3f
.L590cd5:
    jne    .Lforward_advance
.L590cd7:
    xorpd  xmm1,xmm2
.Lforward_advance:
    inc    edx
.L590cdc:
    inc    edi
.L590cdd:
    add    ecx,0x20
.L590ce0:
    sub    esi,0xffffff80
.L590ce3:
    cmp    edx,0x100
.L590ce9:
    jl     .Lforward_loop
.L590ceb:
    cmp    edx,0x200
.L590cf1:
    jge    .Ldone
.L590cf7:
    lea    esi,[ecx*4+0x40]
.L590cfe:
    lea    edi,[edi*4+0x9eed90]
.Lreverse_loop:
# Remaining 256 iterations walk the table downward; preserve original modulo branches.
    cmp    ecx,0x210
.L590d0b:
    jge    .Lreverse_index_update
.L590d0d:
    movd   xmm0,DWORD PTR [edi]
.L590d11:
    mov    eax,DWORD PTR [ebp+0x8]
.L590d14:
    cvtdq2pd xmm0,xmm0
.L590d18:
    mov    eax,DWORD PTR [eax+0x2444]
.L590d1e:
    mulsd  xmm0,xmm1
.L590d22:
    cvtpd2ps xmm0,xmm0
.L590d26:
    movss  DWORD PTR [eax+ecx*4],xmm0
.L590d2b:
    mov    eax,DWORD PTR [ebp+0x8]
.L590d2e:
    mov    eax,DWORD PTR [eax+0x2444]
.L590d34:
    movss  DWORD PTR [esi+eax*1],xmm0
.Lreverse_index_update:
    mov.s    eax,edx
.L590d3b:
    and    eax,0x8000001f
.L590d40:
    jns    .Lreverse_mod32_done
.L590d42:
    dec    eax
.L590d43:
    or     eax,0xffffffe0
.L590d46:
    inc    eax
.Lreverse_mod32_done:
    cmp    eax,0x1f
.L590d4a:
    jne    .Lreverse_sign_check
.L590d4c:
    sub    ecx,0x3ff
.L590d52:
    sub    esi,0xffc
.Lreverse_sign_check:
    mov.s    eax,edx
.L590d5a:
    and    eax,0x8000003f
.L590d5f:
    jns    .Lreverse_mod64_done
.L590d61:
    dec    eax
.L590d62:
    or     eax,0xffffffc0
.L590d65:
    inc    eax
.Lreverse_mod64_done:
    cmp    eax,0x3f
.L590d69:
    jne    .Lreverse_advance
.L590d6b:
    xorpd  xmm1,xmm2
.Lreverse_advance:
    inc    edx
.L590d70:
    sub    edi,0x4
.L590d73:
    add    ecx,0x20
.L590d76:
    sub    esi,0xffffff80
.L590d79:
    cmp    edx,0x200
.L590d7f:
    jl     .Lreverse_loop
.Ldone:
    pop    edi
.L590d82:
    pop    esi
.L590d83:
    mov.s    esp,ebp
.L590d85:
    pop    ebp
.L590d86:
    ret
.section .note.GNU-stack,"",@progbits
