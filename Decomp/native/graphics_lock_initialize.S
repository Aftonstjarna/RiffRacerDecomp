# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x536340,0x5365f7); instruction-contiguous extent, INT3 padding excluded.
# Graphics lock initialization: creates the graphics subsystem critical section with the pinned spin count and preserves the original SEH frame and failure cleanup. Called from graphics startup.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x536340..0x5365f7
.intel_syntax noprefix
.code32
.text
.global original_graphics_lock_initialize
original_graphics_lock_initialize:
.L536340:
 push   ebp
.L536341:
 {load} mov    ebp,esp
.L536343:
 push   0xffffffff
.L536345:
 push   0x906404
.L53634a:
 mov    eax,fs:0x0
.L536350:
 push   eax
.L536351:
 push   ecx
.L536352:
 push   esi
.L536353:
 push   edi
.L536354:
 mov    eax,[0xbaabc0]
.L536359:
 {load} xor    eax,ebp
.L53635b:
 push   eax
.L53635c:
 lea    eax,[ebp-0xc]
.L53635f:
 mov    fs:0x0,eax
.L536365:
 {load} mov    esi,ecx
.L536367:
 mov    DWORD PTR [ebp-0x10],esi
.L53636a:
 mov    BYTE PTR [esi+0x4],0x0
.L53636e:
 mov    DWORD PTR [ebp-0x4],0x1
.L536375:
 mov    DWORD PTR [esi],0x9fff28
.L53637b:
 mov    DWORD PTR [esi+0x8],0x0
.L536382:
 mov    DWORD PTR [esi+0xc],0x0
.L536389:
 mov    WORD PTR [esi+0x10],0x0
.L53638f:
 mov    DWORD PTR [esi+0x14],0x0
.L536396:
 mov    DWORD PTR [esi+0x18],0x0
.L53639d:
 mov    DWORD PTR [esi+0x18c],0x0
.L5363a7:
 mov    DWORD PTR [esi+0x1c0],0x0
.L5363b1:
 mov    DWORD PTR [esi+0x1c4],0x0
.L5363bb:
 mov    DWORD PTR [esi+0x1c8],0x0
.L5363c5:
 mov    DWORD PTR [esi+0x1fc],0x0
.L5363cf:
 mov    DWORD PTR [esi+0x200],0x0
.L5363d9:
 mov    DWORD PTR [esi+0x204],0x0
.L5363e3:
 lea    eax,[esi+0x208]
.L5363e9:
 push   0x80001000
.L5363ee:
 push   eax
.L5363ef:
 call   DWORD PTR [0x92d07c]
.L5363f5:
 lea    ecx,[esi+0x220]
.L5363fb:
 mov    DWORD PTR [ecx],0x0
.L536401:
 mov    DWORD PTR [ecx+0x4],0x0
.L536408:
 mov    DWORD PTR [ecx+0x8],0x0
.L53640f:
 lea    edi,[esi+0x22c]
.L536415:
 mov    DWORD PTR [edi],0x0
.L53641b:
 mov    DWORD PTR [edi+0x4],0x0
.L536422:
 mov    DWORD PTR [edi+0x8],0x0
.L536429:
 mov    DWORD PTR [esi+0x238],0x0
.L536433:
 mov    DWORD PTR [esi+0x23c],0x0
.L53643d:
 mov    DWORD PTR [esi+0x240],0x0
.L536447:
 mov    DWORD PTR [esi+0x244],0x0
.L536451:
 mov    DWORD PTR [esi+0x248],0x0
.L53645b:
 mov    DWORD PTR [esi+0x24c],0x0
.L536465:
 mov    DWORD PTR [esi+0x250],0x0
.L53646f:
 mov    DWORD PTR [esi+0x254],0x0
.L536479:
 mov    DWORD PTR [esi+0x258],0x0
.L536483:
 mov    BYTE PTR [ebp-0x4],0xb
.L536487:
 mov    DWORD PTR [esi+0x25c],0x0
.L536491:
 mov    DWORD PTR [esi+0x260],0xffffffff
