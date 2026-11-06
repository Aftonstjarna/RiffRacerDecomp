# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f90ed, exclusive end 0x8f9131.
.intel_syntax noprefix
.code32
.text
.equ CRT_EXCEPT1,0x8f9d1e
.equ MASK_TABLE_BASE,0x98253f
.equ EXCEPTION_CONTROL,0x982560
.global original_sse_conversion_exception
original_sse_conversion_exception:
    sub esp,0x20
    fstcw WORD PTR [esp]
    movzx eax,WORD PTR [esp]
    cmp edx,0x8
    je dispatch_exception
    test BYTE PTR [edx+MASK_TABLE_BASE],al
    jne finished
 dispatch_exception:
    fldcw WORD PTR [EXCEPTION_CONTROL]
    mov DWORD PTR [esp],edx
    mov DWORD PTR [esp+0x4],0x0
    movsd QWORD PTR [esp+0x8],xmm0
    movsd QWORD PTR [esp+0x10],xmm0
    mov DWORD PTR [esp+0x18],eax
    call CRT_EXCEPT1
    fstp st(0)
 finished:
    add esp,0x20
    ret
.section .note.GNU-stack,"",@progbits
