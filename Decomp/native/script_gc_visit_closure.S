# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f13d0.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_visit_closure
.equ MARK_OBJECT,0x4f0ef0
original_script_gc_visit_closure:
L_4f13d0:
    push ebp
L_4f13d1:
    mov.s ebp,esp
L_4f13d3:
    sub esp,0xc
L_4f13d6:
    push ebx
L_4f13d7:
    push esi
L_4f13d8:
    push edi
L_4f13d9:
    mov.s edi,edx
L_4f13db:
    mov.s ebx,ecx
L_4f13dd:
    mov DWORD PTR [ebp-0xc],ebx
L_4f13e0:
    mov edx,DWORD PTR [edi+0xc]
L_4f13e3:
    test BYTE PTR [edx+0x5],0x3
L_4f13e7:
    je L_4f13ee
L_4f13e9:
    call MARK_OBJECT
L_4f13ee:
    cmp BYTE PTR [edi+0x6],0x0
L_4f13f2:
    je L_4f142b
L_4f13f4:
    xor.s ebx,ebx
L_4f13f6:
    cmp BYTE PTR [edi+0x7],bl
L_4f13f9:
    jbe L_4f1516
L_4f13ff:
    lea esi,[edi+0x14]
L_4f1402:
    cmp DWORD PTR [esi+0x4],0x4
L_4f1406:
    jl L_4f1418
L_4f1408:
    mov edx,DWORD PTR [esi]
L_4f140a:
    test BYTE PTR [edx+0x5],0x3
L_4f140e:
    je L_4f1418
L_4f1410:
    mov ecx,DWORD PTR [ebp-0xc]
L_4f1413:
    call MARK_OBJECT
L_4f1418:
    movzx eax,BYTE PTR [edi+0x7]
L_4f141c:
    inc ebx
L_4f141d:
    add esi,0x8
L_4f1420:
    cmp.s ebx,eax
L_4f1422:
    jl L_4f1402
L_4f1424:
    pop edi
L_4f1425:
    pop esi
L_4f1426:
    pop ebx
L_4f1427:
    mov.s esp,ebp
L_4f1429:
    pop ebp
L_4f142a:
    ret
L_4f142b:
    mov edx,DWORD PTR [edi+0x10]
L_4f142e:
    test BYTE PTR [edx+0x5],0x3
L_4f1432:
    je L_4f143b
L_4f1434:
    mov.s ecx,ebx
L_4f1436:
    call MARK_OBJECT
L_4f143b:
    xor.s edx,edx
L_4f143d:
    mov DWORD PTR [ebp-0x8],edx
L_4f1440:
    cmp BYTE PTR [edi+0x7],dl
L_4f1443:
    jbe L_4f1516
L_4f1449:
    lea ecx,[edi+0x14]
L_4f144c:
    mov DWORD PTR [ebp-0xc],ecx
L_4f144f:
    nop
L_4f1450:
    mov esi,DWORD PTR [ecx]
L_4f1452:
    test BYTE PTR [esi+0x5],0x3
L_4f1456:
    je L_4f1500
L_4f145c:
    movzx eax,BYTE PTR [esi+0x4]
L_4f1460:
    and BYTE PTR [esi+0x5],0xfc
L_4f1464:
    add eax,0xfffffffc
L_4f1467:
    cmp eax,0x6
L_4f146a:
    ja L_4f1500
L_4f1470:
    jmp DWORD PTR [eax*4+0x4f1520]
L_4f1477:
    or BYTE PTR [esi+0x5],0x4
L_4f147b:
    mov eax,DWORD PTR [esi+0x8]
L_4f147e:
    test eax,eax
L_4f1480:
    je L_4f1497
L_4f1482:
    test BYTE PTR [eax+0x5],0x3
L_4f1486:
    je L_4f1497
L_4f1488:
    mov.s edx,eax
L_4f148a:
    mov.s ecx,ebx
L_4f148c:
    call MARK_OBJECT
L_4f1491:
    mov ecx,DWORD PTR [ebp-0xc]
L_4f1494:
    mov edx,DWORD PTR [ebp-0x8]
L_4f1497:
    mov eax,DWORD PTR [esi+0xc]
L_4f149a:
    test BYTE PTR [eax+0x5],0x3
L_4f149e:
    je L_4f1500
L_4f14a0:
    mov.s edx,eax
L_4f14a2:
    mov.s ecx,ebx
L_4f14a4:
    call MARK_OBJECT
L_4f14a9:
    mov ecx,DWORD PTR [ebp-0xc]
L_4f14ac:
    mov edx,DWORD PTR [ebp-0x8]
L_4f14af:
    jmp L_4f1500
L_4f14b1:
    mov eax,DWORD PTR [esi+0x8]
L_4f14b4:
    cmp DWORD PTR [eax+0x4],0x4
L_4f14b8:
    jl L_4f14d1
L_4f14ba:
    mov eax,DWORD PTR [eax]
L_4f14bc:
    test BYTE PTR [eax+0x5],0x3
L_4f14c0:
    je L_4f14d1
L_4f14c2:
    mov.s edx,eax
L_4f14c4:
    mov.s ecx,ebx
L_4f14c6:
    call MARK_OBJECT
L_4f14cb:
    mov ecx,DWORD PTR [ebp-0xc]
L_4f14ce:
    mov edx,DWORD PTR [ebp-0x8]
L_4f14d1:
    lea eax,[esi+0xc]
L_4f14d4:
    cmp DWORD PTR [esi+0x8],eax
L_4f14d7:
    jne L_4f1500
L_4f14d9:
    or BYTE PTR [esi+0x5],0x4
L_4f14dd:
    jmp L_4f1500
L_4f14df:
    mov eax,DWORD PTR [ebx+0x24]
L_4f14e2:
    mov DWORD PTR [esi+0x8],eax
L_4f14e5:
    jmp L_4f14fd
L_4f14e7:
    mov eax,DWORD PTR [ebx+0x24]
L_4f14ea:
    mov DWORD PTR [esi+0x18],eax
L_4f14ed:
    jmp L_4f14fd
L_4f14ef:
    mov eax,DWORD PTR [ebx+0x24]
L_4f14f2:
    mov DWORD PTR [esi+0x5c],eax
L_4f14f5:
    jmp L_4f14fd
L_4f14f7:
    mov eax,DWORD PTR [ebx+0x24]
L_4f14fa:
    mov DWORD PTR [esi+0x44],eax
L_4f14fd:
    mov DWORD PTR [ebx+0x24],esi
L_4f1500:
    movzx eax,BYTE PTR [edi+0x7]
L_4f1504:
    inc edx
L_4f1505:
    add ecx,0x4
L_4f1508:
    mov DWORD PTR [ebp-0x8],edx
L_4f150b:
    mov DWORD PTR [ebp-0xc],ecx
L_4f150e:
    cmp.s edx,eax
L_4f1510:
    jl L_4f1450
L_4f1516:
    pop edi
L_4f1517:
    pop esi
L_4f1518:
    pop ebx
L_4f1519:
    mov.s esp,ebp
L_4f151b:
    pop ebp
L_4f151c:
    ret
.section .note.GNU-stack,"",@progbits
