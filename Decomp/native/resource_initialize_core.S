# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x440120,0x4408e3); instruction-contiguous extent, padding excluded.
# Resource initialization core reached from 0x43F480: SEH frame, operator new via IAT 0x92D4B4,
# constructor/initialization helpers 0x417420, 0x4174B0 and 0x418460, reference-count update
# and original failure cleanup. Instruction-derived; dependency identities are not fully proven.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x440120..0x4408e3
.intel_syntax noprefix
.code32
.text
.global original_resource_initialize_core
original_resource_initialize_core:
.L440120:
 push   ebp
.L440121:
 {load} mov    ebp,esp
.L440123:
 and    esp,0xfffffff0
.L440126:
 push   0xffffffff
.L440128:
 push   0x8ff097
.L44012d:
 mov    eax,fs:0x0
.L440133:
 push   eax
.L440134:
 sub    esp,0x8c
.L44013a:
 push   esi
.L44013b:
 push   edi
.L44013c:
 mov    eax,[0xbaabc0]
.L440141:
 {load} xor    eax,esp
.L440143:
 push   eax
.L440144:
 lea    eax,[esp+0x98]
.L44014b:
 mov    fs:0x0,eax
.L440151:
 {load} mov    edi,ecx
.L440153:
 mov    eax,[0xc0d408]
.L440158:
 mov    ecx,0xbbd00c
.L44015d:
 push   0x94
.L440162:
 push   0x94
.L440167:
 mov    DWORD PTR [esp+0x24],eax
.L44016b:
 call target_442bd0
.L440170:
 mov    DWORD PTR [esp+0xc],eax
.L440174:
 mov    DWORD PTR [esp+0xa0],0x0
.L44017f:
 test   eax,eax
.L440181:
 je .L440190
.L440183:
 push   0x1
.L440185:
 {load} mov    ecx,eax
.L440187:
 call target_423b70
.L44018c:
 {load} mov    esi,eax
.L44018e:
 jmp .L440192
.L440190:
 {load} xor    esi,esi
.L440192:
 mov    DWORD PTR [esp+0xa0],0xffffffff
.L44019d:
 mov    edx,DWORD PTR [edi+0x4]
.L4401a0:
 {load} cmp    edx,esi
.L4401a2:
 je .L4401ca
.L4401a4:
 test   edx,edx
.L4401a6:
 je .L4401ba
.L4401a8:
 mov    eax,DWORD PTR [edx]
.L4401aa:
 mov    ecx,DWORD PTR [eax+0x4]
.L4401ad:
 {load} add    ecx,edx
.L4401af:
 dec    DWORD PTR [ecx+0x4]
.L4401b2:
 jne .L4401ba
.L4401b4:
 mov    eax,DWORD PTR [ecx]
.L4401b6:
 push   0x1
.L4401b8:
 call   DWORD PTR [eax]
.L4401ba:
 mov    DWORD PTR [edi+0x4],esi
.L4401bd:
 test   esi,esi
.L4401bf:
 je .L4401ca
.L4401c1:
 mov    eax,DWORD PTR [esi]
.L4401c3:
 mov    eax,DWORD PTR [eax+0x4]
.L4401c6:
 inc    DWORD PTR [eax+esi*1+0x4]
.L4401ca:
 push   0x9f9b80
.L4401cf:
 lea    ecx,[esp+0x1c]
.L4401d3:
 call target_418460
.L4401d8:
 lea    eax,[esp+0x18]
.L4401dc:
 mov    DWORD PTR [esp+0xa0],0x1
.L4401e7:
 mov    ecx,DWORD PTR [edi+0x4]
.L4401ea:
 push   eax
.L4401eb:
 call target_43f140
.L4401f0:
 mov    DWORD PTR [esp+0xa0],0xffffffff
.L4401fb:
 mov    esi,DWORD PTR [esp+0x18]
.L4401ff:
 test   esi,esi
.L440201:
 js .L440226
.L440203:
 call target_417420
.L440208:
 mov    ecx,DWORD PTR [eax+0x4]
