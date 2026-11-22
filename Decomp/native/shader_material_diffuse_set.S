# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x580ad0,0x580c33); instruction-contiguous extent, INT3 padding excluded.
# Shader material parameter update: references the original diffuse literal and the shared shader-parameter tables, with the original SEH frame and helper calls. Exact material field semantics remain unproven.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x580ad0..0x580c33
.intel_syntax noprefix
.code32
.text
.global original_shader_material_diffuse_set
original_shader_material_diffuse_set:
.L580ad0:
 push   ebp
.L580ad1:
 {load} mov    ebp,esp
.L580ad3:
 push   0xffffffff
.L580ad5:
 push   0x907fe8
.L580ada:
 mov    eax,fs:0x0
.L580ae0:
 push   eax
.L580ae1:
 push   ecx
.L580ae2:
 push   esi
.L580ae3:
 mov    eax,[0xbaabc0]
.L580ae8:
 {load} xor    eax,ebp
.L580aea:
 push   eax
.L580aeb:
 lea    eax,[ebp-0xc]
.L580aee:
 mov    fs:0x0,eax
.L580af4:
 {load} mov    esi,ecx
.L580af6:
 mov    DWORD PTR [ebp-0x10],esi
.L580af9:
 call target_5421b0
.L580afe:
 mov    eax,DWORD PTR [ebp+0xc]
.L580b01:
 mov    DWORD PTR [ebp-0x4],0x0
.L580b08:
 mov    ecx,DWORD PTR [0xbfcd04]
.L580b0e:
 mov    edx,DWORD PTR [ebp+0x8]
.L580b11:
 mov    DWORD PTR [esi],0xa02414
.L580b17:
 {load} add    edx,edx
.L580b19:
 movss  xmm0,DWORD PTR [eax+0x4]
.L580b1e:
 movss  xmm1,DWORD PTR [eax+0x8]
.L580b23:
 movss  xmm2,DWORD PTR [eax+0xc]
.L580b28:
 mov    eax,DWORD PTR [eax]
.L580b2a:
 mov    DWORD PTR [esi+0x58],eax
.L580b2d:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L580b31:
 movss  DWORD PTR [esi+0x5c],xmm0
.L580b36:
 movss  DWORD PTR [esi+0x60],xmm1
.L580b3b:
 movss  DWORD PTR [esi+0x64],xmm2
.L580b40:
 mov    DWORD PTR [esi+0xa8],0x0
.L580b4a:
 mov    DWORD PTR [esi+0xa4],0x0
.L580b54:
 mov    DWORD PTR [esi+0xa0],0x0
.L580b5e:
 mov    DWORD PTR [esi+0x9c],0x0
.L580b68:
 mov    DWORD PTR [esi+0x94],0x0
.L580b72:
 mov    DWORD PTR [esi+0x90],0x0
.L580b7c:
 mov    DWORD PTR [esi+0x8c],0x0
.L580b86:
 mov    DWORD PTR [esi+0x88],0x0
.L580b90:
 mov    DWORD PTR [esi+0x80],0x0
.L580b9a:
 mov    DWORD PTR [esi+0x7c],0x0
.L580ba1:
 mov    DWORD PTR [esi+0x78],0x0
.L580ba8:
 mov    DWORD PTR [esi+0x74],0x0
.L580baf:
 mov    DWORD PTR [esi+0xac],0x3f800000
.L580bb9:
 mov    DWORD PTR [esi+0x98],0x3f800000
.L580bc3:
 mov    DWORD PTR [esi+0x84],0x3f800000
.L580bcd:
 mov    DWORD PTR [esi+0x70],0x3f800000
.L580bd4:
 mov    DWORD PTR [esi+0x4],eax
.L580bd7:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L580bdb:
 mov    DWORD PTR [esi+0x8],eax
.L580bde:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L580be2:
 mov    DWORD PTR [esi+0x10],eax
.L580be5:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L580be9:
 push   0x9fe740
.L580bee:
 push   DWORD PTR [esi+0x10]
.L580bf1:
 mov    DWORD PTR [esi+0x14],eax
.L580bf4:
 call target_542340
.L580bf9:
 push   0xa016bc
.L580bfe:
 push   DWORD PTR [esi+0x14]
.L580c01:
 mov    DWORD PTR [esi+0x68],eax
.L580c04:
 call target_542340
.L580c09:
 push   0xa0246c
.L580c0e:
 push   DWORD PTR [esi+0x14]
.L580c11:
 mov    DWORD PTR [esi+0x6c],eax
.L580c14:
 call target_542340
.L580c19:
 mov    DWORD PTR [esi+0xb0],eax
.L580c1f:
 {load} mov    eax,esi
.L580c21:
 mov    ecx,DWORD PTR [ebp-0xc]
.L580c24:
 mov    DWORD PTR fs:0x0,ecx
.L580c2b:
 pop    ecx
.L580c2c:
 pop    esi
.L580c2d:
 {load} mov    esp,ebp
.L580c2f:
 pop    ebp
.L580c30:
 ret    0x8
.equ target_5421b0,0x5421b0
.equ target_542340,0x542340
