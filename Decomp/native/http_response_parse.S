# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5c1d70,0x5c20da); instruction-contiguous extent, INT3 padding excluded.
# HTTP response parsing: uses strstr/_strnicmp/atoi and the HTTP header literals referenced
# by the request builder; original length-error and vtable paths retained.
# Identification rests on those imports/literals and the worker resource-state caller;
# exact field semantics remain unproven. Reference-assembly evidence only, no source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x5c1d70..0x5c20da
.intel_syntax noprefix
.code32
.text
.global original_http_response_parse
original_http_response_parse:
.L5c1d70:
 push   ebp
.L5c1d71:
 {load} mov    ebp,esp
.L5c1d73:
 sub    esp,0x34
.L5c1d76:
 mov    eax,[0xbaabc0]
.L5c1d7b:
 {load} xor    eax,ebp
.L5c1d7d:
 mov    DWORD PTR [ebp-0x4],eax
.L5c1d80:
 push   ebx
.L5c1d81:
 push   esi
.L5c1d82:
 {load} mov    esi,ecx
.L5c1d84:
 push   edi
.L5c1d85:
 mov    eax,DWORD PTR [esi+0x8]
.L5c1d88:
 lea    ecx,[esi+0x8]
.L5c1d8b:
 call   DWORD PTR [eax+0x28]
.L5c1d8e:
 mov    ecx,DWORD PTR [esi+0xc0]
.L5c1d94:
 lea    edi,[esi+0xc0]
.L5c1d9a:
 mov    DWORD PTR [edi+0x4],ecx
.L5c1d9d:
 mov    ecx,DWORD PTR [edi+0x8]
.L5c1da0:
 sub    ecx,DWORD PTR [edi]
.L5c1da2:
 lea    edx,[eax+0x1]
.L5c1da5:
 mov    DWORD PTR [ebp-0x24],eax
.L5c1da8:
 {load} cmp    ecx,edx
.L5c1daa:
 jae .L5c1dc4
.L5c1dac:
 cmp    edx,0xffffffff
.L5c1daf:
 jbe .L5c1dbc
.L5c1db1:
 push   0x999938
.L5c1db6:
 call   DWORD PTR [0x92d168]
.L5c1dbc:
 push   edx
.L5c1dbd:
 {load} mov    ecx,edi
.L5c1dbf:
 call target_51a450
.L5c1dc4:
 push   DWORD PTR [ebp-0x24]
.L5c1dc7:
 mov    eax,DWORD PTR [esi+0x8]
.L5c1dca:
 lea    ecx,[esi+0x8]
.L5c1dcd:
 push   edi
.L5c1dce:
 call   DWORD PTR [eax+0x2c]
.L5c1dd1:
 mov    eax,DWORD PTR [edi]
.L5c1dd3:
 cmp    eax,DWORD PTR [edi+0x4]
.L5c1dd6:
 je .L5c20ae
.L5c1ddc:
 lea    eax,[ebp-0x20]
.L5c1ddf:
 mov    BYTE PTR [ebp-0x20],0x0
.L5c1de3:
 push   eax
.L5c1de4:
 {load} mov    ecx,edi
.L5c1de6:
 call target_5c20e0
.L5c1deb:
 mov    ebx,DWORD PTR [edi]
.L5c1ded:
 push   0xa06004
.L5c1df2:
 push   ebx
.L5c1df3:
 mov    DWORD PTR [ebp-0x24],ebx
.L5c1df6:
 call   DWORD PTR [0x92d3dc]
.L5c1dfc:
 add    esp,0x8
.L5c1dff:
 mov    DWORD PTR [esi+0xcc],eax
.L5c1e05:
 test   eax,eax
.L5c1e07:
 je .L5c20ac
.L5c1e0d:
 add    eax,0x4
.L5c1e10:
 push   0xa06038
.L5c1e15:
 push   ebx
.L5c1e16:
 mov    DWORD PTR [esi+0xcc],eax
.L5c1e1c:
 call   DWORD PTR [0x92d3dc]
.L5c1e22:
 push   0x20
.L5c1e24:
 push   ebx
.L5c1e25:
 mov    DWORD PTR [ebp-0x28],eax
.L5c1e28:
 call   DWORD PTR [0x92d394]
.L5c1e2e:
 push   0x5
.L5c1e30:
 push   0xa0600c
.L5c1e35:
 push   DWORD PTR [ebp-0x24]
