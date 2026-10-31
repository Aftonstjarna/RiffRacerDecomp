# Reviewed against original instructions and Ghidra export; see SHADERS.md.
# Original VA range 0x5788c0..0x578955
.intel_syntax noprefix
.code32
.text
.global original_shader_drift_ctor
original_shader_drift_ctor:
.L5788c0:
 push   ebp
.L5788c1:
 {load} mov    ebp,esp
.L5788c3:
 push   0xffffffff
.L5788c5:
 push   0x905468
.L5788ca:
 mov    eax,fs:0x0
.L5788d0:
 push   eax
.L5788d1:
 sub    esp,0x8
.L5788d4:
 push   esi
.L5788d5:
 mov    eax,[0xbaabc0]
.L5788da:
 {load} xor    eax,ebp
.L5788dc:
 push   eax
.L5788dd:
 lea    eax,[ebp-0xc]
.L5788e0:
 mov    fs:0x0,eax
.L5788e6:
 {load} mov    esi,ecx
.L5788e8:
 mov    DWORD PTR [ebp-0x10],esi
.L5788eb:
 push   0xe0
.L5788f0:
 call target_52ca50
.L5788f5:
 mov    DWORD PTR [ebp-0x4],0x0
.L5788fc:
 mov    eax,DWORD PTR [esi+0x10]
.L5788ff:
 push   0xa0178c
.L578904:
 mov    DWORD PTR [esi],0xa01734
.L57890a:
 push   0x0
.L57890c:
 mov    ecx,DWORD PTR [eax]
.L57890e:
 push   eax
.L57890f:
 call   DWORD PTR [ecx+0x24]
.L578912:
 mov    DWORD PTR [esi+0x15c],eax
.L578918:
 mov    eax,DWORD PTR [esi+0x14]
.L57891b:
 push   0xa0178c
.L578920:
 push   0x0
.L578922:
 push   eax
.L578923:
 mov    ecx,DWORD PTR [eax]
.L578925:
 call   DWORD PTR [ecx+0x24]
.L578928:
 push   0x40
.L57892a:
 mov    DWORD PTR [esi+0x160],eax
.L578930:
 lea    eax,[esi+0x164]
.L578936:
 push   0x0
.L578938:
 push   eax
.L578939:
 call target_8f8d7e
.L57893e:
 add    esp,0xc
.L578941:
 {load} mov    eax,esi
.L578943:
 mov    ecx,DWORD PTR [ebp-0xc]
.L578946:
 mov    DWORD PTR fs:0x0,ecx
.L57894d:
 pop    ecx
.L57894e:
 pop    esi
.L57894f:
 {load} mov    esp,ebp
.L578951:
 pop    ebp
.L578952:
 ret    0x4
.equ target_52ca50,0x52ca50
.equ target_8f8d7e,0x8f8d7e
