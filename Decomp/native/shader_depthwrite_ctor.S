# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x577f00..0x578047
.intel_syntax noprefix
.code32
.text
.global original_shader_depthwrite_ctor
original_shader_depthwrite_ctor:
.L577f00:
 push   ebp
.L577f01:
 {load} mov    ebp,esp
.L577f03:
 push   0xffffffff
.L577f05:
 push   0x907fe8
.L577f0a:
 mov    eax,fs:0x0
.L577f10:
 push   eax
.L577f11:
 push   ecx
.L577f12:
 push   esi
.L577f13:
 mov    eax,[0xbaabc0]
.L577f18:
 {load} xor    eax,ebp
.L577f1a:
 push   eax
.L577f1b:
 lea    eax,[ebp-0xc]
.L577f1e:
 mov    fs:0x0,eax
.L577f24:
 {load} mov    esi,ecx
.L577f26:
 mov    DWORD PTR [ebp-0x10],esi
.L577f29:
 call target_5421b0
.L577f2e:
 mov    edx,DWORD PTR [ebp+0x8]
.L577f31:
 mov    eax,DWORD PTR [ebp+0xc]
.L577f34:
 mov    DWORD PTR [ebp-0x4],0x0
.L577f3b:
 mov    ecx,DWORD PTR [0xbfcd04]
.L577f41:
 mov    DWORD PTR [esi+0x58],edx
.L577f44:
 {load} add    edx,edx
.L577f46:
 mov    DWORD PTR [esi],0xa01638
.L577f4c:
 mov    DWORD PTR [esi+0x5c],eax
.L577f4f:
 push   0x9fe740
.L577f54:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L577f58:
 mov    DWORD PTR [esi+0x4],eax
.L577f5b:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L577f5f:
 mov    DWORD PTR [esi+0x10],eax
.L577f62:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L577f66:
 push   DWORD PTR [esi+0x10]
.L577f69:
 mov    DWORD PTR [esi+0x8],eax
.L577f6c:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L577f70:
 mov    DWORD PTR [esi+0x14],eax
.L577f73:
 call target_542340
.L577f78:
 push   0x9fe764
.L577f7d:
 push   DWORD PTR [esi+0x10]
.L577f80:
 mov    DWORD PTR [esi+0x60],eax
.L577f83:
 call target_542340
.L577f88:
 push   0xa01628
.L577f8d:
 push   DWORD PTR [esi+0x10]
.L577f90:
 mov    DWORD PTR [esi+0xa4],eax
.L577f96:
 call target_542340
.L577f9b:
 mov    DWORD PTR [esi+0xa8],eax
.L577fa1:
 {load} mov    ecx,esi
.L577fa3:
 mov    DWORD PTR [esi+0x9c],0x0
.L577fad:
 mov    DWORD PTR [esi+0x98],0x0
.L577fb7:
 mov    DWORD PTR [esi+0x94],0x0
.L577fc1:
 mov    DWORD PTR [esi+0x90],0x0
.L577fcb:
 mov    DWORD PTR [esi+0x88],0x0
.L577fd5:
 mov    DWORD PTR [esi+0x84],0x0
.L577fdf:
 mov    DWORD PTR [esi+0x80],0x0
.L577fe9:
 mov    DWORD PTR [esi+0x7c],0x0
.L577ff0:
 mov    DWORD PTR [esi+0x74],0x0
.L577ff7:
 mov    DWORD PTR [esi+0x70],0x0
.L577ffe:
 mov    DWORD PTR [esi+0x6c],0x0
.L578005:
 mov    DWORD PTR [esi+0x68],0x0
.L57800c:
 mov    DWORD PTR [esi+0xa0],0x3f800000
.L578016:
 mov    DWORD PTR [esi+0x8c],0x3f800000
.L578020:
 mov    DWORD PTR [esi+0x78],0x3f800000
.L578027:
 mov    DWORD PTR [esi+0x64],0x3f800000
.L57802e:
 call target_542230
.L578033:
 {load} mov    eax,esi
.L578035:
 mov    ecx,DWORD PTR [ebp-0xc]
.L578038:
 mov    DWORD PTR fs:0x0,ecx
.L57803f:
 pop    ecx
.L578040:
 pop    esi
.L578041:
 {load} mov    esp,ebp
.L578043:
 pop    ebp
.L578044:
 ret    0x8
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