.L5c1e38:
 {load} mov    ebx,eax
.L5c1e3a:
 call   DWORD PTR [0x92d3d4]
.L5c1e40:
 add    esp,0x1c
.L5c1e43:
 test   eax,eax
.L5c1e45:
 jne .L5c20ac
.L5c1e4b:
 test   ebx,ebx
.L5c1e4d:
 je .L5c20ac
.L5c1e53:
 mov    eax,DWORD PTR [ebp-0x28]
.L5c1e56:
 add    eax,0xfffffffc
.L5c1e59:
 {load} cmp    ebx,eax
.L5c1e5b:
 jae .L5c20ac
.L5c1e61:
 mov    al,BYTE PTR [ebx+0x1]
.L5c1e64:
 cmp    al,0x30
.L5c1e66:
 jl .L5c20ac
.L5c1e6c:
 cmp    al,0x39
.L5c1e6e:
 jg .L5c20ac
.L5c1e74:
 mov    cl,BYTE PTR [ebx+0x2]
.L5c1e77:
 cmp    cl,0x30
.L5c1e7a:
 jl .L5c20ac
.L5c1e80:
 cmp    cl,0x39
.L5c1e83:
 jg .L5c20ac
.L5c1e89:
 mov    cl,BYTE PTR [ebx+0x3]
.L5c1e8c:
 cmp    cl,0x30
.L5c1e8f:
 jl .L5c20ac
.L5c1e95:
 cmp    cl,0x39
.L5c1e98:
 jg .L5c20ac
.L5c1e9e:
 mov    BYTE PTR [ebp-0x2c],al
.L5c1ea1:
 mov    al,BYTE PTR [ebx+0x2]
.L5c1ea4:
 mov    BYTE PTR [ebp-0x2b],al
.L5c1ea7:
 mov    al,BYTE PTR [ebx+0x3]
.L5c1eaa:
 mov    BYTE PTR [ebp-0x2a],al
.L5c1ead:
 lea    eax,[ebp-0x2c]
.L5c1eb0:
 push   eax
.L5c1eb1:
 mov    BYTE PTR [ebp-0x29],0x0
.L5c1eb5:
 call   DWORD PTR [0x92d3e8]
.L5c1ebb:
 add    esp,0x4
.L5c1ebe:
 lea    ecx,[eax-0x12c]
.L5c1ec4:
 cmp    ecx,0x63
.L5c1ec7:
 ja .L5c20a4
.L5c1ecd:
 cmp    DWORD PTR [esi+0xbc],0x0
.L5c1ed4:
 jbe .L5c20a4
.L5c1eda:
 mov    eax,DWORD PTR [esi]
.L5c1edc:
 lea    edi,[esi+0x84]
.L5c1ee2:
 push   edi
.L5c1ee3:
 push   0xa06014
.L5c1ee8:
 {load} mov    ecx,esi
.L5c1eea:
 mov    BYTE PTR [esi+0xd0],0x1
.L5c1ef1:
 mov    eax,DWORD PTR [eax+0x24]
.L5c1ef4:
 call   eax
.L5c1ef6:
 test   al,al
.L5c1ef8:
 jne .L5c1f14
.L5c1efa:
 push   0xffffffff
.L5c1efc:
 {load} mov    ecx,esi
.L5c1efe:
 call target_5c1060
.L5c1f03:
 pop    edi
.L5c1f04:
 pop    esi
.L5c1f05:
 pop    ebx
.L5c1f06:
 mov    ecx,DWORD PTR [ebp-0x4]
.L5c1f09:
 {load} xor    ecx,ebp
.L5c1f0b:
 call target_8f8958
.L5c1f10:
 {load} mov    esp,ebp
.L5c1f12:
 pop    ebp
.L5c1f13:
 ret
.L5c1f14:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c1f18:
 jb .L5c1f1e
.L5c1f1a:
 mov    eax,DWORD PTR [edi]
.L5c1f1c:
 jmp .L5c1f20
.L5c1f1e:
 {load} mov    eax,edi
.L5c1f20:
 push   0x7
.L5c1f22:
 push   0xa06020
.L5c1f27:
 push   eax
.L5c1f28:
 call   DWORD PTR [0x92d3d4]
.L5c1f2e:
 add    esp,0xc
.L5c1f31:
 test   eax,eax
.L5c1f33:
 jne .L5c1efa
.L5c1f35:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c1f39:
 jb .L5c1f3f
