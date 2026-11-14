# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x47bf40,0x47c052); excludes surrounding INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ COOKIE_CHECK,0x8f8958
.global original_polyhedral_cached_aabb_recalculate
original_polyhedral_cached_aabb_recalculate:
    push   ebp
    mov.s    ebp,esp
    sub    esp,0x64
    mov    eax,DWORD PTR [0xbaabc0]
    xor.s    eax,ebp
    mov    DWORD PTR [ebp-0x4],eax
    mov    eax,DWORD PTR [0xc0db64]
    push   esi
    mov.s    esi,ecx
    mov    BYTE PTR [esi+0x54],0x1
    test   al,0x1
    jne    directions_ready
    movaps xmm0,XMMWORD PTR [0xa06940]
    or     eax,0x1
    movaps XMMWORD PTR [0xc0db70],xmm0
    movaps xmm0,XMMWORD PTR [0xa06990]
    movaps XMMWORD PTR [0xc0db80],xmm0
    movaps xmm0,XMMWORD PTR [0xa06ba0]
    movaps XMMWORD PTR [0xc0db90],xmm0
    movaps xmm0,XMMWORD PTR [0xa06960]
    movaps XMMWORD PTR [0xc0dba0],xmm0
    movaps xmm0,XMMWORD PTR [0xa069f0]
    movaps XMMWORD PTR [0xc0dbb0],xmm0
    movaps xmm0,XMMWORD PTR [0xa06d50]
    mov DWORD PTR [0xc0db64],eax
    movaps XMMWORD PTR [0xc0dbc0],xmm0
directions_ready:
    mov    eax,DWORD PTR [esi]
    lea    ecx,[ebp-0x64]
    xorps  xmm0,xmm0
    push   0x6
    push   ecx
    push   0xc0db70
    mov.s    ecx,esi
    movups XMMWORD PTR [ebp-0x64],xmm0
    movups XMMWORD PTR [ebp-0x54],xmm0
    movups XMMWORD PTR [ebp-0x44],xmm0
    movups XMMWORD PTR [ebp-0x34],xmm0
    movups XMMWORD PTR [ebp-0x24],xmm0
    movups XMMWORD PTR [ebp-0x14],xmm0
    call   DWORD PTR [eax+0x40]
    movss  xmm0,DWORD PTR [esi+0x2c]
    addss  xmm0,DWORD PTR [ebp-0x64]
    mov    ecx,DWORD PTR [ebp-0x4]
    xor.s    ecx,ebp
    movss  DWORD PTR [esi+0x44],xmm0
    movss  xmm0,DWORD PTR [ebp-0x34]
    subss  xmm0,DWORD PTR [esi+0x2c]
    movss  DWORD PTR [esi+0x34],xmm0
    movss  xmm0,DWORD PTR [esi+0x2c]
    addss  xmm0,DWORD PTR [ebp-0x50]
    movss  DWORD PTR [esi+0x48],xmm0
    movss  xmm0,DWORD PTR [ebp-0x20]
    subss  xmm0,DWORD PTR [esi+0x2c]
    movss  DWORD PTR [esi+0x38],xmm0
    movss  xmm0,DWORD PTR [esi+0x2c]
    addss  xmm0,DWORD PTR [ebp-0x3c]
    movss  DWORD PTR [esi+0x4c],xmm0
    movss  xmm0,DWORD PTR [ebp-0xc]
    subss  xmm0,DWORD PTR [esi+0x2c]
    movss  DWORD PTR [esi+0x3c],xmm0
    pop    esi
    call   COOKIE_CHECK
    mov.s    esp,ebp
    pop    ebp
    ret
.section .note.GNU-stack,"",@progbits
