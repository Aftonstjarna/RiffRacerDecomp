# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA [0x438df0,0x438ee3).
# Six-way jump table at 0x438ee4 and sign mask at 0xa071e0 remain external original data.
.intel_syntax noprefix
.code32
.text
.global original_box_plane_equation
original_box_plane_equation:
L438df0:
    push   ebp
L438df1:
    mov.s    ebp,esp
L438df3:
    and    esp,0xfffffff0
L438df6:
    sub    esp,0x10
L438df9:
    movdqu xmm0,XMMWORD PTR [ecx+0x1c]
L438dfe:
    mov    eax,DWORD PTR [ebp+0xc]
L438e01:
    movdqu XMMWORD PTR [esp],xmm0
L438e06:
    cmp    eax,0x5
L438e09:
    ja L438edd
L438e0f:
    jmp    DWORD PTR [eax*4+0x438ee4]
L438e16:
    mov    eax,DWORD PTR [ebp+0x8]
L438e19:
    movss  xmm0,DWORD PTR [esp]
L438e1e:
    mov    DWORD PTR [eax],0x3f800000
L438e24:
    mov    DWORD PTR [eax+0x8],0x0
L438e2b:
    jmp L438eca
L438e30:
    mov    eax,DWORD PTR [ebp+0x8]
L438e33:
    movss  xmm0,DWORD PTR [esp]
L438e38:
    mov    DWORD PTR [eax],0xbf800000
L438e3e:
    mov    DWORD PTR [eax+0x8],0x0
L438e45:
    jmp L438eca
L438e4a:
    mov    eax,DWORD PTR [ebp+0x8]
L438e4d:
    movss  xmm0,DWORD PTR [esp+0x4]
L438e53:
    xorps  xmm0,XMMWORD PTR [0xa071e0]
L438e5a:
    mov    DWORD PTR [eax],0x0
L438e60:
    mov    DWORD PTR [eax+0x4],0x3f800000
L438e67:
    mov    DWORD PTR [eax+0x8],0x0
L438e6e:
    movss  DWORD PTR [eax+0xc],xmm0
L438e73:
    mov.s    esp,ebp
L438e75:
    pop    ebp
L438e76:
    ret    0x8
L438e79:
    mov    eax,DWORD PTR [ebp+0x8]
L438e7c:
    movss  xmm0,DWORD PTR [esp+0x4]
L438e82:
    xorps  xmm0,XMMWORD PTR [0xa071e0]
L438e89:
    mov    DWORD PTR [eax],0x0
L438e8f:
    mov    DWORD PTR [eax+0x4],0xbf800000
L438e96:
    mov    DWORD PTR [eax+0x8],0x0
L438e9d:
    movss  DWORD PTR [eax+0xc],xmm0
L438ea2:
    mov.s    esp,ebp
L438ea4:
    pop    ebp
L438ea5:
    ret    0x8
L438ea8:
    mov    eax,DWORD PTR [ebp+0x8]
L438eab:
    mov    DWORD PTR [eax+0x8],0x3f800000
L438eb2:
    jmp L438ebe
L438eb4:
    mov    eax,DWORD PTR [ebp+0x8]
L438eb7:
    mov    DWORD PTR [eax+0x8],0xbf800000
L438ebe:
    movss  xmm0,DWORD PTR [esp+0x8]
L438ec4:
    mov    DWORD PTR [eax],0x0
L438eca:
    xorps  xmm0,XMMWORD PTR [0xa071e0]
L438ed1:
    mov    DWORD PTR [eax+0x4],0x0
L438ed8:
    movss  DWORD PTR [eax+0xc],xmm0
L438edd:
    mov.s    esp,ebp
L438edf:
    pop    ebp
L438ee0:
    ret    0x8
.section .note.GNU-stack,"",@progbits
