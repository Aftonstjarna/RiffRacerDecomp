# Mechanically transcribed reference evidence; not high-level source recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4b2500, exclusive end 0x4b2592.
.intel_syntax noprefix
.code32
.text
.global original_record24_append_one
.equ grow_record24,0x4b28d0
original_record24_append_one:
.L4b2500:
 push   ebp
.L4b2501:
 mov.s    ebp,esp
.L4b2503:
 push   esi
.L4b2504:
 mov.s    esi,ecx
.L4b2506:
 push   edi
.L4b2507:
 mov    edi,DWORD PTR [ebp+0x8]
.L4b250a:
 mov    ecx,DWORD PTR [esi+0x4]
.L4b250d:
 cmp.s    edi,ecx
.L4b250f:
 jae .L4b2562
.L4b2511:
 mov    eax,DWORD PTR [esi]
.L4b2513:
 cmp.s    eax,edi
.L4b2515:
 ja .L4b2562
.L4b2517:
 sub.s    edi,eax
.L4b2519:
 mov    eax,0x2aaaaaab
.L4b251e:
 imul   edi
.L4b2520:
 sar    edx,0x2
.L4b2523:
 mov.s    edi,edx
.L4b2525:
 shr    edi,0x1f
.L4b2528:
 add.s    edi,edx
.L4b252a:
 cmp    ecx,DWORD PTR [esi+0x8]
.L4b252d:
 jne .L4b2537
.L4b252f:
 push   ecx
.L4b2530:
 mov.s    ecx,esi
.L4b2532:
 call grow_record24
.L4b2537:
 mov    eax,DWORD PTR [esi]
.L4b2539:
 lea    ecx,[edi+edi*2]
.L4b253c:
 lea    ecx,[eax+ecx*8]
.L4b253f:
 mov    eax,DWORD PTR [esi+0x4]
.L4b2542:
 test   eax,eax
.L4b2544:
 je .L4b2588
.L4b2546:
 movdqu xmm0,XMMWORD PTR [ecx]
.L4b254a:
 pop    edi
.L4b254b:
 movdqu XMMWORD PTR [eax],xmm0
.L4b254f:
 movq   xmm0,QWORD PTR [ecx+0x10]
.L4b2554:
 movq   QWORD PTR [eax+0x10],xmm0
.L4b2559:
 add    DWORD PTR [esi+0x4],0x18
.L4b255d:
 pop    esi
.L4b255e:
 pop    ebp
.L4b255f:
 ret    0x4
.L4b2562:
 cmp    ecx,DWORD PTR [esi+0x8]
.L4b2565:
 jne .L4b256f
.L4b2567:
 push   ecx
.L4b2568:
 mov.s    ecx,esi
.L4b256a:
 call grow_record24
.L4b256f:
 mov    eax,DWORD PTR [esi+0x4]
.L4b2572:
 test   eax,eax
.L4b2574:
 je .L4b2588
.L4b2576:
 movdqu xmm0,XMMWORD PTR [edi]
.L4b257a:
 movdqu XMMWORD PTR [eax],xmm0
.L4b257e:
 movq   xmm0,QWORD PTR [edi+0x10]
.L4b2583:
 movq   QWORD PTR [eax+0x10],xmm0
.L4b2588:
 add    DWORD PTR [esi+0x4],0x18
.L4b258c:
 pop    edi
.L4b258d:
 pop    esi
.L4b258e:
 pop    ebp
.L4b258f:
 ret    0x4
