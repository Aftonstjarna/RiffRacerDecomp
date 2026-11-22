# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x48b8f0,0x48bbc5); instruction-contiguous extent, padding excluded.
# UI sprite-definition apply helper called by the non-null path of sprite set-definition at 0x48830:
# SEH frame, calls 0x41F140, 0x41F280, 0x41F500, 0x426CF0 and 0x454F90; reuses the sprites
# created by the definition routine. No replacement assets or behavior are introduced.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x48b8f0..0x48bbc5
.intel_syntax noprefix
.code32
.text
.global original_ui_sprite_definition_apply
original_ui_sprite_definition_apply:
.L48b8f0:
 push   ebp
.L48b8f1:
 {load} mov    ebp,esp
.L48b8f3:
 push   0xffffffff
.L48b8f5:
 push   0x901618
.L48b8fa:
 mov    eax,fs:0x0
.L48b900:
 push   eax
.L48b901:
 sub    esp,0x10
.L48b904:
 push   ebx
.L48b905:
 push   esi
.L48b906:
 push   edi
.L48b907:
 mov    eax,[0xbaabc0]
.L48b90c:
 {load} xor    eax,ebp
.L48b90e:
 push   eax
.L48b90f:
 lea    eax,[ebp-0xc]
.L48b912:
 mov    fs:0x0,eax
.L48b918:
 {load} mov    esi,ecx
.L48b91a:
 mov    DWORD PTR [ebp-0x18],esi
.L48b91d:
 mov    DWORD PTR [ebp-0x4],0x0
.L48b924:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48b927:
 push   esi
.L48b928:
 call target_454f90
.L48b92d:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48b930:
 lea    eax,[esi+0x4]
.L48b933:
 push   eax
.L48b934:
 call target_455010
.L48b939:
 cmp    BYTE PTR [esi+0x20],0x0
.L48b93d:
 je .L48ba69
.L48b943:
 movss  xmm0,DWORD PTR [esi+0x10]
.L48b948:
 lea    ecx,[esi+0x10]
.L48b94b:
 comiss xmm0,DWORD PTR [0xa063ec]
.L48b952:
 jb .L48b961
.L48b954:
 lea    eax,[esi+0x18]
.L48b957:
 push   eax
.L48b958:
 push   ecx
.L48b959:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48b95c:
 call target_41f280
.L48b961:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48b964:
 xorps  xmm0,xmm0
.L48b967:
 mov    edi,DWORD PTR [esi+0x24]
.L48b96a:
 {load} mov    eax,edi
.L48b96c:
 mov    edx,DWORD PTR [esi+0x28]
.L48b96f:
 shr    eax,0x1f
.L48b972:
 comiss xmm0,DWORD PTR [ecx+0x160]
.L48b979:
 movd   xmm0,edi
.L48b97d:
 cvtdq2pd xmm0,xmm0
.L48b981:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L48b98a:
 {load} mov    eax,edx
.L48b98c:
 jbe .L48b9ab
.L48b98e:
 movss  xmm2,DWORD PTR [0xa06558]
.L48b996:
 cvtpd2ps xmm1,xmm0
.L48b99a:
 movaps xmm0,xmm2
.L48b99d:
 divss  xmm0,xmm1
.L48b9a1:
 movss  DWORD PTR [ecx+0xfc],xmm0
.L48b9a9:
 jmp .L48b9db
.L48b9ab:
 movss  xmm1,DWORD PTR [ecx+0x168]
.L48b9b3:
 subss  xmm1,DWORD PTR [ecx+0x160]
.L48b9bb:
 cvtpd2ps xmm0,xmm0
.L48b9bf:
 movss  xmm2,DWORD PTR [ecx+0x16c]
.L48b9c7:
 divss  xmm1,xmm0
.L48b9cb:
 subss  xmm2,DWORD PTR [ecx+0x164]
.L48b9d3:
 movss  DWORD PTR [ecx+0xfc],xmm1
.L48b9db:
 movd   xmm0,edx
.L48b9df:
 cvtdq2pd xmm0,xmm0
.L48b9e3:
 shr    eax,0x1f
