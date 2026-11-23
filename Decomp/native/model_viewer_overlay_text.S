# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x43f800,0x43fc5c); instruction-contiguous extent, INT3 padding excluded.
# Model viewer overlay formatter: references the original Model Viewer, Model, Bounds and AUX1 bone-name literals and preserves the formatting/state sequence. Called from the application worker; visual behavior is not claimed.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x43f800..0x43fc5c
.intel_syntax noprefix
.code32
.text
.global original_model_viewer_overlay_text
original_model_viewer_overlay_text:
.L43f800:
 push   ebp
.L43f801:
 {load} mov    ebp,esp
.L43f803:
 push   0xffffffff
.L43f805:
 push   0x8fefe8
.L43f80a:
 mov    eax,fs:0x0
.L43f810:
 push   eax
.L43f811:
 sub    esp,0x40
.L43f814:
 push   ebx
.L43f815:
 push   esi
.L43f816:
 push   edi
.L43f817:
 mov    eax,[0xbaabc0]
.L43f81c:
 {load} xor    eax,ebp
.L43f81e:
 push   eax
.L43f81f:
 lea    eax,[ebp-0xc]
.L43f822:
 mov    fs:0x0,eax
.L43f828:
 {load} mov    ebx,ecx
.L43f82a:
 movd   xmm0,DWORD PTR [ebp+0x8]
.L43f82f:
 mov    edi,DWORD PTR [0xc0d408]
.L43f835:
 cvtdq2ps xmm0,xmm0
.L43f838:
 mov    DWORD PTR [ebp-0x1c],edi
.L43f83b:
 mulss  xmm0,xmm2
.L43f83f:
 movss  DWORD PTR [ebx+0x6c],xmm0
.L43f844:
 call target_43fc60
.L43f849:
 cmp    DWORD PTR [ebx+0x8],0x0
.L43f84d:
 je .L43fc48
.L43f853:
 cmp    BYTE PTR [ebx+0x138],0x0
.L43f85a:
 jne .L43f973
.L43f860:
 mov    eax,DWORD PTR [edi]
.L43f862:
 push   0x9f9a58
.L43f867:
 push   0xa
.L43f869:
 push   0x2
.L43f86b:
 push   0x2
.L43f86d:
 push   edi
.L43f86e:
 call   DWORD PTR [eax+0xc0]
.L43f874:
 mov    eax,DWORD PTR [ebx+0x8]
.L43f877:
 lea    ecx,[ebp-0x38]
.L43f87a:
 mov    edx,DWORD PTR [edi]
.L43f87c:
 add    esp,0x14
.L43f87f:
 add    eax,0x24
.L43f882:
 mov    DWORD PTR [ebp-0x2c],0x0
.L43f889:
 mov    DWORD PTR [ebp-0x28],0x0
.L43f890:
 mov    DWORD PTR [ebp-0x24],0x0
.L43f897:
 push   0x1
.L43f899:
 push   ecx
.L43f89a:
 lea    ecx,[ebp-0x2c]
.L43f89d:
 mov    DWORD PTR [ebp-0x38],0x0
.L43f8a4:
 push   ecx
.L43f8a5:
 push   eax
.L43f8a6:
 mov    eax,DWORD PTR [edx+0x40]
.L43f8a9:
 {load} mov    ecx,edi
.L43f8ab:
 mov    DWORD PTR [ebp-0x34],0x0
.L43f8b2:
 mov    DWORD PTR [ebp-0x30],0x0
.L43f8b9:
 call   eax
.L43f8bb:
 test   al,al
.L43f8bd:
 je .L43f95c
.L43f8c3:
 mov    ecx,DWORD PTR [ebx+0x8]
.L43f8c6:
 mov    esi,DWORD PTR [edi]
.L43f8c8:
 add    ecx,0x24
.L43f8cb:
 call target_418540
.L43f8d0:
 push   eax
.L43f8d1:
 push   0x9f9a68
.L43f8d6:
 push   0xd
.L43f8d8:
 push   0x4
.L43f8da:
 push   0x2
.L43f8dc:
 push   edi
