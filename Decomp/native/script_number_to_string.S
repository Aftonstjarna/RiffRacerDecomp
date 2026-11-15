# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f25c0,0x4f2657); both returns included; following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_number_to_string
original_script_number_to_string:
L_4f25c0:
    push   ebp
L_4f25c1:
    mov.s    ebp,esp
L_4f25c3:
    and    esp,0xffffffc0
L_4f25c6:
    sub    esp,0x38
L_4f25c9:
    mov    eax,ds:0xbaabc0
L_4f25ce:
    xor.s    eax,esp
L_4f25d0:
    mov    DWORD PTR [esp+0x34],eax
L_4f25d4:
    push   esi
L_4f25d5:
    mov.s    esi,edx
L_4f25d7:
    push   edi
L_4f25d8:
    mov.s    edi,ecx
L_4f25da:
    cmp    DWORD PTR [esi+0x4],0x3
L_4f25de:
    je L_4f25f3
L_4f25e0:
    xor.s    eax,eax
L_4f25e2:
    pop    edi
L_4f25e3:
    pop    esi
L_4f25e4:
    mov.s    ecx,DWORD PTR [esp+0x34]
L_4f25e8:
    xor.s    ecx,esp
L_4f25ea:
    call 0x8f8958
L_4f25ef:
    mov.s    esp,ebp
L_4f25f1:
    pop    ebp
L_4f25f2:
    ret
L_4f25f3:
    movss  xmm0,DWORD PTR [esi]
L_4f25f7:
    lea    eax,[esp+0x1c]
L_4f25fb:
    cvtps2pd xmm0,xmm0
L_4f25fe:
    sub    esp,0x8
L_4f2601:
    movsd  QWORD PTR [esp],xmm0
L_4f2606:
    push   0x9fd764
L_4f260b:
    push   eax
L_4f260c:
    call   DWORD PTR ds:0x92d374
L_4f2612:
    lea    edx,[esp+0x2c]
L_4f2616:
    add    esp,0x10
L_4f2619:
    lea    ecx,[edx+0x1]
L_4f261c:
    {disp8} lea esp,[esp+0x0]
L_4f2620:
    mov    al,BYTE PTR [edx]
L_4f2622:
    inc    edx
L_4f2623:
    test   al,al
L_4f2625:
    jne L_4f2620
L_4f2627:
    sub.s    edx,ecx
L_4f2629:
    mov.s    ecx,edi
L_4f262b:
    push   edx
L_4f262c:
    lea    edx,[esp+0x20]
L_4f2630:
    call 0x4f5e40
L_4f2635:
    mov.s    ecx,DWORD PTR [esp+0x40]
L_4f2639:
    add    esp,0x4
L_4f263c:
    mov    DWORD PTR [esi],eax
L_4f263e:
    mov    eax,0x1
L_4f2643:
    mov    DWORD PTR [esi+0x4],0x4
L_4f264a:
    pop    edi
L_4f264b:
    pop    esi
L_4f264c:
    xor.s    ecx,esp
L_4f264e:
    call 0x8f8958
L_4f2653:
    mov.s    esp,ebp
L_4f2655:
    pop    ebp
L_4f2656:
    ret
.section .note.GNU-stack,"",@progbits
