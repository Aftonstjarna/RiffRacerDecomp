# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x580150,0x5802cb); instruction-contiguous extent, INT3 padding excluded.
# Shader camera/environment parameter update: references the original matInvView, vCameraPos and mudScratchChromeBlend literals and the shared shader parameter path, retaining its SEH frame and helper calls.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x580150..0x5802cb
.intel_syntax noprefix
.code32
.text
.global original_shader_camera_environment_set
original_shader_camera_environment_set:
.L580150:
 push   ebp
.L580151:
 {load} mov    ebp,esp
.L580153:
 push   0xffffffff
.L580155:
 push   0x908376
.L58015a:
 mov    eax,fs:0x0
.L580160:
 push   eax
.L580161:
 sub    esp,0x8
.L580164:
 push   esi
.L580165:
 mov    eax,[0xbaabc0]
.L58016a:
 {load} xor    eax,ebp
.L58016c:
 push   eax
.L58016d:
 lea    eax,[ebp-0xc]
.L580170:
 mov    fs:0x0,eax
.L580176:
 {load} mov    esi,ecx
.L580178:
 mov    DWORD PTR [ebp-0x10],esi
.L58017b:
 call target_5421b0
.L580180:
 mov    eax,DWORD PTR [ebp+0x8]
.L580183:
 mov    DWORD PTR [ebp-0x4],0x0
.L58018a:
 mov    DWORD PTR [esi],0xa02304
.L580190:
 mov    DWORD PTR [esi+0x58],eax
.L580193:
 mov    DWORD PTR [esi+0x5c],0x0
.L58019a:
 mov    DWORD PTR [esi+0xb0],0x0
.L5801a4:
 mov    BYTE PTR [ebp-0x4],0x1
.L5801a8:
 mov    ecx,DWORD PTR [0xbfcd04]
.L5801ae:
 mov    DWORD PTR [esi+0xb4],0x0
.L5801b8:
 mov    DWORD PTR [esi+0xa8],0x0
.L5801c2:
 mov    DWORD PTR [esi+0xa4],0x0
.L5801cc:
 mov    eax,DWORD PTR [ecx+0x8c8]
.L5801d2:
 mov    DWORD PTR [esi+0xa0],0x0
.L5801dc:
 mov    DWORD PTR [esi+0x9c],0x0
.L5801e6:
 mov    DWORD PTR [esi+0x94],0x0
.L5801f0:
 mov    DWORD PTR [esi+0x90],0x0
.L5801fa:
 mov    DWORD PTR [esi+0x8c],0x0
.L580204:
 mov    DWORD PTR [esi+0x88],0x0
.L58020e:
 mov    DWORD PTR [esi+0x80],0x0
.L580218:
 mov    DWORD PTR [esi+0x7c],0x0
.L58021f:
 mov    DWORD PTR [esi+0x78],0x0
.L580226:
 mov    DWORD PTR [esi+0x74],0x0
.L58022d:
 mov    DWORD PTR [esi+0xac],0x3f800000
.L580237:
 mov    DWORD PTR [esi+0x98],0x3f800000
.L580241:
 mov    DWORD PTR [esi+0x84],0x3f800000
.L58024b:
 mov    DWORD PTR [esi+0x70],0x3f800000
.L580252:
 mov    DWORD PTR [esi+0x4],eax
.L580255:
 mov    eax,DWORD PTR [ecx+0x8d0]
.L58025b:
 mov    DWORD PTR [esi+0x8],eax
.L58025e:
 mov    eax,DWORD PTR [ecx+0x8cc]
.L580264:
 mov    DWORD PTR [esi+0x10],eax
.L580267:
 mov    eax,DWORD PTR [ecx+0x8d4]
.L58026d:
 push   0x9fe740
.L580272:
 push   DWORD PTR [esi+0x10]
.L580275:
 mov    DWORD PTR [esi+0x14],eax
.L580278:
 call target_542340
.L58027d:
 push   0xa01690
.L580282:
 push   DWORD PTR [esi+0x10]
.L580285:
 mov    DWORD PTR [esi+0x60],eax
.L580288:
 call target_542340
.L58028d:
 push   0xa0169c
.L580292:
 push   DWORD PTR [esi+0x10]
.L580295:
 mov    DWORD PTR [esi+0x64],eax
.L580298:
 call target_542340
.L58029d:
 push   0xa019f4
.L5802a2:
 push   DWORD PTR [esi+0x10]
.L5802a5:
 mov    DWORD PTR [esi+0x68],eax
.L5802a8:
 call target_542340
.L5802ad:
 {load} mov    ecx,esi
.L5802af:
 mov    DWORD PTR [esi+0x6c],eax
.L5802b2:
 call target_542230
.L5802b7:
 {load} mov    eax,esi
.L5802b9:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5802bc:
 mov    DWORD PTR fs:0x0,ecx
.L5802c3:
 pop    ecx
.L5802c4:
 pop    esi
.L5802c5:
 {load} mov    esp,ebp
.L5802c7:
 pop    ebp
.L5802c8:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
