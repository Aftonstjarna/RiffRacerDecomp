# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x4f87e0,0x4f8a89); instruction-contiguous extent, INT3 padding excluded.
# Decode worker name release: observes the worker global at 0xBFCD24 and releases the stored name through the original delete/free paths. Called from the decode worker dispatch.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x4f87e0..0x4f8a89
.intel_syntax noprefix
.code32
.text
.global original_decode_worker_name_free
original_decode_worker_name_free:
.L4f87e0:
 push   ebp
.L4f87e1:
 {load} mov    ebp,esp
.L4f87e3:
 and    esp,0xfffffff8
.L4f87e6:
 sub    esp,0x1c
.L4f87e9:
 cmp    DWORD PTR [0xbfcd24],0x0
.L4f87f0:
 push   ebx
.L4f87f1:
 push   esi
.L4f87f2:
 push   edi
.L4f87f3:
 {load} mov    edi,edx
.L4f87f5:
 {load} mov    ebx,ecx
.L4f87f7:
 jne .L4f8812
.L4f87f9:
 call target_596220
.L4f87fe:
 call target_590fc0
.L4f8803:
 call target_590ad0
.L4f8808:
 mov    DWORD PTR [0xbfcd24],0x1
.L4f8812:
 push   ecx
.L4f8813:
 {load} xor    ecx,ecx
.L4f8815:
 call target_55be40
.L4f881a:
 {load} mov    esi,eax
.L4f881c:
 add    esp,0x4
.L4f881f:
 test   esi,esi
.L4f8821:
 je .L4f8848
.L4f8823:
 {load} mov    ecx,esi
.L4f8825:
 call target_55c990
.L4f882a:
 push   esi
.L4f882b:
 mov    DWORD PTR [esi+0x6d3c],0xbaf500
.L4f8835:
 mov    DWORD PTR [esi+0x6d50],0x0
.L4f883f:
 call   DWORD PTR [0xbaf500]
.L4f8845:
 add    esp,0x4
.L4f8848:
 {load} mov    ecx,esi
.L4f884a:
 call target_55cff0
.L4f884f:
 test   esi,esi
.L4f8851:
 je .L4f8889
.L4f8853:
 mov    edx,DWORD PTR [ebp+0x8]
.L4f8856:
 lea    ecx,[esi+0x6da8]
.L4f885c:
 sub    esp,0x8
.L4f885f:
 call target_55d0e0
.L4f8864:
 add    esp,0x8
.L4f8867:
 test   eax,eax
.L4f8869:
 je .L4f8892
.L4f886b:
 mov    DWORD PTR [esi+0x6ed8],eax
.L4f8871:
 {load} mov    ecx,esi
.L4f8873:
 call target_55c990
.L4f8878:
 {load} mov    ecx,esi
.L4f887a:
 call target_58a800
.L4f887f:
 push   esi
.L4f8880:
 call   DWORD PTR [0x92d3a4]
.L4f8886:
 add    esp,0x4
.L4f8889:
 {load} xor    al,al
.L4f888b:
 pop    edi
.L4f888c:
 pop    esi
.L4f888d:
 pop    ebx
.L4f888e:
 {load} mov    esp,ebp
.L4f8890:
 pop    ebp
.L4f8891:
 ret
.L4f8892:
 test   edi,edi
.L4f8894:
 je .L4f88be
.L4f8896:
 test   ebx,ebx
.L4f8898:
 je .L4f8923
.L4f889e:
 push   edi
.L4f889f:
 {load} mov    edx,ebx
.L4f88a1:
 {load} mov    ecx,esi
.L4f88a3:
 call target_58e250
.L4f88a8:
 add    esp,0x4
.L4f88ab:
 test   eax,eax
.L4f88ad:
 jne .L4f8871
.L4f88af:
 cmp    DWORD PTR [esi+0x6ed8],0x12
.L4f88b6:
 jne .L4f88be
.L4f88b8:
 mov    DWORD PTR [esi+0x6ed8],eax
.L4f88be:
 {load} mov    ecx,esi
.L4f88c0:
 call target_55c720
.L4f88c5:
 mov    DWORD PTR [esp+0x14],eax
.L4f88c9:
 test   eax,eax
.L4f88cb:
 js .L4f8871
.L4f88cd:
 jne .L4f88da