.L44020b:
 mov    eax,DWORD PTR [eax+0x28]
.L44020e:
 movsx  ecx,WORD PTR [ecx+esi*2]
.L440212:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L440216:
 jne .L440226
.L440218:
 call target_417420
.L44021d:
 push   esi
.L44021e:
 lea    ecx,[eax+0x4]
.L440221:
 call target_41c090
.L440226:
 cmp    DWORD PTR [edi+0x98],0x0
.L44022d:
 je .L440242
.L44022f:
 cmp    DWORD PTR [edi+0x9c],0x10
.L440236:
 lea    eax,[edi+0x88]
.L44023c:
 jb .L440247
.L44023e:
 mov    eax,DWORD PTR [eax]
.L440240:
 jmp .L440247
.L440242:
 mov    eax,0x9f9a24
.L440247:
 push   eax
.L440248:
 lea    ecx,[esp+0x30]
.L44024c:
 call target_418460
.L440251:
 push   0x94
.L440256:
 push   0x94
.L44025b:
 mov    ecx,0xbbd00c
.L440260:
 mov    DWORD PTR [esp+0xa8],0x2
.L44026b:
 call target_442bd0
.L440270:
 mov    DWORD PTR [esp+0xc],eax
.L440274:
 mov    BYTE PTR [esp+0xa0],0x3
.L44027c:
 test   eax,eax
.L44027e:
 je .L44028d
.L440280:
 push   0x1
.L440282:
 {load} mov    ecx,eax
.L440284:
 call target_423b70
.L440289:
 {load} mov    esi,eax
.L44028b:
 jmp .L44028f
.L44028d:
 {load} xor    esi,esi
.L44028f:
 mov    BYTE PTR [esp+0xa0],0x2
.L440297:
 mov    edx,DWORD PTR [edi+0x8]
.L44029a:
 {load} cmp    edx,esi
.L44029c:
 je .L4402c4
.L44029e:
 test   edx,edx
.L4402a0:
 je .L4402b4
.L4402a2:
 mov    eax,DWORD PTR [edx]
.L4402a4:
 mov    ecx,DWORD PTR [eax+0x4]
.L4402a7:
 {load} add    ecx,edx
.L4402a9:
 dec    DWORD PTR [ecx+0x4]
.L4402ac:
 jne .L4402b4
.L4402ae:
 mov    eax,DWORD PTR [ecx]
.L4402b0:
 push   0x1
.L4402b2:
 call   DWORD PTR [eax]
.L4402b4:
 mov    DWORD PTR [edi+0x8],esi
.L4402b7:
 test   esi,esi
.L4402b9:
 je .L4402c4
.L4402bb:
 mov    eax,DWORD PTR [esi]
.L4402bd:
 mov    eax,DWORD PTR [eax+0x4]
.L4402c0:
 inc    DWORD PTR [eax+esi*1+0x4]
.L4402c4:
 mov    ecx,DWORD PTR [edi+0x8]
.L4402c7:
 lea    eax,[esp+0x2c]
.L4402cb:
 push   eax
.L4402cc:
 call target_43f140
.L4402d1:
 push   0x4
.L4402d3:
 call   DWORD PTR [0x92d4b4]
.L4402d9:
 {load} mov    ecx,eax
.L4402db:
 add    esp,0x4
.L4402de:
 test   ecx,ecx
.L4402e0:
 je .L4402ea
.L4402e2:
 mov    DWORD PTR [ecx],0x9f9bc8
.L4402e8:
 jmp .L4402ec
.L4402ea:
 {load} xor    ecx,ecx
.L4402ec:
 mov    eax,DWORD PTR [edi+0x8]
.L4402ef:
 mov    DWORD PTR [eax+0x18],ecx
.L4402f2:
 push   DWORD PTR [edi+0x8]
.L4402f5:
 mov    ecx,DWORD PTR [edi]
.L4402f7:
 call target_457bb0
.L4402fc:
 cmp    DWORD PTR [edi+0xb0],0x0
.L440303:
 je .L440318
.L440305:
 cmp    DWORD PTR [edi+0xb4],0x10
