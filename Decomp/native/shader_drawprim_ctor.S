# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x5675a0..0x5676e7
.intel_syntax noprefix
.code32
.text
.global original_shader_drawprim_ctor
original_shader_drawprim_ctor:
.L5675a0:
 push   ebp
.L5675a1:
 {load} mov    ebp,esp
.L5675a3:
 push   0xffffffff
.L5675a5:
 push   0x905468
.L5675aa:
 mov    eax,fs:0x0
.L5675b0:
 push   eax
.L5675b1:
 sub    esp,0x8
.L5675b4:
 push   edi
.L5675b5:
 mov    eax,[0xbaabc0]
.L5675ba:
 {load} xor    eax,ebp
.L5675bc:
 push   eax
.L5675bd:
 lea    eax,[ebp-0xc]
.L5675c0:
 mov    fs:0x0,eax
.L5675c6:
 {load} mov    edi,ecx
.L5675c8:
 mov    DWORD PTR [ebp-0x10],edi
.L5675cb:
 call target_5421b0
.L5675d0:
 mov    ecx,DWORD PTR [ebp+0x8]
.L5675d3:
 mov    DWORD PTR [ebp-0x4],0x0
.L5675da:
 shl    ecx,0x4
.L5675dd:
 add    ecx,DWORD PTR [0xbfcd04]
.L5675e3:
 mov    DWORD PTR [edi],0xa00cd4
.L5675e9:
 push   0x9fe740
.L5675ee:
 mov    eax,DWORD PTR [ecx+0x8]
.L5675f1:
 mov    DWORD PTR [edi+0x4],eax
.L5675f4:
 mov    eax,DWORD PTR [ecx+0x10]
.L5675f7:
 mov    DWORD PTR [edi+0x8],eax
.L5675fa:
 mov    eax,DWORD PTR [ecx+0xc]
.L5675fd:
 mov    DWORD PTR [edi+0x10],eax
.L567600:
 mov    eax,DWORD PTR [ecx+0x14]
.L567603:
 push   DWORD PTR [edi+0x10]
.L567606:
 mov    DWORD PTR [edi+0x14],eax
.L567609:
 call target_542340
.L56760e:
 push   0x9fe734
.L567613:
 push   DWORD PTR [edi+0x10]
.L567616:
 mov    DWORD PTR [edi+0x9c],eax
.L56761c:
 call target_542340
.L567621:
 push   0x9fe764
.L567626:
 push   DWORD PTR [edi+0x10]
.L567629:
 mov    DWORD PTR [edi+0x98],eax
.L56762f:
 call target_542340
.L567634:
 push   0xa00c60
.L567639:
 push   DWORD PTR [edi+0x14]
.L56763c:
 mov    DWORD PTR [edi+0xa0],eax
.L567642:
 call target_542340
.L567647:
 push   0xa00c6c
.L56764c:
 push   DWORD PTR [edi+0x14]
.L56764f:
 mov    DWORD PTR [edi+0xa4],eax
.L567655:
 call target_542340
.L56765a:
 push   0xa00cb0
.L56765f:
 push   DWORD PTR [edi+0x14]
.L567662:
 mov    DWORD PTR [edi+0xa8],eax
.L567668:
 call target_542340
.L56766d:
 push   0xa00cbc
.L567672:
 push   DWORD PTR [edi+0x14]
.L567675:
 mov    DWORD PTR [edi+0xac],eax
.L56767b:
 call target_542340
.L567680:
 push   0xa00c98
.L567685:
 push   DWORD PTR [edi+0x14]
.L567688:
 mov    DWORD PTR [edi+0xb0],eax
.L56768e:
 call target_542340
.L567693:
 push   0xa00ca4
.L567698:
 push   DWORD PTR [edi+0x14]
.L56769b:
 mov    DWORD PTR [edi+0xb8],eax
.L5676a1:
 call target_542340
.L5676a6:
 cmp    DWORD PTR [ebp+0x8],0x11
.L5676aa:
 push   0xa00c90
.L5676af:
 push   DWORD PTR [edi+0x14]
.L5676b2:
 mov    DWORD PTR [edi+0xbc],eax
.L5676b8:
 sete   al
.L5676bb:
 mov    BYTE PTR [edi+0xc0],al
.L5676c1:
 call target_542340
.L5676c6:
 {load} mov    ecx,edi
.L5676c8:
 mov    DWORD PTR [edi+0xb4],eax
.L5676ce:
 call target_542230
.L5676d3:
 {load} mov    eax,edi
.L5676d5:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5676d8:
 mov    DWORD PTR fs:0x0,ecx
.L5676df:
 pop    ecx
.L5676e0:
 pop    edi
.L5676e1:
 {load} mov    esp,ebp
.L5676e3:
 pop    ebp
.L5676e4:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