.L53649b:
 mov    eax,DWORD PTR [esi+0x204]
.L5364a1:
 sub    eax,DWORD PTR [esi+0x1fc]
.L5364a7:
 sar    eax,0x2
.L5364aa:
 cmp    eax,0x100
.L5364af:
 jae .L5364c7
.L5364b1:
 push   0x100
.L5364b6:
 lea    ecx,[esi+0x1fc]
.L5364bc:
 call target_426800
.L5364c1:
 lea    ecx,[esi+0x220]
.L5364c7:
 mov    eax,DWORD PTR [ecx+0x8]
.L5364ca:
 sub    eax,DWORD PTR [ecx]
.L5364cc:
 sar    eax,0x2
.L5364cf:
 cmp    eax,0x100
.L5364d4:
 jae .L5364e0
.L5364d6:
 push   0x100
.L5364db:
 call target_426800
.L5364e0:
 mov    eax,DWORD PTR [edi+0x8]
.L5364e3:
 sub    eax,DWORD PTR [edi]
.L5364e5:
 sar    eax,0x2
.L5364e8:
 cmp    eax,0x100
.L5364ed:
 jae .L5364fb
.L5364ef:
 push   0x100
.L5364f4:
 {load} mov    ecx,edi
.L5364f6:
 call target_426800
.L5364fb:
 lea    eax,[esi+0x78]
.L5364fe:
 mov    ecx,0x17
.L536503:
 mov    DWORD PTR [eax-0x5c],0x0
.L53650a:
 lea    eax,[eax+0x4]
.L53650d:
 mov    DWORD PTR [eax-0x4],0x0
.L536514:
 mov    DWORD PTR [eax+0x58],0x0
.L53651b:
 mov    DWORD PTR [eax+0xb4],0x0
.L536525:
 dec    ecx
.L536526:
 jne .L536503
.L536528:
 mov    eax,DWORD PTR [esi+0x1c8]
.L53652e:
 lea    ecx,[esi+0x1c0]
.L536534:
 sub    eax,DWORD PTR [ecx]
.L536536:
 sar    eax,0x4
.L536539:
 cmp    eax,0x18
.L53653c:
 jae .L536545
.L53653e:
 push   0x18
.L536540:
 call target_49c900
.L536545:
 movdqa xmm0,XMMWORD PTR [0xa07250]
.L53654d:
 {load} mov    eax,esi
.L53654f:
 movdqu XMMWORD PTR [esi+0x1cc],xmm0
.L536557:
 movdqu XMMWORD PTR [esi+0x1dc],xmm0
.L53655f:
 movdqu XMMWORD PTR [esi+0x1ec],xmm0
.L536567:
 mov    DWORD PTR [esi+0x18c],0x0
.L536571:
 mov    DWORD PTR [esi+0x190],0x0
.L53657b:
 mov    DWORD PTR [esi+0x194],0x0
.L536585:
 mov    DWORD PTR [esi+0x198],0x0
.L53658f:
 mov    DWORD PTR [esi+0x19c],0x0
.L536599:
 mov    DWORD PTR [esi+0x1a0],0x0
.L5365a3:
 mov    DWORD PTR [esi+0x1a4],0x0
.L5365ad:
 mov    DWORD PTR [esi+0x1a8],0x0
.L5365b7:
 mov    DWORD PTR [esi+0x1ac],0x0
.L5365c1:
 mov    DWORD PTR [esi+0x1b0],0x0
.L5365cb:
 mov    DWORD PTR [esi+0x1b4],0x0
.L5365d5:
 mov    DWORD PTR [esi+0x1b8],0x0
.L5365df:
 mov    BYTE PTR [esi+0x1bc],0x0
.L5365e6:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5365e9:
 mov    DWORD PTR fs:0x0,ecx
.L5365f0:
 pop    ecx
.L5365f1:
 pop    edi
.L5365f2:
 pop    esi
.L5365f3:
 {load} mov    esp,ebp
.L5365f5:
 pop    ebp
.L5365f6:
 ret
.equ target_426800,0x426800
.equ target_49c900,0x49c900
