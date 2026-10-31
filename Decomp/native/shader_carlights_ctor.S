# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x576f00..0x577039
.intel_syntax noprefix
.code32
.text
.global original_shader_carlights_ctor
original_shader_carlights_ctor:
.L576f00:
 push   ebp
.L576f01:
 {load} mov    ebp,esp
.L576f03:
 push   0xffffffff
.L576f05:
 push   0x905468
.L576f0a:
 mov    eax,fs:0x0
.L576f10:
 push   eax
.L576f11:
 sub    esp,0x8
.L576f14:
 push   esi
.L576f15:
 mov    eax,[0xbaabc0]
.L576f1a:
 {load} xor    eax,ebp
.L576f1c:
 push   eax
.L576f1d:
 lea    eax,[ebp-0xc]
.L576f20:
 mov    fs:0x0,eax
.L576f26:
 {load} mov    esi,ecx
.L576f28:
 mov    DWORD PTR [ebp-0x10],esi
.L576f2b:
 call target_5421b0
.L576f30:
 mov    DWORD PTR [ebp-0x4],0x0
.L576f37:
 mov    ecx,DWORD PTR [0xbfcd04]
.L576f3d:
 mov    eax,DWORD PTR [ebp+0x8]
.L576f40:
 mov    DWORD PTR [esi+0xa0],eax
.L576f46:
 mov    DWORD PTR [esi],0xa0145c
.L576f4c:
 mov    eax,DWORD PTR [ecx+0x8e8]
.L576f52:
 mov    DWORD PTR [esi+0x98],0x0
.L576f5c:
 mov    DWORD PTR [esi+0x94],0x0
.L576f66:
 mov    DWORD PTR [esi+0x90],0x0
.L576f70:
 mov    DWORD PTR [esi+0x8c],0x0
.L576f7a:
 mov    DWORD PTR [esi+0x84],0x0
.L576f84:
 mov    DWORD PTR [esi+0x80],0x0
.L576f8e:
 mov    DWORD PTR [esi+0x7c],0x0
.L576f95:
 mov    DWORD PTR [esi+0x78],0x0
.L576f9c:
 mov    DWORD PTR [esi+0x70],0x0
.L576fa3:
 mov    DWORD PTR [esi+0x6c],0x0
.L576faa:
 mov    DWORD PTR [esi+0x68],0x0
.L576fb1:
 mov    DWORD PTR [esi+0x64],0x0
.L576fb8:
 mov    DWORD PTR [esi+0x9c],0x3f800000
.L576fc2:
 mov    DWORD PTR [esi+0x88],0x3f800000
.L576fcc:
 mov    DWORD PTR [esi+0x74],0x3f800000
.L576fd3:
 mov    DWORD PTR [esi+0x60],0x3f800000
.L576fda:
 mov    DWORD PTR [esi+0x4],eax
.L576fdd:
 mov    eax,DWORD PTR [ecx+0x8f0]
.L576fe3:
 mov    DWORD PTR [esi+0x8],eax
.L576fe6:
 mov    eax,DWORD PTR [ecx+0x8ec]
.L576fec:
 mov    DWORD PTR [esi+0x10],eax
.L576fef:
 mov    eax,DWORD PTR [ecx+0x8f4]
.L576ff5:
 mov    DWORD PTR [esi+0x14],eax
.L576ff8:
 mov    eax,DWORD PTR [esi+0x10]
.L576ffb:
 push   0x9fe740
.L577000:
 push   0x0
.L577002:
 push   eax
.L577003:
 mov    ecx,DWORD PTR [eax]
.L577005:
 call   DWORD PTR [ecx+0x24]
.L577008:
 mov    DWORD PTR [esi+0x58],eax
.L57700b:
 mov    eax,DWORD PTR [esi+0x14]
.L57700e:
 push   0xa014b4
.L577013:
 push   0x0
.L577015:
 push   eax
.L577016:
 mov    ecx,DWORD PTR [eax]
.L577018:
 call   DWORD PTR [ecx+0x24]
.L57701b:
 {load} mov    ecx,esi
.L57701d:
 mov    DWORD PTR [esi+0x5c],eax
.L577020:
 call target_542230
.L577025:
 {load} mov    eax,esi
.L577027:
 mov    ecx,DWORD PTR [ebp-0xc]
.L57702a:
 mov    DWORD PTR fs:0x0,ecx
.L577031:
 pop    ecx
.L577032:
 pop    esi
.L577033:
 {load} mov    esp,ebp
.L577035:
 pop    ebp
.L577036:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
