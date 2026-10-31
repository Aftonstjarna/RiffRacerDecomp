# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x578350..0x5784e7
.intel_syntax noprefix
.code32
.text
.global original_shader_carglass_ctor
original_shader_carglass_ctor:
.L578350:
 push   ebp
.L578351:
 {load} mov    ebp,esp
.L578353:
 push   0xffffffff
.L578355:
 push   0x9080c6
.L57835a:
 mov    eax,fs:0x0
.L578360:
 push   eax
.L578361:
 push   ecx
.L578362:
 push   esi
.L578363:
 mov    eax,[0xbaabc0]
.L578368:
 {load} xor    eax,ebp
.L57836a:
 push   eax
.L57836b:
 lea    eax,[ebp-0xc]
.L57836e:
 mov    fs:0x0,eax
.L578374:
 {load} mov    esi,ecx
.L578376:
 mov    DWORD PTR [ebp-0x10],esi
.L578379:
 call target_5421b0
.L57837e:
 mov    al,BYTE PTR [ebp+0x8]
.L578381:
 mov    DWORD PTR [ebp-0x4],0x0
.L578388:
 mov    BYTE PTR [esi+0x58],al
.L57838b:
 mov    al,BYTE PTR [ebp+0xc]
.L57838e:
 mov    DWORD PTR [esi],0xa016d8
.L578394:
 mov    BYTE PTR [esi+0x59],al
.L578397:
 mov    DWORD PTR [esi+0x5c],0x0
.L57839e:
 mov    DWORD PTR [esi+0xb4],0x0
.L5783a8:
 mov    BYTE PTR [ebp-0x4],0x1
.L5783ac:
 mov    ecx,DWORD PTR [0xbfcd04]
.L5783b2:
 mov    DWORD PTR [esi+0xac],0x0
.L5783bc:
 mov    DWORD PTR [esi+0xa8],0x0
.L5783c6:
 mov    DWORD PTR [esi+0xa4],0x0
.L5783d0:
 mov    eax,DWORD PTR [ecx+0x8d8]
.L5783d6:
 mov    DWORD PTR [esi+0xa0],0x0
.L5783e0:
 mov    DWORD PTR [esi+0x98],0x0
.L5783ea:
 mov    DWORD PTR [esi+0x94],0x0
.L5783f4:
 mov    DWORD PTR [esi+0x90],0x0
.L5783fe:
 mov    DWORD PTR [esi+0x8c],0x0
.L578408:
 mov    DWORD PTR [esi+0x84],0x0
.L578412:
 mov    DWORD PTR [esi+0x80],0x0
.L57841c:
 mov    DWORD PTR [esi+0x7c],0x0
.L578423:
 mov    DWORD PTR [esi+0x78],0x0
.L57842a:
 mov    DWORD PTR [esi+0xb0],0x3f800000
.L578434:
 mov    DWORD PTR [esi+0x9c],0x3f800000
.L57843e:
 mov    DWORD PTR [esi+0x88],0x3f800000
.L578448:
 mov    DWORD PTR [esi+0x74],0x3f800000
.L57844f:
 mov    DWORD PTR [esi+0x4],eax
.L578452:
 mov    eax,DWORD PTR [ecx+0x8e0]
.L578458:
 mov    DWORD PTR [esi+0x8],eax
.L57845b:
 mov    eax,DWORD PTR [ecx+0x8dc]
.L578461:
 mov    DWORD PTR [esi+0x10],eax
.L578464:
 mov    eax,DWORD PTR [ecx+0x8e4]
.L57846a:
 mov    DWORD PTR [esi+0x14],eax
.L57846d:
 mov    eax,DWORD PTR [esi+0x10]
.L578470:
 push   0x9fe740
.L578475:
 push   0x0
.L578477:
 push   eax
.L578478:
 mov    ecx,DWORD PTR [eax]
.L57847a:
 call   DWORD PTR [ecx+0x24]
.L57847d:
 mov    DWORD PTR [esi+0x60],eax
.L578480:
 mov    eax,DWORD PTR [esi+0x10]
.L578483:
 push   0xa01690
.L578488:
 push   0x0
.L57848a:
 push   eax
.L57848b:
 mov    ecx,DWORD PTR [eax]
.L57848d:
 call   DWORD PTR [ecx+0x24]
.L578490:
 mov    DWORD PTR [esi+0x64],eax
.L578493:
 mov    eax,DWORD PTR [esi+0x10]
.L578496:
 push   0xa0169c
.L57849b:
 push   0x0
.L57849d:
 push   eax
.L57849e:
 mov    ecx,DWORD PTR [eax]
.L5784a0:
 call   DWORD PTR [ecx+0x24]
.L5784a3:
 mov    DWORD PTR [esi+0x68],eax
.L5784a6:
 mov    eax,DWORD PTR [esi+0x14]
.L5784a9:
 push   0xa016bc
.L5784ae:
 push   0x0
.L5784b0:
 push   eax
.L5784b1:
 mov    ecx,DWORD PTR [eax]
.L5784b3:
 call   DWORD PTR [ecx+0x24]
.L5784b6:
 mov    DWORD PTR [esi+0x6c],eax
.L5784b9:
 mov    eax,DWORD PTR [esi+0x14]
.L5784bc:
 push   0xa016c4
.L5784c1:
 push   0x0
.L5784c3:
 push   eax
.L5784c4:
 mov    ecx,DWORD PTR [eax]
.L5784c6:
 call   DWORD PTR [ecx+0x24]
.L5784c9:
 {load} mov    ecx,esi
.L5784cb:
 mov    DWORD PTR [esi+0x70],eax
.L5784ce:
 call target_542230
.L5784d3:
 {load} mov    eax,esi
.L5784d5:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5784d8:
 mov    DWORD PTR fs:0x0,ecx
.L5784df:
 pop    ecx
.L5784e0:
 pop    esi
.L5784e1:
 {load} mov    esp,ebp
.L5784e3:
 pop    ebp
.L5784e4:
 ret    0x8
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
