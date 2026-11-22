# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x580810,0x58093d); instruction-contiguous extent, INT3 padding excluded.
# Shader skinning parameter update: the routine references the original skinMatrixArray literal and maintains its shader parameter path. Called from the shader-binding references; the exact device interface remains external.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x580810..0x58093d
.intel_syntax noprefix
.code32
.text
.global original_shader_skin_matrix_array_set
original_shader_skin_matrix_array_set:
.L580810:
 push   ebp
.L580811:
 {load} mov    ebp,esp
.L580813:
 push   0xffffffff
.L580815:
 push   0x905468
.L58081a:
 mov    eax,fs:0x0
.L580820:
 push   eax
.L580821:
 sub    esp,0x8
.L580824:
 push   esi
.L580825:
 mov    eax,[0xbaabc0]
.L58082a:
 {load} xor    eax,ebp
.L58082c:
 push   eax
.L58082d:
 lea    eax,[ebp-0xc]
.L580830:
 mov    fs:0x0,eax
.L580836:
 {load} mov    esi,ecx
.L580838:
 mov    DWORD PTR [ebp-0x10],esi
.L58083b:
 call target_5421b0
.L580840:
 mov    edx,DWORD PTR [ebp+0x8]
.L580843:
 mov    DWORD PTR [ebp-0x4],0x0
.L58084a:
 mov    ecx,DWORD PTR [0xbfcd04]
.L580850:
 mov    DWORD PTR [esi+0xa0],edx
.L580856:
 {load} add    edx,edx
.L580858:
 mov    DWORD PTR [esi],0xa023b8
.L58085e:
 mov    DWORD PTR [esi+0x98],0x0
.L580868:
 mov    DWORD PTR [esi+0x94],0x0
.L580872:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L580876:
 mov    DWORD PTR [esi+0x90],0x0
.L580880:
 mov    DWORD PTR [esi+0x8c],0x0
.L58088a:
 mov    DWORD PTR [esi+0x84],0x0
.L580894:
 mov    DWORD PTR [esi+0x80],0x0
.L58089e:
 mov    DWORD PTR [esi+0x7c],0x0
.L5808a5:
 mov    DWORD PTR [esi+0x78],0x0
.L5808ac:
 mov    DWORD PTR [esi+0x70],0x0
.L5808b3:
 mov    DWORD PTR [esi+0x6c],0x0
.L5808ba:
 mov    DWORD PTR [esi+0x68],0x0
.L5808c1:
 mov    DWORD PTR [esi+0x64],0x0
.L5808c8:
 mov    DWORD PTR [esi+0x9c],0x3f800000
.L5808d2:
 mov    DWORD PTR [esi+0x88],0x3f800000
.L5808dc:
 mov    DWORD PTR [esi+0x74],0x3f800000
.L5808e3:
 mov    DWORD PTR [esi+0x60],0x3f800000
.L5808ea:
 mov    DWORD PTR [esi+0x4],eax
.L5808ed:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L5808f1:
 mov    DWORD PTR [esi+0x8],eax
.L5808f4:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L5808f8:
 mov    DWORD PTR [esi+0x10],eax
.L5808fb:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L5808ff:
 push   0x9fe740
.L580904:
 push   DWORD PTR [esi+0x10]
.L580907:
 mov    DWORD PTR [esi+0x14],eax
.L58090a:
 call target_542340
.L58090f:
 push   0xa00048
.L580914:
 push   DWORD PTR [esi+0x10]
.L580917:
 mov    DWORD PTR [esi+0x58],eax
.L58091a:
 call target_542340
.L58091f:
 {load} mov    ecx,esi
.L580921:
 mov    DWORD PTR [esi+0x5c],eax
.L580924:
 call target_542230
.L580929:
 {load} mov    eax,esi
.L58092b:
 mov    ecx,DWORD PTR [ebp-0xc]
.L58092e:
 mov    DWORD PTR fs:0x0,ecx
.L580935:
 pop    ecx
.L580936:
 pop    esi
.L580937:
 {load} mov    esp,ebp
.L580939:
 pop    ebp
.L58093a:
 ret    0x4
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
