# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x55b940,0x55bc93); instruction-contiguous extent, padding excluded.
# Input pointer update: reads the cursor through import slots 0x92D528/0x92D534/0x92D570/0x92D5B0,
# subtracts window-object offsets and selects relative/normalized modes from object bytes;
# original vtable call retained. No client/render scaling is added by this reference.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x55b940..0x55bc93
.intel_syntax noprefix
.code32
.text
.global original_input_pointer_update
original_input_pointer_update:
.L55b940:
 push   ebp
.L55b941:
 {load} mov    ebp,esp
.L55b943:
 mov    edx,DWORD PTR [0xbfcc2c]
.L55b949:
 sub    esp,0x24
.L55b94c:
 push   ebx
.L55b94d:
 {load} mov    ebx,ecx
.L55b94f:
 mov    ecx,0x40
.L55b954:
 push   esi
.L55b955:
 push   edi
.L55b956:
 cmp    DWORD PTR [ebx+0x8],0x0
.L55b95a:
 lea    edi,[ebx+0x10d]
.L55b960:
 movdqu xmm0,XMMWORD PTR [ebx+0x248]
.L55b968:
 lea    esi,[ebx+0xd]
.L55b96b:
 sete   al
.L55b96e:
 rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
.L55b970:
 mov    BYTE PTR [ebx+0xc],al
.L55b973:
 lea    esi,[edx+0x40]
.L55b976:
 mov    eax,DWORD PTR [ebx+0x258]
.L55b97c:
 lea    edi,[ebx+0xd]
.L55b97f:
 mov    ecx,0x40
.L55b984:
 rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]
.L55b986:
 movdqu XMMWORD PTR [ebx+0x25c],xmm0
.L55b98e:
 mov    DWORD PTR [ebx+0x26c],eax
.L55b994:
 movdqu xmm0,XMMWORD PTR [edx+0x18]
.L55b999:
 movdqu XMMWORD PTR [ebx+0x248],xmm0
.L55b9a1:
 mov    eax,DWORD PTR [edx+0x28]
.L55b9a4:
 mov    DWORD PTR [ebx+0x258],eax
.L55b9aa:
 xorps  xmm0,xmm0
.L55b9ad:
 mov    eax,DWORD PTR [edx+0x2c]
.L55b9b0:
 mov    DWORD PTR [ebx+0x270],eax
.L55b9b6:
 mov    eax,DWORD PTR [edx+0x30]
.L55b9b9:
 mov    DWORD PTR [ebx+0x274],eax
.L55b9bf:
 movq   QWORD PTR [edx+0x2c],xmm0
.L55b9c4:
 cmp    BYTE PTR [edx+0x140],0x0
.L55b9cb:
 je .L55bba3
.L55b9d1:
 movss  xmm0,DWORD PTR [ebx+0x23c]
.L55b9d9:
 lea    eax,[ebp-0x18]
.L55b9dc:
 mov    esi,DWORD PTR [0xbfcc28]
.L55b9e2:
 movss  DWORD PTR [ebp-0xc],xmm0
.L55b9e7:
 movss  xmm0,DWORD PTR [ebx+0x240]
.L55b9ef:
 push   eax
.L55b9f0:
 movss  DWORD PTR [ebp-0x10],xmm0
.L55b9f5:
 call   DWORD PTR [0x92d570]
.L55b9fb:
 lea    eax,[ebp-0x18]
.L55b9fe:
 push   eax
.L55b9ff:
 push   DWORD PTR [esi+0x4]
.L55ba02:
 call   DWORD PTR [0x92d528]
.L55ba08:
 mov    eax,DWORD PTR [ebp-0x18]
.L55ba0b:
 lea    edx,[ebp-0x20]
.L55ba0e:
 sub    eax,DWORD PTR [esi+0x14]
.L55ba11:
 mov    ecx,DWORD PTR [ebp-0x14]
.L55ba14:
 sub    ecx,DWORD PTR [esi+0x18]
.L55ba17:
 push   0x0
.L55ba19:
 movd   xmm0,eax
.L55ba1d:
 cvtdq2ps xmm0,xmm0
.L55ba20:
 push   edx
.L55ba21:
 movss  DWORD PTR [ebp-0x18],xmm0
.L55ba26:
 mov    eax,DWORD PTR [ebp-0x18]
.L55ba29:
 movd   xmm0,ecx
.L55ba2d:
 cvtdq2ps xmm0,xmm0