.L5c1f3b:
 mov    eax,DWORD PTR [edi]
.L5c1f3d:
 jmp .L5c1f41
.L5c1f3f:
 {load} mov    eax,edi
.L5c1f41:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c1f45:
 lea    ecx,[eax+0x7]
.L5c1f48:
 jb .L5c1f4e
.L5c1f4a:
 mov    eax,DWORD PTR [edi]
.L5c1f4c:
 jmp .L5c1f50
.L5c1f4e:
 {load} mov    eax,edi
.L5c1f50:
 push   ecx
.L5c1f51:
 push   eax
.L5c1f52:
 lea    eax,[ebp-0x28]
.L5c1f55:
 {load} mov    ecx,edi
.L5c1f57:
 push   eax
.L5c1f58:
 call target_5a07d0
.L5c1f5d:
 push   0x1
.L5c1f5f:
 push   0x0
.L5c1f61:
 lea    eax,[ebp-0x20]
.L5c1f64:
 mov    BYTE PTR [ebp-0x20],0x2f
.L5c1f68:
 push   eax
.L5c1f69:
 {load} mov    ecx,edi
.L5c1f6b:
 call target_440b90
.L5c1f70:
 {load} mov    ebx,eax
.L5c1f72:
 cmp    ebx,0xffffffff
.L5c1f75:
 jne .L5c1f86
.L5c1f77:
 push   0x9fc1e8
.L5c1f7c:
 lea    ecx,[esi+0x6c]
.L5c1f7f:
 call target_415b90
.L5c1f84:
 jmp .L5c1fcc
.L5c1f86:
 push   0xffffffff
.L5c1f88:
 push   ebx
.L5c1f89:
 lea    eax,[ebp-0x1c]
.L5c1f8c:
 {load} mov    ecx,edi
.L5c1f8e:
 push   eax
.L5c1f8f:
 call target_440a90
.L5c1f94:
 push   eax
.L5c1f95:
 lea    ecx,[esi+0x6c]
.L5c1f98:
 call target_440a20
.L5c1f9d:
 lea    ecx,[ebp-0x1c]
.L5c1fa0:
 call target_415b60
.L5c1fa5:
 lea    eax,[ebp-0x28]
.L5c1fa8:
 {load} mov    ecx,edi
.L5c1faa:
 push   eax
.L5c1fab:
 call target_440a60
.L5c1fb0:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c1fb4:
 jb .L5c1fba
.L5c1fb6:
 mov    ecx,DWORD PTR [edi]
.L5c1fb8:
 jmp .L5c1fbc
.L5c1fba:
 {load} mov    ecx,edi
.L5c1fbc:
 push   DWORD PTR [eax]
.L5c1fbe:
 {load} add    ecx,ebx
.L5c1fc0:
 lea    eax,[ebp-0x24]
.L5c1fc3:
 push   ecx
.L5c1fc4:
 push   eax
.L5c1fc5:
 {load} mov    ecx,edi
.L5c1fc7:
 call target_5a07d0
.L5c1fcc:
 push   0x1
.L5c1fce:
 push   0x0
.L5c1fd0:
 lea    eax,[ebp-0x20]
.L5c1fd3:
 mov    BYTE PTR [ebp-0x20],0x3a
.L5c1fd7:
 push   eax
.L5c1fd8:
 {load} mov    ecx,edi
.L5c1fda:
 call target_440b90
.L5c1fdf:
 {load} mov    ebx,eax
.L5c1fe1:
 cmp    ebx,0xffffffff
.L5c1fe4:
 je .L5c203f
.L5c1fe6:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c1fea:
 jb .L5c1ff0
.L5c1fec:
 mov    eax,DWORD PTR [edi]
.L5c1fee:
 jmp .L5c1ff2
.L5c1ff0:
 {load} mov    eax,edi
.L5c1ff2:
 inc    eax
.L5c1ff3:
 {load} add    eax,ebx
.L5c1ff5:
 push   eax
.L5c1ff6:
 call   DWORD PTR [0x92d3e8]
.L5c1ffc:
 add    esp,0x4
.L5c1fff:
 mov    DWORD PTR [ebp-0x28],eax
.L5c2002:
 lea    eax,[ebp-0x24]
.L5c2005:
 {load} mov    ecx,edi
.L5c2007:
 push   eax
.L5c2008:
 call target_440a60
.L5c200d:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c2011:
 jb .L5c2017