.L43f8dd:
 call   DWORD PTR [esi+0xc0]
.L43f8e3:
 movss  xmm0,DWORD PTR [ebp-0x24]
.L43f8e8:
 cvtps2pd xmm0,xmm0
.L43f8eb:
 mov    eax,DWORD PTR [edi]
.L43f8ed:
 movsd  QWORD PTR [esp+0x10],xmm0
.L43f8f3:
 movss  xmm0,DWORD PTR [ebp-0x28]
.L43f8f8:
 cvtps2pd xmm0,xmm0
.L43f8fb:
 movsd  QWORD PTR [esp+0x8],xmm0
.L43f901:
 movss  xmm0,DWORD PTR [ebp-0x2c]
.L43f906:
 cvtps2pd xmm0,xmm0
.L43f909:
 movsd  QWORD PTR [esp],xmm0
.L43f90e:
 push   0x9f9a74
.L43f913:
 push   0xe
.L43f915:
 push   0x5
.L43f917:
 push   0x2
.L43f919:
 push   edi
.L43f91a:
 call   DWORD PTR [eax+0xc0]
.L43f920:
 mov    eax,DWORD PTR [edi]
.L43f922:
 add    esp,0x2c
.L43f925:
 push   0x9f9a88
.L43f92a:
 push   0xd
.L43f92c:
 push   0xd
.L43f92e:
 push   0x2
.L43f930:
 push   edi
.L43f931:
 call   DWORD PTR [eax+0xc0]
.L43f937:
 mov    eax,DWORD PTR [edi]
.L43f939:
 add    esp,0x14
.L43f93c:
 push   0x9f9aac
.L43f941:
 push   0xd
.L43f943:
 push   0xe
.L43f945:
 push   0x2
.L43f947:
 push   edi
.L43f948:
 call   DWORD PTR [eax+0xc0]
.L43f94e:
 add    esp,0x14
.L43f951:
 push   0x9f9ac8
.L43f956:
 push   0xd
.L43f958:
 push   0xf
.L43f95a:
 jmp .L43f965
.L43f95c:
 push   0x9f9af0
.L43f961:
 push   0xc
.L43f963:
 push   0x4
.L43f965:
 mov    eax,DWORD PTR [edi]
.L43f967:
 push   0x2
.L43f969:
 push   edi
.L43f96a:
 call   DWORD PTR [eax+0xc0]
.L43f970:
 add    esp,0x14
.L43f973:
 mov    ecx,DWORD PTR [ebx+0x8]
.L43f976:
 lea    eax,[ebp-0x18]
.L43f979:
 push   eax
.L43f97a:
 call target_43f250
.L43f97f:
 mov    DWORD PTR [ebp-0x4],0x0
.L43f986:
 mov    esi,DWORD PTR [ebp-0x18]
.L43f989:
 test   esi,esi
.L43f98b:
 je .L43fc2b
.L43f991:
 mov    eax,DWORD PTR [esi+0xc]
.L43f994:
 sub    eax,DWORD PTR [esi+0x8]
.L43f997:
 test   eax,0xfffffffc
.L43f99c:
 je .L43fc2b
.L43f9a2:
 mov    eax,DWORD PTR [esi+0x8]
.L43f9a5:
 mov    ecx,DWORD PTR [eax]
.L43f9a7:
 mov    eax,DWORD PTR [ecx+0x14]
.L43f9aa:
 movd   xmm0,eax
.L43f9ae:
 cvtdq2pd xmm0,xmm0
.L43f9b2:
 shr    eax,0x1f
.L43f9b5:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L43f9be:
 cvtpd2ps xmm0,xmm0
.L43f9c2:
 cvttss2si eax,xmm0
.L43f9c6:
 test   eax,eax
.L43f9c8:
 jle .L43f9d8
.L43f9ca:
 cvttss2si eax,DWORD PTR [ecx+0x10]
.L43f9cf:
 cvttss2si ecx,xmm0
.L43f9d3:
 cdq
.L43f9d4:
 idiv   ecx
.L43f9d6:
 jmp .L43f9dc
.L43f9d8:
 {load} xor    edx,edx