.L55ba30:
 mov    DWORD PTR [ebx+0x23c],eax
.L55ba36:
 movss  DWORD PTR [ebp-0x14],xmm0
.L55ba3b:
 mov    eax,DWORD PTR [ebp-0x14]
.L55ba3e:
 mov    DWORD PTR [ebx+0x240],eax
.L55ba44:
 mov    ecx,DWORD PTR [0xc0d408]
.L55ba4a:
 mov    eax,DWORD PTR [ecx]
.L55ba4c:
 call   DWORD PTR [eax+0x10]
.L55ba4f:
 movss  xmm3,DWORD PTR [ebx+0x23c]
.L55ba57:
 xorps  xmm4,xmm4
.L55ba5a:
 comiss xmm3,xmm4
.L55ba5d:
 movss  xmm1,DWORD PTR [ebp-0x1c]
.L55ba62:
 movss  xmm2,DWORD PTR [ebp-0x20]
.L55ba67:
 jb .L55ba87
.L55ba69:
 movss  xmm0,DWORD PTR [ebx+0x240]
.L55ba71:
 comiss xmm0,xmm4
.L55ba74:
 jb .L55ba87
.L55ba76:
 comiss xmm2,xmm3
.L55ba79:
 jbe .L55ba87
.L55ba7b:
 comiss xmm1,xmm0
.L55ba7e:
 jbe .L55ba87
.L55ba80:
 mov    eax,0x1
.L55ba85:
 jmp .L55ba89
.L55ba87:
 {load} xor    eax,eax
.L55ba89:
 cmp    BYTE PTR [ebx+0x246],0x0
.L55ba90:
 mov    BYTE PTR [ebx+0x245],al
.L55ba96:
 je .L55bb1d
.L55ba9c:
 mulss  xmm2,DWORD PTR [0xa06508]
.L55baa4:
 mov    ecx,DWORD PTR [0xbfcc28]
.L55baaa:
 mulss  xmm1,DWORD PTR [0xa06508]
.L55bab2:
 cvttss2si eax,xmm2
.L55bab6:
 movss  DWORD PTR [ebp-0x4],xmm2
.L55babb:
 add    eax,DWORD PTR [ecx+0x14]
.L55babe:
 mov    DWORD PTR [ebp-0x18],eax
.L55bac1:
 cvttss2si eax,xmm1
.L55bac5:
 movss  DWORD PTR [ebp-0x8],xmm1
.L55baca:
 add    eax,DWORD PTR [ecx+0x18]
.L55bacd:
 mov    DWORD PTR [ebp-0x14],eax
.L55bad0:
 lea    eax,[ebp-0x18]
.L55bad3:
 push   eax
.L55bad4:
 push   DWORD PTR [ecx+0x4]
.L55bad7:
 call   DWORD PTR [0x92d534]
.L55badd:
 push   DWORD PTR [ebp-0x14]
.L55bae0:
 push   DWORD PTR [ebp-0x18]
.L55bae3:
 call   DWORD PTR [0x92d5b0]
.L55bae9:
 movss  xmm0,DWORD PTR [ebx+0x23c]
.L55baf1:
 subss  xmm0,DWORD PTR [ebp-0x4]
.L55baf6:
 movss  xmm1,DWORD PTR [ebp-0x1c]
.L55bafb:
 movss  xmm2,DWORD PTR [ebp-0x20]
.L55bb00:
 movss  DWORD PTR [ebx+0x23c],xmm0
.L55bb08:
 movss  xmm0,DWORD PTR [ebx+0x240]
.L55bb10:
 subss  xmm0,DWORD PTR [ebp-0x8]
.L55bb15:
 movss  DWORD PTR [ebx+0x240],xmm0
.L55bb1d:
 cmp    BYTE PTR [ebx+0x247],0x0
.L55bb24:
 je .L55bb5e
.L55bb26:
 divss  xmm2,DWORD PTR [0xa06814]
.L55bb2e:
 movss  xmm0,DWORD PTR [ebx+0x23c]
.L55bb36:
 divss  xmm1,DWORD PTR [0xa06804]
.L55bb3e:
 divss  xmm0,xmm2
.L55bb42:
 movss  DWORD PTR [ebx+0x23c],xmm0
.L55bb4a:
 movss  xmm0,DWORD PTR [ebx+0x240]
.L55bb52:
 divss  xmm0,xmm1