.L44030c:
 lea    eax,[edi+0xa0]
.L440312:
 jb .L44031d
.L440314:
 mov    eax,DWORD PTR [eax]
.L440316:
 jmp .L44031d
.L440318:
 mov    eax,0x9f9a38
.L44031d:
 push   eax
.L44031e:
 lea    ecx,[esp+0x34]
.L440322:
 call target_418790
.L440327:
 mov    BYTE PTR [esp+0xa0],0x4
.L44032f:
 cmp    DWORD PTR [edi+0xb0],0x0
.L440336:
 je .L440341
.L440338:
 cmp    DWORD PTR [edi+0x98],0x0
.L44033f:
 jne .L44034e
.L440341:
 cmp    DWORD PTR [edi+0x98],0x0
.L440348:
 jne .L44052b
.L44034e:
 push   0x20
.L440350:
 push   0x20
.L440352:
 mov    ecx,0xbbd1a8
.L440357:
 call target_442bd0
.L44035c:
 test   eax,eax
.L44035e:
 je .L44036c
.L440360:
 push   ecx
.L440361:
 {load} mov    ecx,eax
.L440363:
 call target_43f0e0
.L440368:
 {load} mov    ecx,eax
.L44036a:
 jmp .L44036e
.L44036c:
 {load} xor    ecx,ecx
.L44036e:
 push   ecx
.L44036f:
 {load} mov    eax,esp
.L440371:
 mov    DWORD PTR [eax],ecx
.L440373:
 test   ecx,ecx
.L440375:
 je .L440380
.L440377:
 mov    eax,DWORD PTR [ecx]
.L440379:
 mov    eax,DWORD PTR [eax+0x4]
.L44037c:
 inc    DWORD PTR [eax+ecx*1+0x4]
.L440380:
 mov    ecx,DWORD PTR [edi+0x8]
.L440383:
 call target_43f1b0
.L440388:
 mov    ecx,DWORD PTR [edi+0x8]
.L44038b:
 lea    eax,[esp+0xc]
.L44038f:
 push   eax
.L440390:
 call target_43f250
.L440395:
 lea    ecx,[esp+0x18]
.L440399:
 mov    BYTE PTR [esp+0xa0],0x5
.L4403a1:
 push   ecx
.L4403a2:
 mov    ecx,DWORD PTR [eax]
.L4403a4:
 call target_4427e0
.L4403a9:
 mov    eax,DWORD PTR [esp+0x18]
.L4403ad:
 test   eax,eax
.L4403af:
 je .L4403c3
.L4403b1:
 mov    ecx,DWORD PTR [eax]
.L4403b3:
 mov    ecx,DWORD PTR [ecx+0x4]
.L4403b6:
 {load} add    ecx,eax
.L4403b8:
 dec    DWORD PTR [ecx+0x4]
.L4403bb:
 jne .L4403c3
.L4403bd:
 mov    eax,DWORD PTR [ecx]
.L4403bf:
 push   0x1
.L4403c1:
 call   DWORD PTR [eax]
.L4403c3:
 mov    BYTE PTR [esp+0xa0],0x4
.L4403cb:
 mov    eax,DWORD PTR [esp+0xc]
.L4403cf:
 test   eax,eax
.L4403d1:
 je .L4403e5
.L4403d3:
 mov    ecx,DWORD PTR [eax]
.L4403d5:
 mov    ecx,DWORD PTR [ecx+0x4]
.L4403d8:
 {load} add    ecx,eax
.L4403da:
 dec    DWORD PTR [ecx+0x4]
.L4403dd:
 jne .L4403e5
.L4403df:
 mov    eax,DWORD PTR [ecx]
.L4403e1:
 push   0x1
.L4403e3:
 call   DWORD PTR [eax]
.L4403e5:
 mov    ecx,DWORD PTR [edi+0x8]
.L4403e8:
 lea    eax,[esp+0xc]
.L4403ec:
 push   eax
.L4403ed:
 call target_43f250
.L4403f2:
 mov    eax,DWORD PTR [eax]
