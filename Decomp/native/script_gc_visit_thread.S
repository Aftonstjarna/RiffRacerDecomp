# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f1540.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_visit_thread
.equ target_4f0ef0,0x4f0ef0
.equ target_4f4e60,0x4f4e60
.equ target_4f7cf0,0x4f7cf0
.equ target_4f7d10,0x4f7d10
original_script_gc_visit_thread:
.L4f1540:
 push   ebp
.L4f1541:
 mov.s    ebp,esp
.L4f1543:
 sub    esp,0x8
.L4f1546:
 push   ebx
.L4f1547:
 mov.s    ebx,edx
.L4f1549:
 mov.s    eax,ecx
.L4f154b:
 push   esi
.L4f154c:
 push   edi
.L4f154d:
 mov    DWORD PTR [ebp-0x8],eax
.L4f1550:
 cmp    DWORD PTR [ebx+0x4c],0x4
.L4f1554:
 jl .L4f1564
.L4f1556:
 mov    edx,DWORD PTR [ebx+0x48]
.L4f1559:
 test   BYTE PTR [edx+0x5],0x3
.L4f155d:
 je .L4f1564
.L4f155f:
 call target_4f0ef0
.L4f1564:
 mov    eax,DWORD PTR [ebx+0x8]
.L4f1567:
 mov.s    edi,eax
.L4f1569:
 mov    ecx,DWORD PTR [ebx+0x28]
.L4f156c:
 mov    edx,DWORD PTR [ebx+0x14]
.L4f156f:
 mov    DWORD PTR [ebp-0x4],eax
.L4f1572:
 cmp.s    ecx,edx
.L4f1574:
 ja .L4f1587
.L4f1576:
 cmp    edi,DWORD PTR [ecx+0x8]
.L4f1579:
 cmovb  edi,DWORD PTR [ecx+0x8]
.L4f157d:
 add    ecx,0x18
.L4f1580:
 cmp.s    ecx,edx
.L4f1582:
 jbe .L4f1576
.L4f1584:
 mov    DWORD PTR [ebp-0x4],edi
.L4f1587:
 mov    esi,DWORD PTR [ebx+0x20]
.L4f158a:
 cmp.s    esi,eax
.L4f158c:
 jae .L4f15b1
.L4f158e:
 mov    edi,DWORD PTR [ebp-0x8]
.L4f1591:
 cmp    DWORD PTR [esi+0x4],0x4
.L4f1595:
 jl .L4f15a6
.L4f1597:
 mov    edx,DWORD PTR [esi]
.L4f1599:
 test   BYTE PTR [edx+0x5],0x3
.L4f159d:
 je .L4f15a6
.L4f159f:
 mov.s    ecx,edi
.L4f15a1:
 call target_4f0ef0
.L4f15a6:
 add    esi,0x8
.L4f15a9:
 cmp    esi,DWORD PTR [ebx+0x8]
.L4f15ac:
 jb .L4f1591
.L4f15ae:
 mov    edi,DWORD PTR [ebp-0x4]
.L4f15b1:
 cmp.s    esi,edi
.L4f15b3:
 ja .L4f15ce
.L4f15b5:
 jmp .L4f15c0
.L4f15b7:
 {disp32} lea esp,[esp+0x0]
.L4f15be:
 mov.s    edi,edi
.L4f15c0:
 mov    DWORD PTR [esi+0x4],0x0
.L4f15c7:
 add    esi,0x8
.L4f15ca:
 cmp.s    esi,edi
.L4f15cc:
 jbe .L4f15c0
.L4f15ce:
 sub    edi,DWORD PTR [ebx+0x20]
.L4f15d1:
 mov    esi,DWORD PTR [ebx+0x30]
.L4f15d4:
 sar    edi,0x3
.L4f15d7:
 cmp    esi,0x4e20
.L4f15dd:
 jg .L4f16e4
.L4f15e3:
 mov    eax,DWORD PTR [ebx+0x28]
.L4f15e6:
 mov    ecx,DWORD PTR [ebx+0x14]
.L4f15e9:
 sub.s    ecx,eax
.L4f15eb:
 mov    DWORD PTR [ebp-0x4],eax
.L4f15ee:
 mov    eax,0x2aaaaaab
.L4f15f3:
 imul   ecx
.L4f15f5:
 sar    edx,0x2
.L4f15f8:
 mov.s    ecx,edx
.L4f15fa:
 shr    ecx,0x1f
.L4f15fd:
 add.s    ecx,edx
.L4f15ff:
 shl    ecx,0x2
.L4f1602:
 cmp.s    ecx,esi
.L4f1604:
 jge .L4f167e
.L4f1606:
 cmp    esi,0x10