.L4f88cf:
 imul   eax,DWORD PTR [ebp+0x8],0x3c0
.L4f88d6:
 mov    DWORD PTR [esp+0x14],eax
.L4f88da:
 {load} xor    ecx,ecx
.L4f88dc:
 mov    edx,0x4
.L4f88e1:
 mul    edx
.L4f88e3:
 seto   cl
.L4f88e6:
 neg    ecx
.L4f88e8:
 {load} or     ecx,eax
.L4f88ea:
 push   ecx
.L4f88eb:
 call target_8f87c8
.L4f88f0:
 add    esp,0x4
.L4f88f3:
 mov    DWORD PTR [esp+0x10],eax
.L4f88f7:
 {load} xor    edi,edi
.L4f88f9:
 mov    DWORD PTR [esp+0x18],edi
.L4f88fd:
 {disp8} lea    ecx,[ecx+0x0]
.L4f8900:
 lea    eax,[esp+0x1c]
.L4f8904:
 {load} mov    ecx,esi
.L4f8906:
 push   eax
.L4f8907:
 lea    eax,[esp+0x24]
.L4f890b:
 push   eax
.L4f890c:
 call target_55c360
.L4f8911:
 add    esp,0x8
.L4f8914:
 cmp    eax,0xfffffff5
.L4f8917:
 jne .L4f8932
.L4f8919:
 mov    DWORD PTR [esp+0x1c],0x1
.L4f8921:
 jmp .L4f8900
.L4f8923:
 mov    DWORD PTR [esi+0x6ed8],0x1f
.L4f892d:
 jmp .L4f8871
.L4f8932:
 mov    ebx,DWORD PTR [esp+0x1c]
.L4f8936:
 test   eax,eax
.L4f8938:
 jne .L4f89cd
.L4f893e:
 mov    ecx,DWORD PTR [esp+0x14]
.L4f8942:
 {load} mov    eax,ebx
.L4f8944:
 shr    eax,0x2
.L4f8947:
 {load} add    eax,edi
.L4f8949:
 mov    DWORD PTR [esp+0x24],eax
.L4f894d:
 {load} cmp    eax,ecx
.L4f894f:
 jbe .L4f89b0
.L4f8951:
 mov    eax,0x66666667
.L4f8956:
 imul   ecx
.L4f8958:
 sar    edx,0x2
.L4f895b:
 {load} mov    eax,edx
.L4f895d:
 shr    eax,0x1f
.L4f8960:
 {load} add    eax,edx
.L4f8962:
 mov    edx,0x4
.L4f8967:
 {load} add    ecx,eax
.L4f8969:
 mov    DWORD PTR [esp+0x14],ecx
.L4f896d:
 {load} xor    ecx,ecx
.L4f896f:
 mov    eax,DWORD PTR [esp+0x14]
.L4f8973:
 mul    edx
.L4f8975:
 seto   cl
.L4f8978:
 neg    ecx
.L4f897a:
 {load} or     ecx,eax
.L4f897c:
 push   ecx
.L4f897d:
 call target_8f87c8
.L4f8982:
 mov    ecx,DWORD PTR [esp+0x1c]
.L4f8986:
 {load} mov    edi,eax
.L4f8988:
 shl    ecx,0x2
.L4f898b:
 push   ecx
.L4f898c:
 mov    ecx,DWORD PTR [esp+0x18]
.L4f8990:
 push   ecx
.L4f8991:
 push   edi
.L4f8992:
 call target_8f8d66
.L4f8997:
 push   DWORD PTR [esp+0x20]
.L4f899b:
 call   DWORD PTR [0x92d4a0]
.L4f89a1:
 {load} mov    eax,edi
.L4f89a3:
 add    esp,0x14
.L4f89a6:
 mov    edi,DWORD PTR [esp+0x18]
.L4f89aa:
 mov    DWORD PTR [esp+0x10],eax
.L4f89ae:
 jmp .L4f89b4
.L4f89b0:
 mov    eax,DWORD PTR [esp+0x10]
.L4f89b4:
 push   ebx
.L4f89b5:
 push   DWORD PTR [esp+0x24]
.L4f89b9:
 lea    eax,[eax+edi*4]
.L4f89bc:
 push   eax
.L4f89bd:
 call target_8f8d66
.L4f89c2:
 mov    edi,DWORD PTR [esp+0x30]