.L4403f4:
 mov    eax,DWORD PTR [eax+0x8]
.L4403f7:
 mov    eax,DWORD PTR [eax]
.L4403f9:
 mov    BYTE PTR [eax+0x28],0x1
.L4403fd:
 mov    eax,DWORD PTR [esp+0xc]
.L440401:
 test   eax,eax
.L440403:
 je .L440417
.L440405:
 mov    ecx,DWORD PTR [eax]
.L440407:
 mov    ecx,DWORD PTR [ecx+0x4]
.L44040a:
 {load} add    ecx,eax
.L44040c:
 dec    DWORD PTR [ecx+0x4]
.L44040f:
 jne .L440417
.L440411:
 mov    eax,DWORD PTR [ecx]
.L440413:
 push   0x1
.L440415:
 call   DWORD PTR [eax]
.L440417:
 mov    ecx,DWORD PTR [edi+0x8]
.L44041a:
 lea    eax,[esp+0xc]
.L44041e:
 push   eax
.L44041f:
 call target_43f250
.L440424:
 mov    eax,DWORD PTR [eax]
.L440426:
 mov    eax,DWORD PTR [eax+0x8]
.L440429:
 mov    eax,DWORD PTR [eax]
.L44042b:
 mov    DWORD PTR [eax+0xc],0x3f800000
.L440432:
 mov    eax,DWORD PTR [esp+0xc]
.L440436:
 test   eax,eax
.L440438:
 je .L44044c
.L44043a:
 mov    ecx,DWORD PTR [eax]
.L44043c:
 mov    ecx,DWORD PTR [ecx+0x4]
.L44043f:
 {load} add    ecx,eax
.L440441:
 dec    DWORD PTR [ecx+0x4]
.L440444:
 jne .L44044c
.L440446:
 mov    eax,DWORD PTR [ecx]
.L440448:
 push   0x1
.L44044a:
 call   DWORD PTR [eax]
.L44044c:
 mov    ecx,DWORD PTR [edi+0x8]
.L44044f:
 lea    eax,[esp+0xc]
.L440453:
 push   eax
.L440454:
 call target_43f250
.L440459:
 mov    BYTE PTR [esp+0xa0],0x6
.L440461:
 mov    eax,DWORD PTR [eax]
.L440463:
 push   ecx
.L440464:
 lea    ecx,[esp+0x34]
.L440468:
 push   ecx
.L440469:
 mov    eax,DWORD PTR [eax+0x8]
.L44046c:
 mov    ecx,DWORD PTR [eax]
.L44046e:
 call target_43f070
.L440473:
 mov    BYTE PTR [esp+0xa0],0x4
.L44047b:
 mov    eax,DWORD PTR [esp+0xc]
.L44047f:
 test   eax,eax
.L440481:
 je .L440495
.L440483:
 mov    ecx,DWORD PTR [eax]
.L440485:
 mov    ecx,DWORD PTR [ecx+0x4]
.L440488:
 {load} add    ecx,eax
.L44048a:
 dec    DWORD PTR [ecx+0x4]
.L44048d:
 jne .L440495
.L44048f:
 mov    eax,DWORD PTR [ecx]
.L440491:
 push   0x1
.L440493:
 call   DWORD PTR [eax]
.L440495:
 mov    ecx,DWORD PTR [edi+0x8]
.L440498:
 lea    eax,[esp+0xc]
.L44049c:
 push   eax
.L44049d:
 call target_43f250
.L4404a2:
 mov    eax,DWORD PTR [eax]
.L4404a4:
 mov    eax,DWORD PTR [eax+0x8]
.L4404a7:
 mov    eax,DWORD PTR [eax]
.L4404a9:
 mov    BYTE PTR [eax+0x2a],0x1
.L4404ad:
 mov    eax,DWORD PTR [esp+0xc]
.L4404b1:
 test   eax,eax
.L4404b3:
 je .L4404c7
.L4404b5:
 mov    ecx,DWORD PTR [eax]
.L4404b7:
 mov    ecx,DWORD PTR [ecx+0x4]
