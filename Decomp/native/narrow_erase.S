# Reviewed pinned depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Evidence /tmp/cloud-string-growth/{erase.asm,exports/00416660.txt}.
# thiscall ECX=string, stack offset/count; EAX=this, ret 8; preserves EBP/ESI/EDI
# and EBX on shift path. Reject offset>size via nonreturning Xout_of_range
# (IAT 92d16c, message 99995c). Clamp suffix deletion, otherwise memmove tail
# through 92d4a4; capacity>=16 selects heap. Update size and NUL; count=0 no-op.
# No local EH or embedded data. Final ret ends 4166fb; exclude int3 padding.
# Original VA range 0x416660..0x4166fb
.intel_syntax noprefix
.code32
.text
.global original_narrow_erase
original_narrow_erase:
.L416660:
 push   ebp
.L416661:
 {load} mov    ebp,esp
.L416663:
 push   esi
.L416664:
 {load} mov    esi,ecx
.L416666:
 mov    ecx,DWORD PTR [ebp+0x8]
.L416669:
 push   edi
.L41666a:
 mov    edi,DWORD PTR [esi+0x10]
.L41666d:
 {load} cmp    edi,ecx
.L41666f:
 jae .L41667c
.L416671:
 push   0x99995c
.L416676:
 call   DWORD PTR [0x92d16c]
.L41667c:
 mov    edx,DWORD PTR [ebp+0xc]
.L41667f:
 {load} mov    eax,edi
.L416681:
 {load} sub    eax,ecx
.L416683:
 {load} cmp    eax,edx
.L416685:
 ja .L4166aa
.L416687:
 cmp    DWORD PTR [esi+0x14],0x10
.L41668b:
 mov    DWORD PTR [esi+0x10],ecx
.L41668e:
 jb .L41669e
.L416690:
 mov    eax,DWORD PTR [esi]
.L416692:
 pop    edi
.L416693:
 mov    BYTE PTR [eax+ecx*1],0x0
.L416697:
 {load} mov    eax,esi
.L416699:
 pop    esi
.L41669a:
 pop    ebp
.L41669b:
 ret    0x8
.L41669e:
 {load} mov    eax,esi
.L4166a0:
 pop    edi
.L4166a1:
 pop    esi
.L4166a2:
 mov    BYTE PTR [eax+ecx*1],0x0
.L4166a6:
 pop    ebp
.L4166a7:
 ret    0x8
.L4166aa:
 test   edx,edx
.L4166ac:
 je .L4166f3
.L4166ae:
 cmp    DWORD PTR [esi+0x14],0x10
.L4166b2:
 jb .L4166b8
.L4166b4:
 mov    eax,DWORD PTR [esi]
.L4166b6:
 jmp .L4166ba
.L4166b8:
 {load} mov    eax,esi
.L4166ba:
 {load} sub    edi,edx
.L4166bc:
 push   ebx
.L4166bd:
 lea    ebx,[eax+ecx*1]
.L4166c0:
 {load} mov    eax,edi
.L4166c2:
 {load} sub    eax,ecx
.L4166c4:
 je .L4166d5
.L4166c6:
 push   eax
.L4166c7:
 lea    eax,[ebx+edx*1]
.L4166ca:
 push   eax
.L4166cb:
 push   ebx
.L4166cc:
 call   DWORD PTR [0x92d4a4]
.L4166d2:
 add    esp,0xc
.L4166d5:
 cmp    DWORD PTR [esi+0x14],0x10
.L4166d9:
 mov    DWORD PTR [esi+0x10],edi
.L4166dc:
 pop    ebx
.L4166dd:
 jb .L4166ed
.L4166df:
 mov    eax,DWORD PTR [esi]
.L4166e1:
 mov    BYTE PTR [eax+edi*1],0x0
.L4166e5:
 {load} mov    eax,esi
.L4166e7:
 pop    edi
.L4166e8:
 pop    esi
.L4166e9:
 pop    ebp
.L4166ea:
 ret    0x8
.L4166ed:
 {load} mov    eax,esi
.L4166ef:
 mov    BYTE PTR [eax+edi*1],0x0
.L4166f3:
 pop    edi
.L4166f4:
 {load} mov    eax,esi
.L4166f6:
 pop    esi
.L4166f7:
 pop    ebp
.L4166f8:
 ret    0x8