.L4f89c6:
 add    esp,0xc
.L4f89c9:
 mov    DWORD PTR [esp+0x18],edi
.L4f89cd:
 test   ebx,ebx
.L4f89cf:
 jne .L4f8900
.L4f89d5:
 lea    eax,[esp+0x1c]
.L4f89d9:
 mov    DWORD PTR [esp+0x18],ebx
.L4f89dd:
 push   eax
.L4f89de:
 lea    edx,[esp+0x1c]
.L4f89e2:
 mov    DWORD PTR [esp+0x20],ebx
.L4f89e6:
 {load} mov    ecx,esi
.L4f89e8:
 call target_55c910
.L4f89ed:
 mov    ebx,DWORD PTR [esp+0x20]
.L4f89f1:
 add    esp,0x4
.L4f89f4:
 test   ebx,ebx
.L4f89f6:
 je .L4f8a22
.L4f89f8:
 mov    eax,DWORD PTR [ebx+0x4]
.L4f89fb:
 test   eax,eax
.L4f89fd:
 je .L4f8a22
.L4f89ff:
 push   0x100
.L4f8a04:
 push   DWORD PTR [eax]
.L4f8a06:
 push   DWORD PTR [ebp+0x14]
.L4f8a09:
 call   DWORD PTR [0x92d3e4]
.L4f8a0f:
 mov    eax,DWORD PTR [ebx+0x8]
.L4f8a12:
 add    esp,0xc
.L4f8a15:
 test   eax,eax
.L4f8a17:
 je .L4f8a5a
.L4f8a19:
 push   0x100
.L4f8a1e:
 push   DWORD PTR [eax]
.L4f8a20:
 jmp .L4f8a4e
.L4f8a22:
 mov    ebx,DWORD PTR [esp+0x18]
.L4f8a26:
 test   ebx,ebx
.L4f8a28:
 je .L4f8a5a
.L4f8a2a:
 lea    eax,[ebx+0x3]
.L4f8a2d:
 test   eax,eax
.L4f8a2f:
 je .L4f8a5a
.L4f8a31:
 push   0x100
.L4f8a36:
 push   eax
.L4f8a37:
 push   DWORD PTR [ebp+0x14]
.L4f8a3a:
 call   DWORD PTR [0x92d3e4]
.L4f8a40:
 add    esp,0xc
.L4f8a43:
 add    ebx,0x21
.L4f8a46:
 je .L4f8a5a
.L4f8a48:
 push   0x100
.L4f8a4d:
 push   ebx
.L4f8a4e:
 push   DWORD PTR [ebp+0x1c]
.L4f8a51:
 call   DWORD PTR [0x92d3e4]
.L4f8a57:
 add    esp,0xc
.L4f8a5a:
 mov    eax,DWORD PTR [ebp+0xc]
.L4f8a5d:
 mov    ecx,DWORD PTR [esp+0x10]
.L4f8a61:
 mov    DWORD PTR [eax],ecx
.L4f8a63:
 {load} mov    ecx,esi
.L4f8a65:
 mov    eax,DWORD PTR [ebp+0x10]
.L4f8a68:
 mov    DWORD PTR [eax],edi
.L4f8a6a:
 call target_55c990
.L4f8a6f:
 {load} mov    ecx,esi
.L4f8a71:
 call target_58a800
.L4f8a76:
 push   esi
.L4f8a77:
 call   DWORD PTR [0x92d3a4]
.L4f8a7d:
 add    esp,0x4
.L4f8a80:
 mov    al,0x1
.L4f8a82:
 pop    edi
.L4f8a83:
 pop    esi
.L4f8a84:
 pop    ebx
.L4f8a85:
 {load} mov    esp,ebp
.L4f8a87:
 pop    ebp
.L4f8a88:
 ret
.equ target_55be40,0x55be40
.equ target_55c360,0x55c360
.equ target_55c720,0x55c720
.equ target_55c910,0x55c910
.equ target_55c990,0x55c990
.equ target_55cff0,0x55cff0
.equ target_55d0e0,0x55d0e0
.equ target_58a800,0x58a800
.equ target_58e250,0x58e250
.equ target_590ad0,0x590ad0
.equ target_590fc0,0x590fc0
.equ target_596220,0x596220
.equ target_8f87c8,0x8f87c8
.equ target_8f8d66,0x8f8d66