.L4404ba:
 {load} add    ecx,eax
.L4404bc:
 dec    DWORD PTR [ecx+0x4]
.L4404bf:
 jne .L4404c7
.L4404c1:
 mov    eax,DWORD PTR [ecx]
.L4404c3:
 push   0x1
.L4404c5:
 call   DWORD PTR [eax]
.L4404c7:
 mov    ecx,DWORD PTR [edi+0x8]
.L4404ca:
 lea    eax,[esp+0xc]
.L4404ce:
 push   eax
.L4404cf:
 call target_43f250
.L4404d4:
 mov    eax,DWORD PTR [eax]
.L4404d6:
 mov    eax,DWORD PTR [eax+0x8]
.L4404d9:
 mov    eax,DWORD PTR [eax]
.L4404db:
 mov    BYTE PTR [eax+0x29],0x1
.L4404df:
 mov    eax,DWORD PTR [esp+0xc]
.L4404e3:
 test   eax,eax
.L4404e5:
 je .L4404f9
.L4404e7:
 mov    ecx,DWORD PTR [eax]
.L4404e9:
 mov    ecx,DWORD PTR [ecx+0x4]
.L4404ec:
 {load} add    ecx,eax
.L4404ee:
 dec    DWORD PTR [ecx+0x4]
.L4404f1:
 jne .L4404f9
.L4404f3:
 mov    eax,DWORD PTR [ecx]
.L4404f5:
 push   0x1
.L4404f7:
 call   DWORD PTR [eax]
.L4404f9:
 mov    ecx,DWORD PTR [edi+0x8]
.L4404fc:
 lea    eax,[esp+0xc]
.L440500:
 push   eax
.L440501:
 call target_43f250
.L440506:
 mov    ecx,DWORD PTR [eax]
.L440508:
 lea    eax,[edi+0x128]
.L44050e:
 mov    DWORD PTR [ecx+0x4],eax
.L440511:
 mov    eax,DWORD PTR [esp+0xc]
.L440515:
 test   eax,eax
.L440517:
 je .L44052b
.L440519:
 mov    ecx,DWORD PTR [eax]
.L44051b:
 mov    ecx,DWORD PTR [ecx+0x4]
.L44051e:
 {load} add    ecx,eax
.L440520:
 dec    DWORD PTR [ecx+0x4]
.L440523:
 jne .L44052b
.L440525:
 mov    eax,DWORD PTR [ecx]
.L440527:
 push   0x1
.L440529:
 call   DWORD PTR [eax]
.L44052b:
 mov    ecx,DWORD PTR [esp+0x1c]
.L44052f:
 lea    esi,[esp+0x20]
.L440533:
 mov    eax,DWORD PTR [edi+0x8]
.L440536:
 push   0x1
.L440538:
 push   esi
.L440539:
 mov    DWORD PTR [esp+0x54],0x0
.L440541:
 lea    esi,[esp+0x54]
.L440545:
 mov    DWORD PTR [esp+0x58],0x0
.L44054d:
 add    eax,0x24
.L440550:
 mov    DWORD PTR [esp+0x5c],0x0
.L440558:
 mov    DWORD PTR [esp+0x28],0x0
.L440560:
 mov    DWORD PTR [esp+0x2c],0x0
.L440568:
 mov    DWORD PTR [esp+0x30],0x0
.L440570:
 mov    edx,DWORD PTR [ecx]
.L440572:
 push   esi
.L440573:
 push   eax
.L440574:
 mov    eax,DWORD PTR [edx+0x40]
.L440577:
 call   eax
.L440579:
 test   al,al
.L44057b:
 je .L440785
.L440581:
 movss  xmm0,DWORD PTR [esp+0x4c]
.L440587:
 movss  xmm1,DWORD PTR [esp+0x50]
.L44058d:
 mulss  xmm0,xmm0
.L440591:
 push   ecx
.L440592:
 mulss  xmm1,xmm1
.L440596:
 addss  xmm1,xmm0
.L44059a:
 movss  xmm0,DWORD PTR [esp+0x58]
