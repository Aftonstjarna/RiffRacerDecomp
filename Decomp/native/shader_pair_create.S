# Reviewed original instructions and Ghidra control flow; see SHADERS.md.
# Original VA range 0x52d840..0x52d8fd
.intel_syntax noprefix
.code32
.text
.global original_shader_pair_create
original_shader_pair_create:
.L52d840:
 push   ebp
.L52d841:
 {load} mov    ebp,esp
.L52d843:
 mov    eax,[0xbfcc44]
.L52d848:
 push   ebx
.L52d849:
 mov    ebx,DWORD PTR [ebp+0x8]
.L52d84c:
 push   esi
.L52d84d:
 mov    eax,DWORD PTR [eax+0x78]
.L52d850:
 {load} mov    esi,ecx
.L52d852:
 push   edi
.L52d853:
 push   esi
.L52d854:
 push   ebx
.L52d855:
 mov    edx,DWORD PTR [eax]
.L52d857:
 push   eax
.L52d858:
 call   DWORD PTR [edx+0x16c]
.L52d85e:
 test   eax,eax
.L52d860:
 js .L52d8eb
.L52d866:
 lea    edi,[esi+0x4]
.L52d869:
 push   edi
.L52d86a:
 push   ebx
.L52d86b:
 call   DWORD PTR [0x92d64c]
.L52d871:
 test   eax,eax
.L52d873:
 jns .L52d88c
.L52d875:
 mov    eax,DWORD PTR [esi]
.L52d877:
 push   eax
.L52d878:
 mov    ecx,DWORD PTR [eax]
.L52d87a:
 call   DWORD PTR [ecx+0x8]
.L52d87d:
 pop    edi
.L52d87e:
 mov    DWORD PTR [esi],0x0
.L52d884:
 {load} xor    al,al
.L52d886:
 pop    esi
.L52d887:
 pop    ebx
.L52d888:
 pop    ebp
.L52d889:
 ret    0x8
.L52d88c:
 mov    eax,[0xbfcc44]
.L52d891:
 lea    ebx,[esi+0x8]
.L52d894:
 push   ebx
.L52d895:
 push   DWORD PTR [ebp+0xc]
.L52d898:
 mov    eax,DWORD PTR [eax+0x78]
.L52d89b:
 push   eax
.L52d89c:
 mov    ecx,DWORD PTR [eax]
.L52d89e:
 call   DWORD PTR [ecx+0x1a8]
.L52d8a4:
 test   eax,eax
.L52d8a6:
 js .L52d8c7
.L52d8a8:
 lea    eax,[ebx+0x4]
.L52d8ab:
 push   eax
.L52d8ac:
 push   DWORD PTR [ebp+0xc]
.L52d8af:
 call   DWORD PTR [0x92d64c]
.L52d8b5:
 test   eax,eax
.L52d8b7:
 jns .L52d8f4
.L52d8b9:
 mov    eax,DWORD PTR [ebx]
.L52d8bb:
 push   eax
.L52d8bc:
 mov    ecx,DWORD PTR [eax]
.L52d8be:
 call   DWORD PTR [ecx+0x8]
.L52d8c1:
 mov    DWORD PTR [ebx],0x0
.L52d8c7:
 mov    ecx,DWORD PTR [edi]
.L52d8c9:
 test   ecx,ecx
.L52d8cb:
 je .L52d8d3
.L52d8cd:
 mov    eax,DWORD PTR [ecx]
.L52d8cf:
 push   ecx
.L52d8d0:
 call   DWORD PTR [eax+0x8]
.L52d8d3:
 mov    ecx,DWORD PTR [esi]
.L52d8d5:
 mov    DWORD PTR [edi],0x0
.L52d8db:
 test   ecx,ecx
.L52d8dd:
 je .L52d8e5
.L52d8df:
 mov    eax,DWORD PTR [ecx]
.L52d8e1:
 push   ecx
.L52d8e2:
 call   DWORD PTR [eax+0x8]
.L52d8e5:
 mov    DWORD PTR [esi],0x0
.L52d8eb:
 pop    edi
.L52d8ec:
 pop    esi
.L52d8ed:
 {load} xor    al,al
.L52d8ef:
 pop    ebx
.L52d8f0:
 pop    ebp
.L52d8f1:
 ret    0x8
.L52d8f4:
 pop    edi
.L52d8f5:
 pop    esi
.L52d8f6:
 mov    al,0x1
.L52d8f8:
 pop    ebx
.L52d8f9:
 pop    ebp
.L52d8fa:
 ret    0x8
