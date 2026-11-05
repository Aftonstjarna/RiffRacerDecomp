# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x416520; exclusive end 0x416617. All six returns and intervening branches included.
.intel_syntax noprefix
.code32
.text
.global original_narrow_assign_range
original_narrow_assign_range:
.L416520:
 push   ebp
.L416521:
 {load} mov    ebp,esp
.L416523:
 push   ebx
.L416524:
 mov    ebx,DWORD PTR [ebp+0x8]
.L416527:
 push   esi
.L416528:
 {load} mov    esi,ecx
.L41652a:
 test   ebx,ebx
.L41652c:
 je .L416585
.L41652e:
 mov    ecx,DWORD PTR [esi+0x14]
.L416531:
 cmp    ecx,0x10
.L416534:
 jb .L41653a
.L416536:
 mov    eax,DWORD PTR [esi]
.L416538:
 jmp .L41653c
.L41653a:
 {load} mov    eax,esi
.L41653c:
 {load} cmp    ebx,eax
.L41653e:
 jb .L416585
.L416540:
 cmp    ecx,0x10
.L416543:
 jb .L416549
.L416545:
 mov    edx,DWORD PTR [esi]
.L416547:
 jmp .L41654b
.L416549:
 {load} mov    edx,esi
.L41654b:
 mov    eax,DWORD PTR [esi+0x10]
.L41654e:
 {load} add    eax,edx
.L416550:
 {load} cmp    eax,ebx
.L416552:
 jbe .L416585
# Interior source delegates to substring assignment; retain both storage branches.
.L416554:
 cmp    ecx,0x10
.L416557:
 jb .L41656f
.L416559:
 push   DWORD PTR [ebp+0xc]
.L41655c:
 mov    eax,DWORD PTR [esi]
.L41655e:
 {load} mov    ecx,esi
.L416560:
 {load} sub    ebx,eax
.L416562:
 push   ebx
.L416563:
 push   esi
.L416564:
 call target_415fe0
.L416569:
 pop    esi
.L41656a:
 pop    ebx
.L41656b:
 pop    ebp
.L41656c:
 ret    0x8
.L41656f:
 push   DWORD PTR [ebp+0xc]
.L416572:
 {load} mov    eax,esi
.L416574:
 {load} mov    ecx,esi
.L416576:
 {load} sub    ebx,eax
.L416578:
 push   ebx
.L416579:
 push   esi
.L41657a:
 call target_415fe0
.L41657f:
 pop    esi
.L416580:
 pop    ebx
.L416581:
 pop    ebp
.L416582:
 ret    0x8
# Nonalias source: validate length, ensure capacity, copy, terminate.
.L416585:
 push   edi
.L416586:
 mov    edi,DWORD PTR [ebp+0xc]
.L416589:
 cmp    edi,0xfffffffe
.L41658c:
 jbe .L416599
.L41658e:
 push   0x99994c
.L416593:
 call   DWORD PTR 0x92d168
.L416599:
 mov    eax,DWORD PTR [esi+0x14]
.L41659c:
 {load} cmp    eax,edi
.L41659e:
 jae .L4165b9
.L4165a0:
 push   DWORD PTR [esi+0x10]
.L4165a3:
 {load} mov    ecx,esi
.L4165a5:
 push   edi
.L4165a6:
 call target_416890
.L4165ab:
 test   edi,edi
.L4165ad:
 je .L41660e
.L4165af:
 cmp    DWORD PTR [esi+0x14],0x10
.L4165b3:
 jb .L4165df
.L4165b5:
 mov    eax,DWORD PTR [esi]
.L4165b7:
 jmp .L4165e1
.L4165b9:
 test   edi,edi
.L4165bb:
 jne .L4165af
.L4165bd:
 mov    DWORD PTR [esi+0x10],edi
.L4165c0:
 cmp    eax,0x10
.L4165c3:
 jb .L4165d3
.L4165c5:
 mov    eax,DWORD PTR [esi]
.L4165c7:
 pop    edi
.L4165c8:
 mov    BYTE PTR [eax],0x0
.L4165cb:
 {load} mov    eax,esi
.L4165cd:
 pop    esi
.L4165ce:
 pop    ebx
.L4165cf:
 pop    ebp
.L4165d0:
 ret    0x8
.L4165d3:
 {load} mov    eax,esi
.L4165d5:
 pop    edi
.L4165d6:
 pop    esi
.L4165d7:
 pop    ebx
.L4165d8:
 mov    BYTE PTR [eax],0x0
.L4165db:
 pop    ebp
.L4165dc:
 ret    0x8
.L4165df:
 {load} mov    eax,esi
.L4165e1:
 test   edi,edi
.L4165e3:
 je .L4165f0
.L4165e5:
 push   edi
.L4165e6:
 push   ebx
.L4165e7:
 push   eax
.L4165e8:
 call target_8f8d66
.L4165ed:
 add    esp,0xc
.L4165f0:
 cmp    DWORD PTR [esi+0x14],0x10
.L4165f4:
 mov    DWORD PTR [esi+0x10],edi
.L4165f7:
 jb .L416608
.L4165f9:
 mov    eax,DWORD PTR [esi]
.L4165fb:
 mov    BYTE PTR [eax+edi*1],0x0
.L4165ff:
 {load} mov    eax,esi
.L416601:
 pop    edi
.L416602:
 pop    esi
.L416603:
 pop    ebx
.L416604:
 pop    ebp
.L416605:
 ret    0x8
.L416608:
 {load} mov    eax,esi
.L41660a:
 mov    BYTE PTR [eax+edi*1],0x0
.L41660e:
 pop    edi
.L41660f:
 {load} mov    eax,esi
.L416611:
 pop    esi
.L416612:
 pop    ebx
.L416613:
 pop    ebp
.L416614:
 ret    0x8
.equ target_415fe0,0x415fe0
.equ target_416890,0x416890
.equ target_8f8d66,0x8f8d66
.section .note.GNU-stack,"",@progbits