.L48b9e6:
 mov    DWORD PTR [ecx+0x104],edi
.L48b9ec:
 mov    DWORD PTR [ecx+0x108],edx
.L48b9f2:
 push   0x0
.L48b9f4:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L48b9fd:
 cvtpd2ps xmm0,xmm0
.L48ba01:
 divss  xmm2,xmm0
.L48ba05:
 movss  xmm0,DWORD PTR [ecx+0xfc]
.L48ba0d:
 movss  DWORD PTR [ecx+0x100],xmm2
.L48ba15:
 movss  xmm1,xmm2
.L48ba19:
 movss  DWORD PTR [ecx+0x78],xmm0
.L48ba1e:
 movss  DWORD PTR [ecx+0x7c],xmm1
.L48ba23:
 or     DWORD PTR [ecx+0x170],0x8020
.L48ba2d:
 movss  xmm0,DWORD PTR [esi+0x34]
.L48ba32:
 mov    edi,DWORD PTR [esi+0x30]
.L48ba35:
 mov    ebx,DWORD PTR [ebp+0x8]
.L48ba38:
 {load} mov    ecx,ebx
.L48ba3a:
 mov    esi,DWORD PTR [esi+0x2c]
.L48ba3d:
 push   esi
.L48ba3e:
 movss  DWORD PTR [ebp-0x10],xmm0
.L48ba43:
 call target_41f140
.L48ba48:
 movss  xmm0,DWORD PTR [ebp-0x10]
.L48ba4d:
 mov    DWORD PTR [ebx+0x114],esi
.L48ba53:
 mov    esi,DWORD PTR [ebp-0x18]
.L48ba56:
 mov    DWORD PTR [ebx+0x118],edi
.L48ba5c:
 movss  DWORD PTR [ebx+0x11c],xmm0
.L48ba64:
 jmp .L48bb83
.L48ba69:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48ba6c:
 movss  xmm1,DWORD PTR [esi+0x24]
.L48ba71:
 movss  xmm2,DWORD PTR [esi+0x28]
.L48ba76:
 movss  DWORD PTR [ebp-0x1c],xmm1
.L48ba7b:
 movss  xmm0,DWORD PTR [ecx+0x80]
.L48ba83:
 ucomiss xmm0,xmm1
.L48ba86:
 movss  DWORD PTR [ebp-0x18],xmm2
.L48ba8b:
 lahf
.L48ba8c:
 test   ah,0x44
.L48ba8f:
 jp .L48baa2
.L48ba91:
 movss  xmm0,DWORD PTR [ecx+0x84]
.L48ba99:
 ucomiss xmm0,xmm2
.L48ba9c:
 lahf
.L48ba9d:
 test   ah,0x44
.L48baa0:
 jnp .L48baa9
.L48baa2:
 or     DWORD PTR [ecx+0x170],0x40
.L48baa9:
 mov    eax,DWORD PTR [ebp-0x1c]
.L48baac:
 mov    DWORD PTR [ecx+0x80],eax
.L48bab2:
 mov    eax,DWORD PTR [ebp-0x18]
.L48bab5:
 mov    DWORD PTR [ecx+0x84],eax
.L48babb:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48babe:
 movss  xmm1,DWORD PTR [esi+0x2c]
.L48bac3:
 movss  xmm2,DWORD PTR [esi+0x30]
.L48bac8:
 movss  DWORD PTR [ebp-0x1c],xmm1
.L48bacd:
 movss  xmm0,DWORD PTR [ecx+0x88]
.L48bad5:
 ucomiss xmm0,xmm1
.L48bad8:
 movss  DWORD PTR [ebp-0x18],xmm2
.L48badd:
 lahf
.L48bade:
 test   ah,0x44
.L48bae1:
 jp .L48baf4
.L48bae3:
 movss  xmm0,DWORD PTR [ecx+0x8c]
.L48baeb:
 ucomiss xmm0,xmm2
.L48baee:
 lahf
.L48baef:
 test   ah,0x44
.L48baf2:
 jnp .L48bafe
.L48baf4:
 or     DWORD PTR [ecx+0x170],0x80
