# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x577320..0x577535
.intel_syntax noprefix
.code32
.text
.global original_shader_sea_ctor
original_shader_sea_ctor:
.L577320:
 push   ebp
.L577321:
 {load} mov    ebp,esp
.L577323:
 push   0xffffffff
.L577325:
 push   0x907fb6
.L57732a:
 mov    eax,fs:0x0
.L577330:
 push   eax
.L577331:
 push   ecx
.L577332:
 push   esi
.L577333:
 mov    eax,[0xbaabc0]
.L577338:
 {load} xor    eax,ebp
.L57733a:
 push   eax
.L57733b:
 lea    eax,[ebp-0xc]
.L57733e:
 mov    fs:0x0,eax
.L577344:
 {load} mov    esi,ecx
.L577346:
 mov    DWORD PTR [ebp-0x10],esi
.L577349:
 call target_5421b0
.L57734e:
 mov    DWORD PTR [ebp-0x4],0x0
.L577355:
 mov    DWORD PTR [esi],0xa015d0
.L57735b:
 mov    DWORD PTR [esi+0x58],0x0
.L577362:
 mov    DWORD PTR [esi+0x80],0x0
.L57736c:
 mov    DWORD PTR [esi+0x84],0x0
.L577376:
 mov    BYTE PTR [ebp-0x4],0x1
.L57737a:
 mov    ecx,DWORD PTR [0xbfcd04]
.L577380:
 mov    BYTE PTR [esi+0xc8],0x0
.L577387:
 mov    DWORD PTR [esi+0xc0],0x0
.L577391:
 mov    DWORD PTR [esi+0xbc],0x0
.L57739b:
 mov    eax,DWORD PTR [ecx+0x918]
.L5773a1:
 mov    DWORD PTR [esi+0xb8],0x0
.L5773ab:
 mov    DWORD PTR [esi+0xb4],0x0
.L5773b5:
 mov    DWORD PTR [esi+0xac],0x0
.L5773bf:
 mov    DWORD PTR [esi+0xa8],0x0
.L5773c9:
 mov    DWORD PTR [esi+0xa4],0x0
.L5773d3:
 mov    DWORD PTR [esi+0xa0],0x0
.L5773dd:
 mov    DWORD PTR [esi+0x98],0x0
.L5773e7:
 mov    DWORD PTR [esi+0x94],0x0
.L5773f1:
 mov    DWORD PTR [esi+0x90],0x0
.L5773fb:
 mov    DWORD PTR [esi+0x8c],0x0
.L577405:
 mov    DWORD PTR [esi+0xc4],0x3f800000
.L57740f:
 mov    DWORD PTR [esi+0xb0],0x3f800000
.L577419:
 mov    DWORD PTR [esi+0x9c],0x3f800000
.L577423:
 mov    DWORD PTR [esi+0x88],0x3f800000
.L57742d:
 mov    DWORD PTR [esi+0x4],eax
.L577430:
 mov    eax,DWORD PTR [ecx+0x920]
.L577436:
 mov    DWORD PTR [esi+0x8],eax
.L577439:
 mov    eax,DWORD PTR [ecx+0x91c]
.L57743f:
 mov    DWORD PTR [esi+0x10],eax
.L577442:
 mov    eax,DWORD PTR [ecx+0x924]
.L577448:
 mov    DWORD PTR [esi+0x14],eax
.L57744b:
 mov    eax,DWORD PTR [esi+0x10]
.L57744e:
 push   0x9fe740
.L577453:
 push   0x0
.L577455:
 push   eax
.L577456:
 mov    ecx,DWORD PTR [eax]
.L577458:
 call   DWORD PTR [ecx+0x24]
.L57745b:
 mov    DWORD PTR [esi+0x5c],eax
.L57745e:
 mov    eax,DWORD PTR [esi+0x10]
.L577461:
 push   0x9fe764
.L577466:
 push   0x0
.L577468:
 push   eax
.L577469:
 mov    ecx,DWORD PTR [eax]
.L57746b:
 call   DWORD PTR [ecx+0x24]
.L57746e:
 mov    DWORD PTR [esi+0x60],eax
