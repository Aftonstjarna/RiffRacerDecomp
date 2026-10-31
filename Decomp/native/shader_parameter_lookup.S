# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x542340..0x5423d5
.intel_syntax noprefix
.code32
.text
.global original_shader_parameter_lookup
original_shader_parameter_lookup:
.L542340:
 push   ebp
.L542341:
 {load} mov    ebp,esp
.L542343:
 sub    esp,0x3c
.L542346:
 push   ebx
.L542347:
 push   esi
.L542348:
 push   edi
.L542349:
 mov    edi,DWORD PTR [ebp+0x8]
.L54234c:
 test   edi,edi
.L54234e:
 je .L5423bf
.L542350:
 mov    eax,DWORD PTR [edi]
.L542352:
 lea    ecx,[ebp-0xc]
.L542355:
 push   ecx
.L542356:
 push   edi
.L542357:
 call   DWORD PTR [eax+0x14]
.L54235a:
 test   eax,eax
.L54235c:
 jne .L5423bf
.L54235e:
 {load} xor    esi,esi
.L542360:
 cmp    DWORD PTR [ebp-0x4],esi
.L542363:
 jbe .L5423bf
.L542365:
 mov    eax,DWORD PTR [edi]
.L542367:
 push   esi
.L542368:
 push   0x0
.L54236a:
 push   edi
.L54236b:
 mov    DWORD PTR [ebp+0x8],0x1
.L542372:
 call   DWORD PTR [eax+0x20]
.L542375:
 {load} mov    ebx,eax
.L542377:
 test   ebx,ebx
.L542379:
 je .L5423b9
.L54237b:
 mov    ecx,DWORD PTR [edi]
.L54237d:
 lea    eax,[ebp+0x8]
.L542380:
 push   eax
.L542381:
 lea    eax,[ebp-0x3c]
.L542384:
 push   eax
.L542385:
 push   ebx
.L542386:
 push   edi
.L542387:
 call   DWORD PTR [ecx+0x18]
.L54238a:
 mov    eax,DWORD PTR [ebp+0xc]
.L54238d:
 mov    ecx,DWORD PTR [ebp-0x3c]
.L542390:
 mov    dl,BYTE PTR [ecx]
.L542392:
 cmp    dl,BYTE PTR [eax]
.L542394:
 jne .L5423b0
.L542396:
 test   dl,dl
.L542398:
 je .L5423ac
.L54239a:
 mov    dl,BYTE PTR [ecx+0x1]
.L54239d:
 cmp    dl,BYTE PTR [eax+0x1]
.L5423a0:
 jne .L5423b0
.L5423a2:
 add    ecx,0x2
.L5423a5:
 add    eax,0x2
.L5423a8:
 test   dl,dl
.L5423aa:
 jne .L542390
.L5423ac:
 {load} xor    eax,eax
.L5423ae:
 jmp .L5423b5
.L5423b0:
 {load} sbb    eax,eax
.L5423b2:
 or     eax,0x1
.L5423b5:
 test   eax,eax
.L5423b7:
 je .L5423ca
.L5423b9:
 inc    esi
.L5423ba:
 cmp    esi,DWORD PTR [ebp-0x4]
.L5423bd:
 jb .L542365
.L5423bf:
 {load} xor    eax,eax
.L5423c1:
 pop    edi
.L5423c2:
 pop    esi
.L5423c3:
 pop    ebx
.L5423c4:
 {load} mov    esp,ebp
.L5423c6:
 pop    ebp
.L5423c7:
 ret    0x8
.L5423ca:
 pop    edi
.L5423cb:
 pop    esi
.L5423cc:
 {load} mov    eax,ebx
.L5423ce:
 pop    ebx
.L5423cf:
 {load} mov    esp,ebp
.L5423d1:
 pop    ebp
.L5423d2:
 ret    0x8