.L55bb56:
 movss  DWORD PTR [ebx+0x240],xmm0
.L55bb5e:
 movss  xmm0,DWORD PTR [ebx+0x23c]
.L55bb66:
 ucomiss xmm0,DWORD PTR [ebp-0xc]
.L55bb6a:
 lahf
.L55bb6b:
 test   ah,0x44
.L55bb6e:
 jp .L55bb94
.L55bb70:
 movss  xmm0,DWORD PTR [ebx+0x240]
.L55bb78:
 ucomiss xmm0,DWORD PTR [ebp-0x10]
.L55bb7c:
 lahf
.L55bb7d:
 test   ah,0x44
.L55bb80:
 jp .L55bb94
.L55bb82:
 mov    eax,0x1
.L55bb87:
 test   al,al
.L55bb89:
 sete   al
.L55bb8c:
 mov    BYTE PTR [ebx+0x244],al
.L55bb92:
 jmp .L55bbc0
.L55bb94:
 {load} xor    eax,eax
.L55bb96:
 test   al,al
.L55bb98:
 sete   al
.L55bb9b:
 mov    BYTE PTR [ebx+0x244],al
.L55bba1:
 jmp .L55bbc0
.L55bba3:
 mov    WORD PTR [ebx+0x244],0x0
.L55bbac:
 mov    DWORD PTR [ebx+0x23c],0xbf800000
.L55bbb6:
 mov    DWORD PTR [ebx+0x240],0xbf800000
.L55bbc0:
 mov    ecx,DWORD PTR [ebx+0x4]
.L55bbc3:
 mov    eax,DWORD PTR [ecx]
.L55bbc5:
 call   DWORD PTR [eax+0x10]
.L55bbc8:
 mov    ecx,DWORD PTR [ebx+0x210]
.L55bbce:
 {load} mov    edx,eax
.L55bbd0:
 cmp    BYTE PTR [ebx+ecx*1+0xd],0x0
.L55bbd5:
 je .L55bbda
.L55bbd7:
 or     edx,0x1
.L55bbda:
 mov    ecx,DWORD PTR [ebx+0x214]
.L55bbe0:
 cmp    BYTE PTR [ebx+ecx*1+0xd],0x0
.L55bbe5:
 je .L55bbea
.L55bbe7:
 or     edx,0x2
.L55bbea:
 mov    eax,DWORD PTR [ebx+0x218]
.L55bbf0:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bbf5:
 je .L55bbfa
.L55bbf7:
 or     edx,0x4
.L55bbfa:
 mov    eax,DWORD PTR [ebx+0x21c]
.L55bc00:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc05:
 je .L55bc0a
.L55bc07:
 or     edx,0x8
.L55bc0a:
 mov    eax,DWORD PTR [ebx+0x220]
.L55bc10:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc15:
 je .L55bc1a
.L55bc17:
 or     edx,0x10
.L55bc1a:
 mov    eax,DWORD PTR [ebx+0x224]
.L55bc20:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc25:
 je .L55bc2a
.L55bc27:
 or     edx,0x20
.L55bc2a:
 mov    eax,DWORD PTR [ebx+0x228]
.L55bc30:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc35:
 je .L55bc3a
.L55bc37:
 or     edx,0x40
.L55bc3a:
 mov    eax,DWORD PTR [ebx+0x22c]
.L55bc40:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc45:
 je .L55bc4d
.L55bc47:
 or     edx,0x80
.L55bc4d:
 mov    eax,DWORD PTR [ebx+0x230]
.L55bc53:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc58:
 je .L55bc60
.L55bc5a:
 or     edx,0x100
.L55bc60:
 mov    eax,DWORD PTR [ebx+0x234]
.L55bc66:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc6b:
 je .L55bc73
.L55bc6d:
 or     edx,0x200
.L55bc73:
 mov    eax,DWORD PTR [ebx+0x238]
.L55bc79:
 cmp    BYTE PTR [ebx+eax*1+0xd],0x0
.L55bc7e:
 mov    eax,DWORD PTR [ebx+0x4]
.L55bc81:
 je .L55bc89
.L55bc83:
 or     edx,0x400
.L55bc89:
 pop    edi
.L55bc8a:
 pop    esi
.L55bc8b:
 mov    DWORD PTR [eax+0x8],edx
.L55bc8e:
 pop    ebx
.L55bc8f:
 {load} mov    esp,ebp
.L55bc91:
 pop    ebp
.L55bc92:
 ret
