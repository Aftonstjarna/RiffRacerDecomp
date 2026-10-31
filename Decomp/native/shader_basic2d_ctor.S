# Reviewed original disassembly and Ghidra; see SHADERS.md.
# Original VA range 0x52ca50..0x52cc23
.intel_syntax noprefix
.code32
.text
.global original_shader_basic2d_ctor
original_shader_basic2d_ctor:
.L52ca50:
 push   ebp
.L52ca51:
 {load} mov    ebp,esp
.L52ca53:
 push   0xffffffff
.L52ca55:
 push   0x905468
.L52ca5a:
 mov    eax,fs:0x0
.L52ca60:
 push   eax
.L52ca61:
 sub    esp,0x8
.L52ca64:
 push   edi
.L52ca65:
 mov    eax,[0xbaabc0]
.L52ca6a:
 {load} xor    eax,ebp
.L52ca6c:
 push   eax
.L52ca6d:
 lea    eax,[ebp-0xc]
.L52ca70:
 mov    fs:0x0,eax
.L52ca76:
 {load} mov    edi,ecx
.L52ca78:
 mov    DWORD PTR [ebp-0x10],edi
.L52ca7b:
 call target_5421b0
.L52ca80:
 mov    ecx,DWORD PTR [ebp+0x8]
.L52ca83:
 mov    DWORD PTR [ebp-0x4],0x0
.L52ca8a:
 shl    ecx,0x4
.L52ca8d:
 add    ecx,DWORD PTR [0xbfcd04]
.L52ca93:
 mov    DWORD PTR [edi],0x9fe83c
.L52ca99:
 push   0x9fe740
.L52ca9e:
 push   0x0
.L52caa0:
 mov    eax,DWORD PTR [ecx+0x8]
.L52caa3:
 mov    DWORD PTR [edi+0x4],eax
.L52caa6:
 mov    eax,DWORD PTR [ecx+0x10]
.L52caa9:
 mov    DWORD PTR [edi+0x8],eax
.L52caac:
 mov    eax,DWORD PTR [ecx+0xc]
.L52caaf:
 mov    DWORD PTR [edi+0x10],eax
.L52cab2:
 mov    eax,DWORD PTR [ecx+0x14]
.L52cab5:
 mov    DWORD PTR [edi+0x14],eax
.L52cab8:
 mov    eax,DWORD PTR [edi+0x10]
.L52cabb:
 push   eax
.L52cabc:
 mov    ecx,DWORD PTR [eax]
.L52cabe:
 call   DWORD PTR [ecx+0x24]
.L52cac1:
 mov    DWORD PTR [edi+0x58],eax
.L52cac4:
 mov    eax,DWORD PTR [edi+0x10]
.L52cac7:
 push   0x9fe734
.L52cacc:
 push   0x0
.L52cace:
 push   eax
.L52cacf:
 mov    ecx,DWORD PTR [eax]
.L52cad1:
 call   DWORD PTR [ecx+0x24]
.L52cad4:
 push   0x9fe6f8
.L52cad9:
 push   DWORD PTR [edi+0x14]
.L52cadc:
 mov    DWORD PTR [edi+0x5c],eax
.L52cadf:
 call target_542340
.L52cae4:
 push   0x9fe6e8
.L52cae9:
 push   DWORD PTR [edi+0x14]
.L52caec:
 mov    DWORD PTR [edi+0x60],eax
.L52caef:
 call target_542340
.L52caf4:
 push   0x9fe714
.L52caf9:
 push   DWORD PTR [edi+0x14]
.L52cafc:
 mov    DWORD PTR [edi+0x74],eax
.L52caff:
 call target_542340
.L52cb04:
 push   0x9fe704
.L52cb09:
 push   DWORD PTR [edi+0x14]
.L52cb0c:
 mov    DWORD PTR [edi+0x78],eax
.L52cb0f:
 call target_542340
.L52cb14:
 push   0x9fe7a0