.L4405a0:
 mulss  xmm0,xmm0
.L4405a4:
 addss  xmm1,xmm0
.L4405a8:
 movss  DWORD PTR [esp],xmm1
.L4405ad:
 call target_426d60
.L4405b2:
 fmul   DWORD PTR [0xa06508]
.L4405b8:
 lea    ecx,[esp+0x68]
.L4405bc:
 add    esp,0x4
.L4405bf:
 fstp   DWORD PTR [esp+0x18]
.L4405c3:
 call target_422650
.L4405c8:
 movss  xmm0,DWORD PTR [esp+0x18]
.L4405ce:
 lea    eax,[esp+0x34]
.L4405d2:
 movss  xmm2,DWORD PTR [esp+0x20]
.L4405d8:
 lea    ecx,[esp+0x64]
.L4405dc:
 movss  xmm1,DWORD PTR [esp+0x24]
.L4405e2:
 movaps xmm5,xmm0
.L4405e5:
 movaps xmm3,xmm0
.L4405e8:
 mov    DWORD PTR [esp+0x34],0x0
.L4405f0:
 movaps xmm4,xmm0
.L4405f3:
 mov    DWORD PTR [esp+0x38],0x3f800000
.L4405fb:
 movss  xmm0,DWORD PTR [esp+0x28]
.L440601:
 addss  xmm5,xmm2
.L440605:
 addss  xmm3,xmm1
.L440609:
 mov    DWORD PTR [esp+0x3c],0x0
.L440611:
 addss  xmm4,xmm0
.L440615:
 push   eax
.L440616:
 lea    eax,[esp+0x44]
.L44061a:
 addss  xmm5,DWORD PTR [0xc00b2c]
.L440622:
 addss  xmm3,DWORD PTR [0xc00b30]
.L44062a:
 addss  xmm4,DWORD PTR [0xc00b34]
.L440632:
 push   eax
.L440633:
 subss  xmm2,xmm5
.L440637:
 movss  DWORD PTR [esp+0x24],xmm5
.L44063d:
 subss  xmm1,xmm3
.L440641:
 movss  DWORD PTR [esp+0x14],xmm3
.L440647:
 subss  xmm0,xmm4
.L44064b:
 movss  DWORD PTR [esp+0x68],xmm4
.L440651:
 movss  DWORD PTR [esp+0x48],xmm2
.L440657:
 movss  DWORD PTR [esp+0x4c],xmm1
.L44065d:
 movss  DWORD PTR [esp+0x50],xmm0
.L440663:
 call target_4582a0
.L440668:
 mov    eax,DWORD PTR [esp+0x60]
.L44066c:
 movss  xmm1,DWORD PTR [esp+0xc]
.L440672:
 movss  xmm0,DWORD PTR [esp+0x1c]
.L440678:
 unpcklps xmm0,xmm1
.L44067b:
 mov    DWORD PTR [esp+0x90],eax
.L440682:
 mov    eax,DWORD PTR [edi]
.L440684:
 movq   QWORD PTR [esp+0x88],xmm0
.L44068d:
 movdqu xmm0,XMMWORD PTR [esp+0x64]
.L440693:
 mov    eax,DWORD PTR [eax+0x1ac]
.L440699:
 movdqu XMMWORD PTR [eax+0x44],xmm0
.L44069e:
 movdqu xmm0,XMMWORD PTR [esp+0x74]
.L4406a4:
 movdqu XMMWORD PTR [eax+0x54],xmm0
.L4406a9:
 movdqu xmm0,XMMWORD PTR [esp+0x84]
.L4406b2:
 movdqu XMMWORD PTR [eax+0x64],xmm0
.L4406b7:
 mov    ecx,DWORD PTR [edi+0x4]
.L4406ba:
 movq   xmm0,QWORD PTR [esp+0x20]
.L4406c0:
 movq   QWORD PTR [ecx+0x4c],xmm0
.L4406c5:
 mov    eax,DWORD PTR [esp+0x28]
.L4406c9:
 mov    DWORD PTR [ecx+0x54],eax
