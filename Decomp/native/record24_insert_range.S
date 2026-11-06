# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x5433a0,0x5434ed); both return paths included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_record24_insert_range
original_record24_insert_range:
L_5433a0:
 push   ebp
L_5433a1:
 {load} mov    ebp,esp
L_5433a3:
 push   ecx
L_5433a4:
 push   ebx
L_5433a5:
 push   esi
L_5433a6:
 mov    esi,DWORD PTR [ebp+0x10]
L_5433a9:
 mov    eax,0x2aaaaaab
L_5433ae:
 push   edi
L_5433af:
 {load} mov    edi,ecx
L_5433b1:
 {load} mov    edx,esi
L_5433b3:
 mov    ecx,DWORD PTR [ebp+0xc]
L_5433b6:
 {load} sub    edx,ecx
L_5433b8:
 imul   edx
L_5433ba:
 sar    edx,0x2
L_5433bd:
 {load} mov    ebx,edx
L_5433bf:
 shr    ebx,0x1f
L_5433c2:
 {load} add    ebx,edx
L_5433c4:
 je L_5434e4
L_5433ca:
 mov    edx,DWORD PTR [edi+0x8]
L_5433cd:
 mov    eax,0x2aaaaaab
L_5433d2:
 sub    edx,DWORD PTR [edi+0x4]
L_5433d5:
 imul   edx
L_5433d7:
 sar    edx,0x2
L_5433da:
 {load} mov    eax,edx
L_5433dc:
 shr    eax,0x1f
L_5433df:
 {load} add    eax,edx
L_5433e1:
 mov    edx,DWORD PTR [edi+0x4]
L_5433e4:
 {load} cmp    eax,ebx
L_5433e6:
 jae L_5434af
L_5433ec:
 sub    edx,DWORD PTR [edi]
L_5433ee:
 mov    eax,0x2aaaaaab
L_5433f3:
 imul   edx
L_5433f5:
 mov    eax,0xaaaaaaa
L_5433fa:
 sar    edx,0x2
L_5433fd:
 {load} mov    ecx,edx
L_5433ff:
 shr    ecx,0x1f
L_543402:
 {load} add    ecx,edx
L_543404:
 {load} sub    eax,ecx
L_543406:
 {load} cmp    eax,ebx
L_543408:
 jae L_543415
L_54340a:
 push   0x999938
L_54340f:
 call   DWORD PTR 0x92d168
L_543415:
 lea    eax,[ecx+ebx*1]
L_543418:
 {load} mov    ecx,edi
L_54341a:
 push   eax
L_54341b:
 call target_543310
L_543420:
 push   eax
L_543421:
 mov    DWORD PTR [ebp-0x4],eax
L_543424:
 call target_543360
L_543429:
 push   DWORD PTR [ebp+0x8]
L_54342c:
 mov    edx,DWORD PTR [ebp+0x8]
L_54342f:
 {load} mov    esi,eax
L_543431:
 mov    ecx,DWORD PTR [edi]
L_543433:
 sub    esp,0x8
L_543436:
 push   esi
L_543437:
 call target_4b3e40
L_54343c:
 mov    edx,DWORD PTR [ebp+0x10]
L_54343f:
 add    esp,0x10
L_543442:
 push   DWORD PTR [ebp+0x8]
L_543445:
 push   ecx
L_543446:
 mov    ecx,DWORD PTR [ebp+0xc]
L_543449:
 push   eax
L_54344a:
 call target_4b3e40
L_54344f:
 mov    edx,DWORD PTR [edi+0x4]
L_543452:
 add    esp,0xc
L_543455:
 mov    ecx,DWORD PTR [ebp+0x8]
L_543458:
 push   DWORD PTR [ebp+0x8]
L_54345b:
 sub    esp,0x8
L_54345e:
 push   eax
L_54345f:
 call target_4b3e40
L_543464:
 mov    ecx,DWORD PTR [edi+0x4]
L_543467:
 mov    eax,0x2aaaaaab
L_54346c:
 sub    ecx,DWORD PTR [edi]
L_54346e:
 add    esp,0x10
L_543471:
 imul   ecx
L_543473:
 sar    edx,0x2
L_543476:
 {load} mov    eax,edx
L_543478:
 shr    eax,0x1f
L_54347b:
 {load} add    eax,edx
L_54347d:
 {load} add    ebx,eax
L_54347f:
 mov    eax,DWORD PTR [edi]
L_543481:
 test   eax,eax
L_543483:
 je L_54348f
L_543485:
 push   eax
L_543486:
 call   DWORD PTR 0x92d4b0
L_54348c:
 add    esp,0x4
L_54348f:
 mov    eax,DWORD PTR [ebp-0x4]
L_543492:
 mov    DWORD PTR [edi],esi
L_543494:
 lea    eax,[eax+eax*2]
L_543497:
 lea    eax,[esi+eax*8]
L_54349a:
 mov    DWORD PTR [edi+0x8],eax
L_54349d:
 lea    eax,[ebx+ebx*2]
L_5434a0:
 lea    eax,[esi+eax*8]
L_5434a3:
 mov    DWORD PTR [edi+0x4],eax
L_5434a6:
 pop    edi
L_5434a7:
 pop    esi
L_5434a8:
 pop    ebx
L_5434a9:
 {load} mov    esp,ebp
L_5434ab:
 pop    ebp
L_5434ac:
 ret    0x10
L_5434af:
 push   DWORD PTR [ebp+0x8]
L_5434b2:
 push   ecx
L_5434b3:
 push   edx
L_5434b4:
 {load} mov    edx,esi
L_5434b6:
 call target_4b3e40
L_5434bb:
 mov    edx,DWORD PTR [edi+0x4]
L_5434be:
 lea    esi,[ebx+ebx*2]
L_5434c1:
 mov    ecx,DWORD PTR [ebp+0x8]
L_5434c4:
 add    esp,0xc
L_5434c7:
 shl    esi,0x3
L_5434ca:
 lea    eax,[esi+edx*1]
L_5434cd:
 {load} cmp    ecx,edx
L_5434cf:
 je L_5434e1
L_5434d1:
 {load} cmp    edx,eax
L_5434d3:
 je L_5434e1
L_5434d5:
 sub    esp,0x8
L_5434d8:
 push   eax
L_5434d9:
 call target_5434f0
L_5434de:
 add    esp,0xc
L_5434e1:
 add    DWORD PTR [edi+0x4],esi
L_5434e4:
 pop    edi
L_5434e5:
 pop    esi
L_5434e6:
 pop    ebx
L_5434e7:
 {load} mov    esp,ebp
L_5434e9:
 pop    ebp
L_5434ea:
 ret    0x10
.equ target_4b3e40,0x4b3e40
.equ target_543310,0x543310
.equ target_543360,0x543360
.equ target_5434f0,0x5434f0
.section .note.GNU-stack,"",@progbits