.L43f9da:
 {load} mov    ecx,eax
.L43f9dc:
 cmp    BYTE PTR [ebx+0x138],0x0
.L43f9e3:
 jne .L43fa35
.L43f9e5:
 mov    eax,DWORD PTR [edi]
.L43f9e7:
 push   ecx
.L43f9e8:
 push   edx
.L43f9e9:
 push   0x9f9b04
.L43f9ee:
 push   0xe
.L43f9f0:
 push   0x7
.L43f9f2:
 push   0x2
.L43f9f4:
 push   edi
.L43f9f5:
 call   DWORD PTR [eax+0xc0]
.L43f9fb:
 mov    ecx,DWORD PTR [ebx+0x130]
.L43fa01:
 mov    eax,0x30c30c31
.L43fa06:
 sub    ecx,DWORD PTR [ebx+0x12c]
.L43fa0c:
 add    esp,0x1c
.L43fa0f:
 mov    edi,DWORD PTR [edi]
.L43fa11:
 imul   ecx
.L43fa13:
 sar    edx,0x4
.L43fa16:
 {load} mov    eax,edx
.L43fa18:
 shr    eax,0x1f
.L43fa1b:
 {load} add    eax,edx
.L43fa1d:
 push   eax
.L43fa1e:
 push   0x9f9b18
.L43fa23:
 push   0xe
.L43fa25:
 push   0x8
.L43fa27:
 push   0x2
.L43fa29:
 push   DWORD PTR [ebp-0x1c]
.L43fa2c:
 call   DWORD PTR [edi+0xc0]
.L43fa32:
 add    esp,0x18
.L43fa35:
 mov    ecx,DWORD PTR [0xc0d410]
.L43fa3b:
 push   0x0
.L43fa3d:
 mov    eax,DWORD PTR [ecx]
.L43fa3f:
 call   DWORD PTR [eax+0x4]
.L43fa42:
 {load} mov    edi,eax
.L43fa44:
 push   0x1
.L43fa46:
 {load} mov    ecx,edi
.L43fa48:
 mov    edx,DWORD PTR [edi]
.L43fa4a:
 mov    edx,DWORD PTR [edx+0x4]
.L43fa4d:
 call   edx
.L43fa4f:
 test   al,al
.L43fa51:
 je .L43fa68
.L43fa53:
 mov    eax,DWORD PTR [esi+0x8]
.L43fa56:
 mov    ecx,DWORD PTR [eax]
.L43fa58:
 mov    al,BYTE PTR [ecx+0x2a]
.L43fa5b:
 test   al,al
.L43fa5d:
 sete   al
.L43fa60:
 mov    BYTE PTR [ecx+0x2a],al
.L43fa63:
 jmp .L43faf1
.L43fa68:
 mov    eax,DWORD PTR [edi]
.L43fa6a:
 {load} mov    ecx,edi
.L43fa6c:
 push   0x2
.L43fa6e:
 mov    eax,DWORD PTR [eax+0x4]
.L43fa71:
 call   eax
.L43fa73:
 test   al,al
.L43fa75:
 je .L43fa90
.L43fa77:
 mov    eax,DWORD PTR [esi+0x8]
.L43fa7a:
 mov    eax,DWORD PTR [eax]
.L43fa7c:
 movss  xmm0,DWORD PTR [eax+0x10]
.L43fa81:
 addss  xmm0,DWORD PTR [0xa06558]
.L43fa89:
 movss  DWORD PTR [eax+0x10],xmm0
.L43fa8e:
 jmp .L43faf1
.L43fa90:
 mov    eax,DWORD PTR [edi]
.L43fa92:
 {load} mov    ecx,edi
.L43fa94:
 push   0x4
.L43fa96:
 mov    eax,DWORD PTR [eax+0x4]
.L43fa99:
 call   eax
.L43fa9b:
 test   al,al
.L43fa9d:
 je .L43fab1
.L43fa9f:
 cmp    BYTE PTR [ebx+0x138],0x0
.L43faa6:
 sete   al
.L43faa9:
 mov    BYTE PTR [ebx+0x138],al