.L4406cc:
 movss  xmm2,DWORD PTR [esp+0x24]
.L4406d2:
 movss  xmm0,DWORD PTR [esp+0x20]
.L4406d8:
 subss  xmm2,xmm1
.L4406dc:
 subss  xmm0,DWORD PTR [esp+0x1c]
.L4406e2:
 movss  xmm1,DWORD PTR [esp+0x28]
.L4406e8:
 subss  xmm1,DWORD PTR [esp+0x60]
.L4406ee:
 mulss  xmm2,xmm2
.L4406f2:
 mulss  xmm0,xmm0
.L4406f6:
 mulss  xmm1,xmm1
.L4406fa:
 addss  xmm2,xmm0
.L4406fe:
 addss  xmm2,xmm1
.L440702:
 cvtps2pd xmm0,xmm2
.L440705:
 call target_8f8d60
.L44070a:
 cvtsd2ss xmm0,xmm0
.L44070e:
 movss  DWORD PTR [esp+0x1c],xmm0
.L440714:
 movss  xmm2,DWORD PTR [esp+0x18]
.L44071a:
 movaps xmm1,xmm2
.L44071d:
 movaps xmm0,xmm2
.L440720:
 mulss  xmm1,xmm2
.L440724:
 push   ecx
.L440725:
 mulss  xmm0,xmm2
.L440729:
 mulss  xmm2,xmm2
.L44072d:
 addss  xmm1,xmm0
.L440731:
 addss  xmm1,xmm2
.L440735:
 movss  DWORD PTR [esp],xmm1
.L44073a:
 call target_426d60
.L44073f:
 mov    eax,DWORD PTR [edi]
.L440741:
 add    esp,0x4
.L440744:
 movss  xmm0,DWORD PTR [esp+0x1c]
.L44074a:
 fstp   DWORD PTR [esp+0xc]
.L44074e:
 addss  xmm0,DWORD PTR [esp+0xc]
.L440754:
 mov    eax,DWORD PTR [eax+0x1ac]
.L44075a:
 movss  DWORD PTR [eax+0xc],xmm0
.L44075f:
 mov    ecx,DWORD PTR [edi]
.L440761:
 movss  xmm0,DWORD PTR [0xa0680c]
.L440769:
 mov    eax,DWORD PTR [ecx+0x1ac]
.L44076f:
 comiss xmm0,DWORD PTR [eax+0xc]
.L440773:
 jbe .L440865
.L440779:
 mov    DWORD PTR [eax+0xc],0x447a0000
.L440780:
 jmp .L440865
.L440785:
 lea    ecx,[esp+0x64]
.L440789:
 call target_422650
.L44078e:
 movss  xmm0,DWORD PTR [0xc00b2c]
.L440796:
 lea    eax,[esp+0x40]
.L44079a:
 movss  xmm3,DWORD PTR [0xc00b30]
.L4407a2:
 lea    ecx,[esp+0x64]
.L4407a6:
 movss  xmm2,DWORD PTR [0xc00b34]
.L4407ae:
 xorps  xmm4,xmm4
.L4407b1:
 addss  xmm0,xmm4
.L4407b5:
 mov    DWORD PTR [esp+0x40],0x0
.L4407bd:
 addss  xmm3,xmm4
.L4407c1:
 mov    DWORD PTR [esp+0x44],0x3f800000
.L4407c9:
 addss  xmm2,xmm4
.L4407cd:
 mov    DWORD PTR [esp+0x48],0x0
.L4407d5:
 movaps xmm1,xmm4
.L4407d8:
 push   eax
.L4407d9:
 subss  xmm1,xmm0
.L4407dd:
 movq   QWORD PTR [esp+0x10],xmm0
.L4407e3:
 movaps xmm0,xmm4
.L4407e6:
 movss  DWORD PTR [esp+0x20],xmm3
.L4407ec:
 subss  xmm0,xmm3
.L4407f0:
 movss  DWORD PTR [esp+0x64],xmm2
.L4407f6:
 subss  xmm4,xmm2