.L577471:
 mov    eax,DWORD PTR [esi+0x14]
.L577474:
 push   0xa0154c
.L577479:
 push   0x0
.L57747b:
 push   eax
.L57747c:
 mov    ecx,DWORD PTR [eax]
.L57747e:
 call   DWORD PTR [ecx+0x24]
.L577481:
 mov    DWORD PTR [esi+0x64],eax
.L577484:
 mov    eax,DWORD PTR [esi+0x14]
.L577487:
 push   0xa0155c
.L57748c:
 push   0x0
.L57748e:
 push   eax
.L57748f:
 mov    ecx,DWORD PTR [eax]
.L577491:
 call   DWORD PTR [ecx+0x24]
.L577494:
 mov    DWORD PTR [esi+0x74],eax
.L577497:
 mov    eax,DWORD PTR [esi+0x10]
.L57749a:
 push   0xa01538
.L57749f:
 push   0x0
.L5774a1:
 push   eax
.L5774a2:
 mov    ecx,DWORD PTR [eax]
.L5774a4:
 call   DWORD PTR [ecx+0x24]
.L5774a7:
 mov    DWORD PTR [esi+0x68],eax
.L5774aa:
 mov    eax,DWORD PTR [esi+0x10]
.L5774ad:
 push   0xa01540
.L5774b2:
 push   0x0
.L5774b4:
 push   eax
.L5774b5:
 mov    ecx,DWORD PTR [eax]
.L5774b7:
 call   DWORD PTR [ecx+0x24]
.L5774ba:
 mov    DWORD PTR [esi+0x70],eax
.L5774bd:
 mov    eax,DWORD PTR [esi+0x10]
.L5774c0:
 push   0xa0151c
.L5774c5:
 push   0x0
.L5774c7:
 mov    ecx,DWORD PTR [eax]
.L5774c9:
 push   eax
.L5774ca:
 call   DWORD PTR [ecx+0x24]
.L5774cd:
 mov    DWORD PTR [esi+0x6c],eax
.L5774d0:
 mov    eax,DWORD PTR [esi+0x14]
.L5774d3:
 push   0xa00028
.L5774d8:
 push   0x0
.L5774da:
 push   eax
.L5774db:
 mov    ecx,DWORD PTR [eax]
.L5774dd:
 call   DWORD PTR [ecx+0x24]
.L5774e0:
 mov    DWORD PTR [esi+0x3c],eax
.L5774e3:
 mov    eax,DWORD PTR [esi+0x14]
.L5774e6:
 push   0x9fffd0
.L5774eb:
 push   0x0
.L5774ed:
 push   eax
.L5774ee:
 mov    ecx,DWORD PTR [eax]
.L5774f0:
 call   DWORD PTR [ecx+0x24]
.L5774f3:
 mov    DWORD PTR [esi+0x44],eax
.L5774f6:
 mov    eax,DWORD PTR [esi+0x10]
.L5774f9:
 push   0xa0152c
.L5774fe:
 push   0x0
.L577500:
 push   eax
.L577501:
 mov    ecx,DWORD PTR [eax]
.L577503:
 call   DWORD PTR [ecx+0x24]
.L577506:
 mov    DWORD PTR [esi+0x78],eax
.L577509:
 mov    eax,DWORD PTR [esi+0x10]
.L57750c:
 push   0xa014dc
.L577511:
 push   0x0
.L577513:
 push   eax
.L577514:
 mov    ecx,DWORD PTR [eax]
.L577516:
 call   DWORD PTR [ecx+0x24]
.L577519:
 {load} mov    ecx,esi
.L57751b:
 mov    DWORD PTR [esi+0x7c],eax
.L57751e:
 call target_542230
.L577523:
 {load} mov    eax,esi
.L577525:
 mov    ecx,DWORD PTR [ebp-0xc]
.L577528:
 mov    DWORD PTR fs:0x0,ecx
.L57752f:
 pop    ecx
.L577530:
 pop    esi
.L577531:
 {load} mov    esp,ebp
.L577533:
 pop    ebp
.L577534:
 ret
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
