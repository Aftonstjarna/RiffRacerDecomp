# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x576c20..0x576ce0
.intel_syntax noprefix
.code32
.text
.global original_shader_shadowdraw_ctor
original_shader_shadowdraw_ctor:
.L576c20:
 push   ebp
.L576c21:
 {load} mov    ebp,esp
.L576c23:
 push   0xffffffff
.L576c25:
 push   0x905468
.L576c2a:
 mov    eax,fs:0x0
.L576c30:
 push   eax
.L576c31:
 sub    esp,0x8
.L576c34:
 push   esi
.L576c35:
 mov    eax,[0xbaabc0]
.L576c3a:
 {load} xor    eax,ebp
.L576c3c:
 push   eax
.L576c3d:
 lea    eax,[ebp-0xc]
.L576c40:
 mov    fs:0x0,eax
.L576c46:
 {load} mov    esi,ecx
.L576c48:
 mov    DWORD PTR [ebp-0x10],esi
.L576c4b:
 call target_5421b0
.L576c50:
 mov    edx,DWORD PTR [ebp+0x8]
.L576c53:
 mov    DWORD PTR [ebp-0x4],0x0
.L576c5a:
 mov    ecx,DWORD PTR [0xbfcd04]
.L576c60:
 mov    DWORD PTR [esi],0xa013d8
.L576c66:
 mov    DWORD PTR [esi+0x64],0x0
.L576c6d:
 mov    DWORD PTR [esi+0x68],0x0
.L576c74:
 mov    DWORD PTR [esi+0x6c],edx
.L576c77:
 {load} add    edx,edx
.L576c79:
 push   0x9fe740
.L576c7e:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L576c82:
 mov    DWORD PTR [esi+0x4],eax
.L576c85:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L576c89:
 mov    DWORD PTR [esi+0x8],eax
.L576c8c:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L576c90:
 mov    DWORD PTR [esi+0x10],eax
.L576c93:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L576c97:
 push   DWORD PTR [esi+0x10]
.L576c9a:
 mov    DWORD PTR [esi+0x14],eax
.L576c9d:
 call target_542340
.L576ca2:
 push   0xa013b0
.L576ca7:
 push   DWORD PTR [esi+0x10]
.L576caa:
 mov    DWORD PTR [esi+0x58],eax
.L576cad:
 call target_542340
.L576cb2:
 push   0xa013b0
.L576cb7:
 push   DWORD PTR [esi+0x14]
.L576cba:
 mov    DWORD PTR [esi+0x5c],eax
.L576cbd:
 call target_542340
.L576cc2:
 {load} mov    ecx,esi
.L576cc4:
 mov    DWORD PTR [esi+0x60],eax
.L576cc7:
 call target_542230
.L576ccc:
 {load} mov    eax,esi
.L576cce:
 mov    ecx,DWORD PTR [ebp-0xc]
.L576cd1:
 mov    DWORD PTR fs:0x0,ecx
.L576cd8:
 pop    ecx
.L576cd9:
 pop    esi
.L576cda:
 {load} mov    esp,ebp
.L576cdc:
 pop    ebp
.L576cdd:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
