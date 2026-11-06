# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x8fc420, 133 bytes.
.intel_syntax noprefix
.code32
.text
.global original_double_integer_parity
original_double_integer_parity:
L8fc420:
    push   edi
L8fc421:
    mov    edi,DWORD PTR [esp+0xc]
L8fc425:
    and    edi,0x7fffffff
L8fc42b:
    {load} mov    edx,edi
L8fc42d:
    mov    eax,DWORD PTR [esp+0x8]
L8fc431:
    {load} or     edx,eax
L8fc433:
    je     L8fc49e
L8fc435:
    lea    edx,[edi-0x3ff00000]
L8fc43b:
    cmp    edx,0x40000000
L8fc441:
    jae    L8fc481
L8fc443:
    cmp    edi,0x43400000
L8fc449:
    jge    L8fc49e
L8fc44b:
    {load} mov    ecx,edi
L8fc44d:
    and    ecx,0x7ff00000
L8fc453:
    add    ecx,0xc0100000
L8fc459:
    sar    ecx,0x14
L8fc45c:
    cmp    ecx,0x14
L8fc45f:
    jg     L8fc485
L8fc461:
    {load} mov    edx,edi
L8fc463:
    shl    edx,cl
L8fc465:
    shl    edx,0xc
L8fc468:
    {load} or     edx,eax
L8fc46a:
    jne    L8fc481
L8fc46c:
    add    ecx,0xb
L8fc46f:
    shl    edi,cl
L8fc471:
    not    edi
L8fc473:
    and    edi,0x80000000
L8fc479:
    shr    edi,0x1f
L8fc47c:
    inc    edi
L8fc47d:
    {load} mov    eax,edi
L8fc47f:
    pop    edi
L8fc480:
    ret
L8fc481:
    {load} xor    eax,eax
L8fc483:
    pop    edi
L8fc484:
    ret
L8fc485:
    add    ecx,0xb
L8fc488:
    shl    eax,cl
L8fc48a:
    test   eax,0x7fffffff
L8fc48f:
    jne    L8fc481
L8fc491:
    not    eax
L8fc493:
    and    eax,0x80000000
L8fc498:
    shr    eax,0x1f
L8fc49b:
    inc    eax
L8fc49c:
    pop    edi
L8fc49d:
    ret
L8fc49e:
    mov    eax,0x2
L8fc4a3:
    pop    edi
L8fc4a4:
    ret
.section .note.GNU-stack,"",@progbits