.L4407fa:
 lea    eax,[esp+0x38]
.L4407fe:
 push   eax
.L4407ff:
 movss  DWORD PTR [esp+0x3c],xmm1
.L440805:
 movss  DWORD PTR [esp+0x40],xmm0
.L44080b:
 movss  DWORD PTR [esp+0x44],xmm4
.L440811:
 call target_4582a0
.L440816:
 mov    eax,DWORD PTR [esp+0x60]
.L44081a:
 movss  xmm0,DWORD PTR [esp+0x1c]
.L440820:
 movq   xmm1,QWORD PTR [esp+0xc]
.L440826:
 mov    DWORD PTR [esp+0x90],eax
.L44082d:
 mov    eax,DWORD PTR [edi]
.L44082f:
 unpcklps xmm1,xmm0
.L440832:
 movdqu xmm0,XMMWORD PTR [esp+0x64]
.L440838:
 mov    eax,DWORD PTR [eax+0x1ac]
.L44083e:
 movq   QWORD PTR [esp+0x88],xmm1
.L440847:
 movdqu XMMWORD PTR [eax+0x44],xmm0
.L44084c:
 movdqu xmm0,XMMWORD PTR [esp+0x74]
.L440852:
 movdqu XMMWORD PTR [eax+0x54],xmm0
.L440857:
 movdqu xmm0,XMMWORD PTR [esp+0x84]
.L440860:
 movdqu XMMWORD PTR [eax+0x64],xmm0
.L440865:
 mov    BYTE PTR [esp+0xa0],0x2
.L44086d:
 mov    esi,DWORD PTR [esp+0x30]
.L440871:
 test   esi,esi
.L440873:
 js .L440898
.L440875:
 call target_4174b0
.L44087a:
 mov    ecx,DWORD PTR [eax+0x4]
.L44087d:
 mov    eax,DWORD PTR [eax+0x28]
.L440880:
 movsx  ecx,WORD PTR [ecx+esi*2]
.L440884:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L440888:
 jne .L440898
.L44088a:
 call target_4174b0
.L44088f:
 push   esi
.L440890:
 lea    ecx,[eax+0x4]
.L440893:
 call target_41c090
.L440898:
 mov    DWORD PTR [esp+0xa0],0xffffffff
.L4408a3:
 mov    esi,DWORD PTR [esp+0x2c]
.L4408a7:
 test   esi,esi
.L4408a9:
 js .L4408ce
.L4408ab:
 call target_417420
.L4408b0:
 mov    ecx,DWORD PTR [eax+0x4]
.L4408b3:
 mov    eax,DWORD PTR [eax+0x28]
.L4408b6:
 movsx  ecx,WORD PTR [ecx+esi*2]
.L4408ba:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L4408be:
 jne .L4408ce
.L4408c0:
 call target_417420
.L4408c5:
 push   esi
.L4408c6:
 lea    ecx,[eax+0x4]
.L4408c9:
 call target_41c090
.L4408ce:
 mov    ecx,DWORD PTR [esp+0x98]
.L4408d5:
 mov    DWORD PTR fs:0x0,ecx
.L4408dc:
 pop    ecx
.L4408dd:
 pop    edi
.L4408de:
 pop    esi
.L4408df:
 {load} mov    esp,ebp
.L4408e1:
 pop    ebp
.L4408e2:
 ret
.equ target_417420,0x417420
.equ target_4174b0,0x4174b0
.equ target_418460,0x418460
.equ target_418790,0x418790
.equ target_41c090,0x41c090
.equ target_422650,0x422650
.equ target_423b70,0x423b70
.equ target_426d60,0x426d60
.equ target_43f070,0x43f070
.equ target_43f0e0,0x43f0e0
.equ target_43f140,0x43f140
.equ target_43f1b0,0x43f1b0
.equ target_43f250,0x43f250
.equ target_4427e0,0x4427e0
.equ target_442bd0,0x442bd0
.equ target_457bb0,0x457bb0
.equ target_4582a0,0x4582a0
.equ target_8f8d60,0x8f8d60