.L43faaf:
 jmp .L43faf1
.L43fab1:
 mov    eax,DWORD PTR [edi]
.L43fab3:
 {load} mov    ecx,edi
.L43fab5:
 push   0x8
.L43fab7:
 mov    eax,DWORD PTR [eax+0x4]
.L43faba:
 call   eax
.L43fabc:
 test   al,al
.L43fabe:
 je .L43fad2
.L43fac0:
 cmp    BYTE PTR [ebx+0x139],0x0
.L43fac7:
 sete   al
.L43faca:
 mov    BYTE PTR [ebx+0x139],al
.L43fad0:
 jmp .L43faf1
.L43fad2:
 mov    eax,DWORD PTR [edi]
.L43fad4:
 {load} mov    ecx,edi
.L43fad6:
 push   0x10
.L43fad8:
 mov    eax,DWORD PTR [eax+0x4]
.L43fadb:
 call   eax
.L43fadd:
 test   al,al
.L43fadf:
 je .L43faf1
.L43fae1:
 cmp    BYTE PTR [ebx+0x13a],0x0
.L43fae8:
 sete   al
.L43faeb:
 mov    BYTE PTR [ebx+0x13a],al
.L43faf1:
 cmp    BYTE PTR [ebx+0x138],0x0
.L43faf8:
 je .L43fba1
.L43fafe:
 mov    ecx,DWORD PTR [ebx+0x130]
.L43fb04:
 mov    eax,0x30c30c31
.L43fb09:
 sub    ecx,DWORD PTR [ebx+0x12c]
.L43fb0f:
 mov    edi,0x0
.L43fb14:
 imul   ecx
.L43fb16:
 mov    DWORD PTR [ebp+0x8],edi
.L43fb19:
 sar    edx,0x4
.L43fb1c:
 {load} mov    eax,edx
.L43fb1e:
 shr    eax,0x1f
.L43fb21:
 {load} add    eax,edx
.L43fb23:
 mov    DWORD PTR [ebp-0x20],eax
.L43fb26:
 je .L43fba1
.L43fb28:
 mov    esi,DWORD PTR [ebp-0x1c]
.L43fb2b:
 mov    DWORD PTR [ebp-0x14],edi
.L43fb2e:
 {load} mov    edi,edi
.L43fb30:
 mov    eax,DWORD PTR [esi]
.L43fb32:
 push   0x9f9b28
.L43fb37:
 push   0xa
.L43fb39:
 push   0x2
.L43fb3b:
 push   0x2
.L43fb3d:
 push   esi
.L43fb3e:
 call   DWORD PTR [eax+0xc0]
.L43fb44:
 mov    ecx,DWORD PTR [ebp-0x14]
.L43fb47:
 add    esp,0x14
.L43fb4a:
 mov    eax,0x76b981db
.L43fb4f:
 add    ecx,0x4
.L43fb52:
 mul    edi
.L43fb54:
 mov    eax,DWORD PTR [ebx+0x12c]
.L43fb5a:
 mov    edi,DWORD PTR [esi]
.L43fb5c:
 {load} add    eax,ecx
.L43fb5e:
 mov    ecx,DWORD PTR [ebp+0x8]
.L43fb61:
 push   eax
.L43fb62:
 shr    edx,0x5
.L43fb65:
 imul   eax,edx,0x45
.L43fb68:
 push   0x999914
.L43fb6d:
 push   0xe
.L43fb6f:
 {load} sub    ecx,eax
.L43fb71:
 {load} mov    eax,edx
.L43fb73:
 shl    eax,0x4
.L43fb76:
 add    ecx,0x5
.L43fb79:
 {load} sub    eax,edx
.L43fb7b:
 push   ecx
.L43fb7c:
 lea    eax,[eax*2+0x2]
.L43fb83:
 push   eax
.L43fb84:
 push   esi
.L43fb85:
 call   DWORD PTR [edi+0xc0]
.L43fb8b:
 mov    edi,DWORD PTR [ebp+0x8]
.L43fb8e:
 add    esp,0x18
.L43fb91:
 add    DWORD PTR [ebp-0x14],0x54
