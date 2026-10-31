# Reviewed against original instructions and Ghidra export; see SHADERS.md.
# Original VA range 0x5789c0..0x578c1a
.intel_syntax noprefix
.code32
.text
.global original_shader_normalmapped_ctor
original_shader_normalmapped_ctor:
.L5789c0:
 push   ebp
.L5789c1:
 {load} mov    ebp,esp
.L5789c3:
 push   0xffffffff
.L5789c5:
 push   0x905468
.L5789ca:
 mov    eax,fs:0x0
.L5789d0:
 push   eax
.L5789d1:
 push   ecx
.L5789d2:
 push   esi
.L5789d3:
 push   edi
.L5789d4:
 mov    eax,[0xbaabc0]
.L5789d9:
 {load} xor    eax,ebp
.L5789db:
 push   eax
.L5789dc:
 lea    eax,[ebp-0xc]
.L5789df:
 mov    fs:0x0,eax
.L5789e5:
 {load} mov    edi,ecx
.L5789e7:
 mov    DWORD PTR [ebp-0x10],edi
.L5789ea:
 call target_5421b0
.L5789ef:
 mov    esi,DWORD PTR [ebp+0x8]
.L5789f2:
 {load} mov    edx,esi
.L5789f4:
 mov    eax,DWORD PTR [ebp+0xc]
.L5789f7:
 {load} add    edx,edx
.L5789f9:
 mov    DWORD PTR [ebp-0x4],0x0
.L578a00:
 mov    ecx,DWORD PTR [0xbfcd04]
.L578a06:
 mov    DWORD PTR [edi+0x58],eax
.L578a09:
 mov    eax,DWORD PTR [ebp+0x10]
.L578a0c:
 mov    DWORD PTR [edi],0xa01808
.L578a12:
 mov    DWORD PTR [edi+0xc],eax
.L578a15:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L578a19:
 mov    DWORD PTR [edi+0xbc],0x0
.L578a23:
 mov    DWORD PTR [edi+0xb8],0x0
.L578a2d:
 mov    DWORD PTR [edi+0xb4],0x0
.L578a37:
 mov    DWORD PTR [edi+0xb0],0x0
.L578a41:
 mov    DWORD PTR [edi+0xa8],0x0
.L578a4b:
 mov    DWORD PTR [edi+0xa4],0x0
.L578a55:
 mov    DWORD PTR [edi+0xa0],0x0
.L578a5f:
 mov    DWORD PTR [edi+0x9c],0x0
.L578a69:
 mov    DWORD PTR [edi+0x94],0x0
.L578a73:
 mov    DWORD PTR [edi+0x90],0x0
.L578a7d:
 mov    DWORD PTR [edi+0x8c],0x0
.L578a87:
 mov    DWORD PTR [edi+0x88],0x0
.L578a91:
 mov    DWORD PTR [edi+0xc0],0x3f800000
.L578a9b:
 mov    DWORD PTR [edi+0xac],0x3f800000
.L578aa5:
 mov    DWORD PTR [edi+0x98],0x3f800000
.L578aaf:
 mov    DWORD PTR [edi+0x84],0x3f800000
.L578ab9:
 mov    DWORD PTR [edi+0x4],eax
.L578abc:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L578ac0:
 mov    DWORD PTR [edi+0x8],eax
.L578ac3:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L578ac7:
 mov    DWORD PTR [edi+0x10],eax
.L578aca:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L578ace:
 push   0x9fe740
.L578ad3:
 push   DWORD PTR [edi+0x10]
.L578ad6:
 mov    DWORD PTR [edi+0x14],eax
.L578ad9:
 call target_542340
.L578ade:
 push   0x9fe764
.L578ae3:
 push   DWORD PTR [edi+0x10]
.L578ae6:
 mov    DWORD PTR [edi+0x5c],eax
.L578ae9:
 call target_542340
.L578aee:
 push   0x9fe754
.L578af3:
 push   DWORD PTR [edi+0x10]
