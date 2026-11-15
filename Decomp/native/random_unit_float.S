.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4787b0,0x478808); INT3 padding excluded.
# ECX points to writable uint32 RNG state; no stack arguments; float in ST(0).
.equ UNSIGNED_CORRECTION,0xa071b0
.equ FLOAT_DIVISOR,0xa0684c
.equ FLOAT_OFFSET,0xa063ec
.global original_random_unit_float
original_random_unit_float:
    push ebp
    mov.s ebp,esp
    push ecx
    imul edx,DWORD PTR [ecx],0x27
    add edx,0x27a39e8f
    mov DWORD PTR [ecx],edx
    shl DWORD PTR [ecx],0xd
    mov eax,DWORD PTR [ecx]
    sar edx,0x13
    and edx,0x1fff
    or.s eax,edx
    mov DWORD PTR [ecx],eax
    movzx eax,ax
    movd xmm0,eax
    cvtdq2pd xmm0,xmm0
    shr eax,0x1f
    addsd xmm0,QWORD PTR [eax*8+UNSIGNED_CORRECTION]
    cvtpd2ps xmm0,xmm0
    divss xmm0,DWORD PTR [FLOAT_DIVISOR]
    addss xmm0,DWORD PTR [FLOAT_OFFSET]
    movss DWORD PTR [ebp-4],xmm0
    fld DWORD PTR [ebp-4]
    mov.s esp,ebp
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