.L5c2013:
 mov    ecx,DWORD PTR [edi]
.L5c2015:
 jmp .L5c2019
.L5c2017:
 {load} mov    ecx,edi
.L5c2019:
 push   DWORD PTR [eax]
.L5c201b:
 {load} add    ecx,ebx
.L5c201d:
 lea    eax,[ebp-0x30]
.L5c2020:
 push   ecx
.L5c2021:
 push   eax
.L5c2022:
 {load} mov    ecx,edi
.L5c2024:
 call target_5a07d0
.L5c2029:
 mov    ecx,DWORD PTR [ebp-0x28]
.L5c202c:
 lea    eax,[ecx-0x1]
.L5c202f:
 cmp    eax,0xfffd
.L5c2034:
 ja .L5c1efa
.L5c203a:
 movzx  ecx,cx
.L5c203d:
 jmp .L5c2044
.L5c203f:
 mov    ecx,0x50
.L5c2044:
 dec    DWORD PTR [esi+0xbc]
.L5c204a:
 cmp    DWORD PTR [edi+0x14],0x10
.L5c204e:
 jb .L5c2052
.L5c2050:
 mov    edi,DWORD PTR [edi]
.L5c2052:
 mov    eax,DWORD PTR [esi+0x8]
.L5c2055:
 push   ecx
.L5c2056:
 push   edi
.L5c2057:
 lea    ecx,[esi+0x8]
.L5c205a:
 mov    eax,DWORD PTR [eax+0x4]
.L5c205d:
 call   eax
.L5c205f:
 test   al,al
.L5c2061:
 jne .L5c2085
.L5c2063:
 mov    eax,DWORD PTR [esi+0x8]
.L5c2066:
 lea    ecx,[esi+0x8]
.L5c2069:
 call   DWORD PTR [eax+0x38]
.L5c206c:
 push   eax
.L5c206d:
 {load} mov    ecx,esi
.L5c206f:
 call target_5c1060
.L5c2074:
 pop    edi
.L5c2075:
 pop    esi
.L5c2076:
 pop    ebx
.L5c2077:
 mov    ecx,DWORD PTR [ebp-0x4]
.L5c207a:
 {load} xor    ecx,ebp
.L5c207c:
 call target_8f8958
.L5c2081:
 {load} mov    esp,ebp
.L5c2083:
 pop    ebp
.L5c2084:
 ret
.L5c2085:
 mov    BYTE PTR [esi+0xd0],0x0
.L5c208c:
 mov    DWORD PTR [esi+0x64],0x1
.L5c2093:
 pop    edi
.L5c2094:
 pop    esi
.L5c2095:
 pop    ebx
.L5c2096:
 mov    ecx,DWORD PTR [ebp-0x4]
.L5c2099:
 {load} xor    ecx,ebp
.L5c209b:
 call target_8f8958
.L5c20a0:
 {load} mov    esp,ebp
.L5c20a2:
 pop    ebp
.L5c20a3:
 ret
.L5c20a4:
 mov    DWORD PTR [esi+0xd8],eax
.L5c20aa:
 jmp .L5c20bb
.L5c20ac:
 mov    eax,DWORD PTR [edi]
.L5c20ae:
 mov    DWORD PTR [edi+0x4],eax
.L5c20b1:
 mov    DWORD PTR [esi+0xd4],0xffffffff
.L5c20bb:
 mov    ecx,DWORD PTR [ebp-0x4]
.L5c20be:
 pop    edi
.L5c20bf:
 mov    DWORD PTR [esi+0x64],0x0
.L5c20c6:
 {load} xor    ecx,ebp
.L5c20c8:
 mov    BYTE PTR [esi+0xd0],0x1
.L5c20cf:
 pop    esi
.L5c20d0:
 pop    ebx
.L5c20d1:
 call target_8f8958
.L5c20d6:
 {load} mov    esp,ebp
.L5c20d8:
 pop    ebp
.L5c20d9:
 ret
.equ target_415b60,0x415b60
.equ target_415b90,0x415b90
.equ target_440a20,0x440a20
.equ target_440a60,0x440a60
.equ target_440a90,0x440a90
.equ target_440b90,0x440b90
.equ target_51a450,0x51a450
.equ target_5a07d0,0x5a07d0
.equ target_5c1060,0x5c1060
.equ target_5c20e0,0x5c20e0
.equ target_8f8958,0x8f8958