.L4f1609:
 jle .L4f167e
.L4f160b:
 mov.s    eax,esi
.L4f160d:
 cdq
.L4f160e:
 sub.s    eax,edx
.L4f1610:
 mov.s    esi,eax
.L4f1612:
 sar    esi,1
.L4f1614:
 lea    ecx,[esi+0x1]
.L4f1617:
 cmp    ecx,0xaaaaaaa
.L4f161d:
 ja .L4f163f
.L4f161f:
 mov    eax,DWORD PTR [ebx+0x30]
.L4f1622:
 lea    ecx,[esi+esi*2]
.L4f1625:
 mov    edx,DWORD PTR [ebp-0x4]
.L4f1628:
 shl    ecx,0x3
.L4f162b:
 push   ecx
.L4f162c:
 lea    eax,[eax+eax*2]
.L4f162f:
 mov.s    ecx,ebx
.L4f1631:
 shl    eax,0x3
.L4f1634:
 push   eax
.L4f1635:
 call target_4f7d10
.L4f163a:
 add    esp,0x8
.L4f163d:
 jmp .L4f1646
.L4f163f:
 mov.s    ecx,ebx
.L4f1641:
 call target_4f7cf0
.L4f1646:
 mov    ecx,DWORD PTR [ebx+0x14]
.L4f1649:
 sub    ecx,DWORD PTR [ebp-0x4]
.L4f164c:
 mov    DWORD PTR [ebp-0x8],eax
.L4f164f:
 mov    DWORD PTR [ebx+0x28],eax
.L4f1652:
 mov    eax,0x2aaaaaab
.L4f1657:
 imul   ecx
.L4f1659:
 mov    ecx,DWORD PTR [ebp-0x8]
.L4f165c:
 sar    edx,0x2
.L4f165f:
 mov.s    eax,edx
.L4f1661:
 mov    DWORD PTR [ebx+0x30],esi
.L4f1664:
 shr    eax,0x1f
.L4f1667:
 add.s    eax,edx
.L4f1669:
 lea    eax,[eax+eax*2]
.L4f166c:
 lea    eax,[ecx+eax*8]
.L4f166f:
 mov    DWORD PTR [ebx+0x14],eax
.L4f1672:
 lea    eax,[esi-0x1]
.L4f1675:
 lea    eax,[eax+eax*2]
.L4f1678:
 lea    eax,[ecx+eax*8]
.L4f167b:
 mov    DWORD PTR [ebx+0x24],eax
.L4f167e:
 mov    esi,DWORD PTR [ebx+0x2c]
.L4f1681:
 lea    eax,[edi*4+0x0]
.L4f1688:
 cmp.s    eax,esi
.L4f168a:
 jge .L4f16e4
.L4f168c:
 cmp    esi,0x5a
.L4f168f:
 jle .L4f16e4
.L4f1691:
 mov.s    eax,esi
.L4f1693:
 cdq
.L4f1694:
 sub.s    eax,edx
.L4f1696:
 mov    edx,DWORD PTR [ebx+0x20]
.L4f1699:
 mov.s    edi,eax
.L4f169b:
 mov    DWORD PTR [ebp-0x8],edx
.L4f169e:
 sar    edi,1
.L4f16a0:
 lea    eax,[edi+0x6]
.L4f16a3:
 lea    ecx,[eax+0x1]
.L4f16a6:
 cmp    ecx,0x1fffffff
.L4f16ac:
 mov.s    ecx,ebx
.L4f16ae:
 ja .L4f16c6
.L4f16b0:
 shl    eax,0x3
.L4f16b3:
 push   eax
.L4f16b4:
 lea    eax,[esi*8+0x0]
.L4f16bb:
 push   eax
.L4f16bc:
 call target_4f7d10
.L4f16c1:
 add    esp,0x8
.L4f16c4:
 jmp .L4f16cb
.L4f16c6:
 call target_4f7cf0
.L4f16cb:
 mov    edx,DWORD PTR [ebp-0x8]
.L4f16ce:
 lea    ecx,[edi+0x6]
.L4f16d1:
 mov    DWORD PTR [ebx+0x20],eax
.L4f16d4:
 lea    eax,[eax+edi*8]
.L4f16d7:
 mov    DWORD PTR [ebx+0x2c],ecx
.L4f16da:
 mov.s    ecx,ebx
.L4f16dc:
 mov    DWORD PTR [ebx+0x1c],eax
.L4f16df:
 call target_4f4e60
.L4f16e4:
 pop    edi
.L4f16e5:
 pop    esi
.L4f16e6:
 pop    ebx
.L4f16e7:
 mov.s    esp,ebp
.L4f16e9:
 pop    ebp
.L4f16ea:
 ret
