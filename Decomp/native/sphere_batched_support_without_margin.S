# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x47d560,0x47d596); surrounding INT3 padding excluded.
# Sphere vtable 0x9f987c slot +0x40. No imports or global data.
.intel_syntax noprefix
.code32
.text
.global original_sphere_batched_support_without_margin
original_sphere_batched_support_without_margin:
    push ebp
    mov.s ebp,esp
    mov ecx,DWORD PTR [ebp+0x10]
    test ecx,ecx
    jle L_done
    mov eax,DWORD PTR [ebp+0xc]
    add eax,0x8
L_loop:
    mov DWORD PTR [eax-0x8],0
    lea eax,[eax+0x10]
    mov DWORD PTR [eax-0x14],0
    mov DWORD PTR [eax-0x10],0
    mov DWORD PTR [eax-0xc],0
    dec ecx
    jne L_loop
L_done:
    pop ebp
    ret 0xc
.section .note.GNU-stack,"",@progbits