.L52cb19:
 push   DWORD PTR [edi+0x10]
.L52cb1c:
 mov    DWORD PTR [edi+0x7c],eax
.L52cb1f:
 call target_542340
.L52cb24:
 push   0x9fe7a0
.L52cb29:
 push   DWORD PTR [edi+0x14]
.L52cb2c:
 mov    DWORD PTR [edi+0x64],eax
.L52cb2f:
 call target_542340
.L52cb34:
 push   0x9fe788
.L52cb39:
 push   DWORD PTR [edi+0x14]
.L52cb3c:
 mov    DWORD PTR [edi+0x68],eax
.L52cb3f:
 call target_542340
.L52cb44:
 push   0x9fe7b8
.L52cb49:
 push   DWORD PTR [edi+0x14]
.L52cb4c:
 mov    DWORD PTR [edi+0x6c],eax
.L52cb4f:
 call target_542340
.L52cb54:
 push   0x9fe7ac
.L52cb59:
 push   DWORD PTR [edi+0x10]
.L52cb5c:
 mov    DWORD PTR [edi+0x70],eax
.L52cb5f:
 call target_542340
.L52cb64:
 push   0x9fe764
.L52cb69:
 push   DWORD PTR [edi+0x10]
.L52cb6c:
 mov    DWORD PTR [edi+0x80],eax
.L52cb72:
 call target_542340
.L52cb77:
 push   0x9fe754
.L52cb7c:
 push   DWORD PTR [edi+0x10]
.L52cb7f:
 mov    DWORD PTR [edi+0x84],eax
.L52cb85:
 call target_542340
.L52cb8a:
 push   0x9fe77c
.L52cb8f:
 push   DWORD PTR [edi+0x10]
.L52cb92:
 mov    DWORD PTR [edi+0x88],eax
.L52cb98:
 call target_542340
.L52cb9d:
 push   0x9fe770
.L52cba2:
 push   DWORD PTR [edi+0x10]
.L52cba5:
 mov    DWORD PTR [edi+0x8c],eax
.L52cbab:
 call target_542340
.L52cbb0:
 mov    DWORD PTR [edi+0x90],eax
.L52cbb6:
 push   0x9fe7cc
.L52cbbb:
 push   DWORD PTR [edi+0x14]
.L52cbbe:
 call target_542340
.L52cbc3:
 push   0x40
.L52cbc5:
 mov    DWORD PTR [edi+0x94],eax
.L52cbcb:
 lea    eax,[edi+0x98]
.L52cbd1:
 push   0x0
.L52cbd3:
 push   eax
.L52cbd4:
 call target_8f8d7e
.L52cbd9:
 add    esp,0xc
.L52cbdc:
 lea    eax,[edi+0xd8]
.L52cbe2:
 push   0x40
.L52cbe4:
 push   0x0
.L52cbe6:
 push   eax
.L52cbe7:
 call target_8f8d7e
.L52cbec:
 add    esp,0xc
.L52cbef:
 lea    eax,[edi+0x118]
.L52cbf5:
 push   0x40
.L52cbf7:
 push   0x0
.L52cbf9:
 push   eax
.L52cbfa:
 call target_8f8d7e
.L52cbff:
 add    esp,0xc
.L52cc02:
 cmp    DWORD PTR [ebp+0x8],0x3
.L52cc06:
 sete   al
.L52cc09:
 mov    BYTE PTR [edi+0x158],al
.L52cc0f:
 {load} mov    eax,edi
.L52cc11:
 mov    ecx,DWORD PTR [ebp-0xc]
.L52cc14:
 mov    DWORD PTR fs:0x0,ecx
.L52cc1b:
 pop    ecx
.L52cc1c:
 pop    edi
.L52cc1d:
 {load} mov    esp,ebp
.L52cc1f:
 pop    ebp
.L52cc20:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542340,0x542340
.equ target_8f8d7e,0x8f8d7e