.L578af6:
 mov    DWORD PTR [edi+0x60],eax
.L578af9:
 call target_542340
.L578afe:
 push   0x9fe7ac
.L578b03:
 push   DWORD PTR [edi+0x10]
.L578b06:
 mov    DWORD PTR [edi+0x64],eax
.L578b09:
 call target_542340
.L578b0e:
 push   0xa017b0
.L578b13:
 push   DWORD PTR [edi+0x10]
.L578b16:
 mov    DWORD PTR [edi+0x68],eax
.L578b19:
 call target_542340
.L578b1e:
 push   0xa017bc
.L578b23:
 push   DWORD PTR [edi+0x10]
.L578b26:
 mov    DWORD PTR [edi+0x6c],eax
.L578b29:
 call target_542340
.L578b2e:
 push   0xa017ec
.L578b33:
 push   DWORD PTR [edi+0x10]
.L578b36:
 mov    DWORD PTR [edi+0x70],eax
.L578b39:
 call target_542340
.L578b3e:
 push   0x9fe704
.L578b43:
 push   DWORD PTR [edi+0x14]
.L578b46:
 mov    DWORD PTR [edi+0x74],eax
.L578b49:
 call target_542340
.L578b4e:
 push   0x9fe6e8
.L578b53:
 push   DWORD PTR [edi+0x14]
.L578b56:
 mov    DWORD PTR [edi+0x78],eax
.L578b59:
 call target_542340
.L578b5e:
 push   0x9fe714
.L578b63:
 push   DWORD PTR [edi+0x14]
.L578b66:
 mov    DWORD PTR [edi+0x7c],eax
.L578b69:
 call target_542340
.L578b6e:
 push   0x9fe7a0
.L578b73:
 push   DWORD PTR [edi+0x10]
.L578b76:
 mov    DWORD PTR [edi+0x80],eax
.L578b7c:
 call target_542340
.L578b81:
 mov    DWORD PTR [edi+0xf4],eax
.L578b87:
 push   0x9fe788
.L578b8c:
 push   DWORD PTR [edi+0x14]
.L578b8f:
 call target_542340
.L578b94:
 push   0x9fe7b8
.L578b99:
 push   DWORD PTR [edi+0x14]
.L578b9c:
 mov    DWORD PTR [edi+0xf8],eax
.L578ba2:
 call target_542340
.L578ba7:
 push   0xa017f8
.L578bac:
 push   DWORD PTR [edi+0x14]
.L578baf:
 mov    DWORD PTR [edi+0xfc],eax
.L578bb5:
 call target_542340
.L578bba:
 push   0xa017c8
.L578bbf:
 push   DWORD PTR [edi+0x14]
.L578bc2:
 mov    DWORD PTR [edi+0x100],eax
.L578bc8:
 call target_542340
.L578bcd:
 push   0xa017d4
.L578bd2:
 push   DWORD PTR [edi+0x14]
.L578bd5:
 mov    DWORD PTR [edi+0x104],eax
.L578bdb:
 call target_542340
.L578be0:
 cmp    esi,0x53
.L578be3:
 mov    DWORD PTR [edi+0x108],eax
.L578be9:
 {load} mov    ecx,edi
.L578beb:
 sete   al
.L578bee:
 cmp    esi,0x5b
.L578bf1:
 mov    BYTE PTR [edi+0x110],al
.L578bf7:
 sete   al
.L578bfa:
 mov    BYTE PTR [edi+0x111],al
.L578c00:
 call target_542230
.L578c05:
 {load} mov    eax,edi
.L578c07:
 mov    ecx,DWORD PTR [ebp-0xc]
.L578c0a:
 mov    DWORD PTR fs:0x0,ecx
.L578c11:
 pop    ecx
.L578c12:
 pop    edi
.L578c13:
 pop    esi
.L578c14:
 {load} mov    esp,ebp
.L578c16:
 pop    ebp
.L578c17:
 ret    0xc
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
