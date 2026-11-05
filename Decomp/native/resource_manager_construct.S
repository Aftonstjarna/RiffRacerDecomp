# Mechanically transcribed reference evidence, NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x417810..0x4178e9 exclusive; adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_resource_manager_construct
original_resource_manager_construct:
.L417810:
 push   ebp
.L417811:
 {load} mov    ebp,esp
.L417813:
 push   0xffffffff
.L417815:
 push   0x8fd7f9
.L41781a:
 mov    eax,fs:0x0
.L417820:
 push   eax
.L417821:
 push   ecx
.L417822:
 push   ebx
.L417823:
 push   esi
.L417824:
 push   edi
.L417825:
 mov    eax,DWORD PTR [0xbaabc0]
.L41782a:
 {load} xor    eax,ebp
.L41782c:
 push   eax
.L41782d:
 lea    eax,[ebp-0xc]
.L417830:
 mov    fs:0x0,eax
.L417836:
 {load} mov    esi,ecx
.L417838:
 mov    DWORD PTR [ebp-0x10],esi
.L41783b:
 mov    DWORD PTR [esi],0x0
.L417841:
 mov    DWORD PTR [esi+0x4],0x0
.L417848:
 mov    DWORD PTR [esi+0x8],0x0
.L41784f:
 mov    DWORD PTR [ebp-0x4],0x0
.L417856:
 mov    DWORD PTR [esi+0xc],0x0
.L41785d:
 mov    DWORD PTR [esi+0x10],0x0
.L417864:
 mov    DWORD PTR [esi+0x14],0x0
.L41786b:
 mov    DWORD PTR [esi+0x18],0x0
.L417872:
 mov    DWORD PTR [esi+0x1c],0x0
.L417879:
 mov    DWORD PTR [esi+0x20],0x0
.L417880:
 mov    DWORD PTR [esi+0x24],0x0
.L417887:
 mov    DWORD PTR [esi+0x28],0x0
.L41788e:
 mov    DWORD PTR [esi+0x2c],0x0
.L417895:
 mov    edx,DWORD PTR [ebp+0x8]
.L417898:
 {load} xor    eax,eax
.L41789a:
 mov    BYTE PTR [ebp-0x4],0x3
.L41789e:
 mov    DWORD PTR [esi+0x30],eax
.L4178a1:
 mov    DWORD PTR [esi+0x34],eax
.L4178a4:
 mov    DWORD PTR [esi+0x4c],0xf
.L4178ab:
 mov    DWORD PTR [esi+0x48],eax
.L4178ae:
 mov    BYTE PTR [esi+0x38],al
.L4178b1:
 cmp    BYTE PTR [edx],al
.L4178b3:
 je     .L4178c9
.L4178b5:
 {load} mov    eax,edx
.L4178b7:
 lea    ebx,[eax+0x1]
.L4178ba:
 {disp32} lea    ebx,[ebx+0x0]
.L4178c0:
 mov    cl,BYTE PTR [eax]
.L4178c2:
 inc    eax
.L4178c3:
 test   cl,cl
.L4178c5:
 jne    .L4178c0
.L4178c7:
 {load} sub    eax,ebx
.L4178c9:
 push   eax
.L4178ca:
 push   edx
.L4178cb:
 lea    ecx,[esi+0x38]
.L4178ce:
 call   target_416520
.L4178d3:
 {load} mov    eax,esi
.L4178d5:
 mov    ecx,DWORD PTR [ebp-0xc]
.L4178d8:
 mov    DWORD PTR fs:0x0,ecx
.L4178df:
 pop    ecx
.L4178e0:
 pop    edi
.L4178e1:
 pop    esi
.L4178e2:
 pop    ebx
.L4178e3:
 {load} mov    esp,ebp
.L4178e5:
 pop    ebp
.L4178e6:
 ret    0x4
.equ target_416520,0x416520
.section .note.GNU-stack,"",@progbits