.L48bafe:
 mov    eax,DWORD PTR [ebp-0x1c]
.L48bb01:
 mov    DWORD PTR [ecx+0x88],eax
.L48bb07:
 mov    eax,DWORD PTR [ebp-0x18]
.L48bb0a:
 mov    DWORD PTR [ecx+0x8c],eax
.L48bb10:
 movss  xmm0,DWORD PTR [esi+0x24]
.L48bb15:
 ucomiss xmm0,DWORD PTR [esi+0x2c]
.L48bb19:
 lahf
.L48bb1a:
 test   ah,0x44
.L48bb1d:
 jnp .L48bb23
.L48bb1f:
 mov    al,0x1
.L48bb21:
 jmp .L48bb25
.L48bb23:
 {load} xor    al,al
.L48bb25:
 mov    ecx,DWORD PTR [ebp+0x8]
.L48bb28:
 push   eax
.L48bb29:
 call target_41f500
.L48bb2e:
 movss  xmm0,DWORD PTR [esi+0x30]
.L48bb33:
 subss  xmm0,DWORD PTR [esi+0x28]
.L48bb38:
 push   ecx
.L48bb39:
 movss  DWORD PTR [esp],xmm0
.L48bb3e:
 call target_426cf0
.L48bb43:
 movss  xmm0,DWORD PTR [esi+0x2c]
.L48bb48:
 subss  xmm0,DWORD PTR [esi+0x24]
.L48bb4d:
 fstp   DWORD PTR [ebp-0x18]
.L48bb50:
 movss  DWORD PTR [esp],xmm0
.L48bb55:
 call target_426cf0
.L48bb5a:
 mov    edx,DWORD PTR [ebp+0x8]
.L48bb5d:
 add    esp,0x4
.L48bb60:
 movss  xmm0,DWORD PTR [ebp-0x18]
.L48bb65:
 fstp   DWORD PTR [ebp-0x14]
.L48bb68:
 mov    eax,DWORD PTR [ebp-0x14]
.L48bb6b:
 mov    DWORD PTR [edx+0x78],eax
.L48bb6e:
 mov    eax,DWORD PTR [ebp+0x8]
.L48bb71:
 or     DWORD PTR [edx+0x170],0x20
.L48bb78:
 movss  DWORD PTR [ebp-0x10],xmm0
.L48bb7d:
 mov    ecx,DWORD PTR [ebp-0x10]
.L48bb80:
 mov    DWORD PTR [eax+0x7c],ecx
.L48bb83:
 cmp    BYTE PTR [esi+0x21],0x0
.L48bb87:
 je .L48bb93
.L48bb89:
 mov    eax,DWORD PTR [ebp+0x8]
.L48bb8c:
 mov    BYTE PTR [eax+0xe3],0x1
.L48bb93:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L48bb9a:
 mov    eax,DWORD PTR [ebp+0x8]
.L48bb9d:
 test   eax,eax
.L48bb9f:
 je .L48bbb3
.L48bba1:
 mov    ecx,DWORD PTR [eax]
.L48bba3:
 mov    ecx,DWORD PTR [ecx+0x4]
.L48bba6:
 {load} add    ecx,eax
.L48bba8:
 dec    DWORD PTR [ecx+0x4]
.L48bbab:
 jne .L48bbb3
.L48bbad:
 mov    eax,DWORD PTR [ecx]
.L48bbaf:
 push   0x1
.L48bbb1:
 call   DWORD PTR [eax]
.L48bbb3:
 mov    ecx,DWORD PTR [ebp-0xc]
.L48bbb6:
 mov    DWORD PTR fs:0x0,ecx
.L48bbbd:
 pop    ecx
.L48bbbe:
 pop    edi
.L48bbbf:
 pop    esi
.L48bbc0:
 pop    ebx
.L48bbc1:
 {load} mov    esp,ebp
.L48bbc3:
 pop    ebp
.L48bbc4:
 ret
.equ target_41f140,0x41f140
.equ target_41f280,0x41f280
.equ target_41f500,0x41f500
.equ target_426cf0,0x426cf0
.equ target_454f90,0x454f90
.equ target_455010,0x455010