.L43fb95:
 inc    edi
.L43fb96:
 mov    DWORD PTR [ebp+0x8],edi
.L43fb99:
 cmp    edi,DWORD PTR [ebp-0x20]
.L43fb9c:
 jb .L43fb30
.L43fb9e:
 mov    esi,DWORD PTR [ebp-0x18]
.L43fba1:
 cmp    BYTE PTR [ebx+0x139],0x0
.L43fba8:
 je .L43fc15
.L43fbaa:
 mov    ecx,DWORD PTR [0xbfb61c]
.L43fbb0:
 lea    edi,[ebp-0x48]
.L43fbb3:
 movaps xmm0,XMMWORD PTR [0xa06fe0]
.L43fbba:
 push   edi
.L43fbbb:
 mov    DWORD PTR [ebp-0x20],ecx
.L43fbbe:
 mov    edx,DWORD PTR [ecx]
.L43fbc0:
 movups XMMWORD PTR [ebp-0x48],xmm0
.L43fbc4:
 call   DWORD PTR [edx]
.L43fbc6:
 mov    ecx,DWORD PTR [ebx+0x130]
.L43fbcc:
 mov    eax,0x30c30c31
.L43fbd1:
 sub    ecx,DWORD PTR [ebx+0x12c]
.L43fbd7:
 imul   ecx
.L43fbd9:
 sar    edx,0x4
.L43fbdc:
 {load} mov    eax,edx
.L43fbde:
 shr    eax,0x1f
.L43fbe1:
 {load} add    eax,edx
.L43fbe3:
 je .L43fc15
.L43fbe5:
 {load} xor    edi,edi
.L43fbe7:
 {load} mov    esi,eax
.L43fbe9:
 {disp32} lea    esp,[esp+0x0]
.L43fbf0:
 mov    ecx,DWORD PTR [ebp-0x20]
.L43fbf3:
 mov    eax,DWORD PTR [ebx+0x12c]
.L43fbf9:
 push   ecx
.L43fbfa:
 add    eax,0x48
.L43fbfd:
 mov    DWORD PTR [esp],0x3dcccccd
.L43fc04:
 mov    edx,DWORD PTR [ecx]
.L43fc06:
 {load} add    eax,edi
.L43fc08:
 push   eax
.L43fc09:
 call   DWORD PTR [edx+0x1c]
.L43fc0c:
 add    edi,0x54
.L43fc0f:
 dec    esi
.L43fc10:
 jne .L43fbf0
.L43fc12:
 mov    esi,DWORD PTR [ebp-0x18]
.L43fc15:
 {load} xor    eax,eax
.L43fc17:
 mov    ecx,0xffff
.L43fc1c:
 cmp    BYTE PTR [ebx+0x13a],al
.L43fc22:
 cmovne eax,ecx
.L43fc25:
 mov    ecx,DWORD PTR [ebp-0x1c]
.L43fc28:
 mov    DWORD PTR [ecx+0xc],eax
.L43fc2b:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L43fc32:
 test   esi,esi
.L43fc34:
 je .L43fc48
.L43fc36:
 mov    eax,DWORD PTR [esi]
.L43fc38:
 mov    ecx,DWORD PTR [eax+0x4]
.L43fc3b:
 {load} add    ecx,esi
.L43fc3d:
 dec    DWORD PTR [ecx+0x4]
.L43fc40:
 jne .L43fc48
.L43fc42:
 mov    eax,DWORD PTR [ecx]
.L43fc44:
 push   0x1
.L43fc46:
 call   DWORD PTR [eax]
.L43fc48:
 mov    ecx,DWORD PTR [ebp-0xc]
.L43fc4b:
 mov    DWORD PTR fs:0x0,ecx
.L43fc52:
 pop    ecx
.L43fc53:
 pop    edi
.L43fc54:
 pop    esi
.L43fc55:
 pop    ebx
.L43fc56:
 {load} mov    esp,ebp
.L43fc58:
 pop    ebp
.L43fc59:
 ret    0x4
.equ target_418540,0x418540
.equ target_43f250,0x43f250
.equ target_43fc60,0x43fc60
