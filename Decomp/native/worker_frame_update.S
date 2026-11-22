# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x4987c0,0x498cbc); instruction-contiguous extent, padding excluded.
# Worker active-frame update reached by the frame step: SEH frame, imports including thread/alloc
# slots, calls 0x42BFD0, 0x4979F0, 0x498CC0 and 0x49A940. Complete body with all return paths;
# callee implementations remain external dependencies.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x4987c0..0x498cbc
.intel_syntax noprefix
.code32
.text
.global original_worker_frame_update
original_worker_frame_update:
.L4987c0:
 push   ebp
.L4987c1:
 {load} mov    ebp,esp
.L4987c3:
 and    esp,0xfffffff8
.L4987c6:
 push   0xffffffff
.L4987c8:
 push   0x90218c
.L4987cd:
 mov    eax,fs:0x0
.L4987d3:
 push   eax
.L4987d4:
 sub    esp,0x8
.L4987d7:
 push   ebx
.L4987d8:
 push   esi
.L4987d9:
 push   edi
.L4987da:
 mov    eax,[0xbaabc0]
.L4987df:
 {load} xor    eax,esp
.L4987e1:
 push   eax
.L4987e2:
 lea    eax,[esp+0x18]
.L4987e6:
 mov    fs:0x0,eax
.L4987ec:
 {load} mov    edi,ecx
.L4987ee:
 mov    ebx,DWORD PTR [0xbfcb48]
.L4987f4:
 test   ebx,ebx
.L4987f6:
 jne .L49882a
.L4987f8:
 push   0x18
.L4987fa:
 call   DWORD PTR [0x92d4b4]
.L498800:
 add    esp,0x4
.L498803:
 mov    DWORD PTR [esp+0x10],eax
.L498807:
 mov    DWORD PTR [esp+0x20],ebx
.L49880b:
 test   eax,eax
.L49880d:
 je .L49881a
.L49880f:
 {load} mov    ecx,eax
.L498811:
 call target_42bfd0
.L498816:
 {load} mov    ebx,eax
.L498818:
 jmp .L49881c
.L49881a:
 {load} xor    ebx,ebx
.L49881c:
 mov    DWORD PTR [esp+0x20],0xffffffff
.L498824:
 mov    DWORD PTR [0xbfcb48],ebx
.L49882a:
 mov    esi,DWORD PTR [ebx]
.L49882c:
 cmp    esi,DWORD PTR [ebx+0x4]
.L49882f:
 je .L49887b
.L498831:
 mov    eax,DWORD PTR [esi]
.L498833:
 cmp    BYTE PTR [eax+0x1c4],0x0
.L49883a:
 je .L498873
.L49883c:
 cmp    BYTE PTR [ebp+0x8],0x0
.L498840:
 mov    ecx,DWORD PTR [eax+0x180]
.L498846:
 je .L498852
.L498848:
 test   ecx,0x1000
.L49884e:
 je .L498873
.L498850:
 jmp .L49885a
.L498852:
 test   ecx,0x1000
.L498858:
 jne .L498873
.L49885a:
 test   ecx,0x60000000
.L498860:
 jne .L498873
.L498862:
 cmp    DWORD PTR [eax+0x1c0],0x0
.L498869:
 jne .L498873
.L49886b:
 push   eax
.L49886c:
 {load} mov    ecx,edi
.L49886e:
 call target_4979f0
.L498873:
 add    esi,0x4
.L498876:
 cmp    esi,DWORD PTR [ebx+0x4]
.L498879:
 jne .L498831
.L49887b:
 mov    bl,BYTE PTR [ebp+0x8]
.L49887e:
 test   bl,bl
.L498880:
 jne .L498889
.L498882:
 {load} mov    ecx,edi
.L498884:
 call target_498cc0
.L498889:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L49888f:
 mov    eax,DWORD PTR [edi+0x9c]
.L498895:
 mov    DWORD PTR [ecx+0x70],eax
.L498898:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L49889e:
 mov    eax,DWORD PTR [edi+0x1c]
.L4988a1:
 mov    DWORD PTR [ecx+0x74],eax
.L4988a4:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4988aa:
 mov    eax,DWORD PTR [edi+0x20]
.L4988ad:
 mov    DWORD PTR [ecx+0x78],eax
.L4988b0:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4988b6:
 mov    eax,DWORD PTR [edi+0x2cd4]
.L4988bc:
 mov    DWORD PTR [ecx+0x7c],eax
.L4988bf:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4988c5:
 mov    eax,DWORD PTR [edi+0xc]
.L4988c8:
 mov    DWORD PTR [ecx+0x84],eax
.L4988ce:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4988d4:
 mov    eax,DWORD PTR [edi+0x24]
.L4988d7:
 mov    DWORD PTR [ecx+0x80],eax
.L4988dd:
 mov    eax,DWORD PTR [edi+0x2cd8]
.L4988e3:
 lea    eax,[eax+eax*2]
.L4988e6:
 lea    eax,[eax+0xb27]
.L4988ec:
 lea    ecx,[edi+eax*4]
.L4988ef:
 mov    eax,DWORD PTR [edi+0x2ccc]
.L4988f5:
 mov    DWORD PTR [eax+0x94],ecx
.L4988fb:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L498901:
 mov    eax,DWORD PTR [edi+0x10]
.L498904:
 mov    DWORD PTR [ecx+0x88],eax
.L49890a:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L498910:
 mov    eax,DWORD PTR [edi+0x28]
.L498913:
 mov    DWORD PTR [ecx+0x8c],eax
.L498919:
 mov    eax,DWORD PTR [edi+0x2ccc]
.L49891f:
 mov    BYTE PTR [eax+0x90],bl
.L498925:
 mov    eax,DWORD PTR [edi+0x2ccc]
.L49892b:
 movdqu xmm0,XMMWORD PTR [edi+0x2928]
.L498933:
 movdqu XMMWORD PTR [eax+0x60],xmm0
.L498938:
 cmp    BYTE PTR [edi+0x2e20],0x0
.L49893f:
 je .L49899b
.L498941:
 mov    eax,DWORD PTR [edi+0x2ccc]
.L498947:
 {load} xor    esi,esi
.L498949:
 mov    ecx,DWORD PTR [eax+0x4]
.L49894c:
 sub    ecx,DWORD PTR [eax]
.L49894e:
 sar    ecx,0x2
.L498951:
 test   ecx,ecx
.L498953:
 je .L49898d
.L498955:
 {load} mov    ebx,eax
.L498957:
 mov    edx,DWORD PTR [ebx]
.L498959:
 {disp32} lea    esp,[esp+0x0]
.L498960:
 mov    ecx,DWORD PTR [edx]
.L498962:
 cmp    DWORD PTR [ecx+0x5dc],0x0
.L498969:
 jne .L49897d
.L49896b:
 mov    eax,DWORD PTR [ecx+0x5d4]
.L498971:
 cmp    eax,DWORD PTR [edi+0x2e58]
.L498977:
 je .L498b02
.L49897d:
 mov    eax,DWORD PTR [ebx+0x4]
.L498980:
 inc    esi
.L498981:
 sub    eax,DWORD PTR [ebx]
.L498983:
 add    edx,0x4
.L498986:
 sar    eax,0x2
.L498989:
 {load} cmp    esi,eax
.L49898b:
 jb .L498960
.L49898d:
 mov    BYTE PTR [edi+0x2e20],0x0
.L498994:
 and    DWORD PTR [edi+0x2e1c],0xffffffb3
.L49899b:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4989a1:
 lea    edx,[edi+0x2d16]
.L4989a7:
 movzx  eax,BYTE PTR [edi+0x2d13]
.L4989ae:
 mov    BYTE PTR [ecx+0x98],al
.L4989b4:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4989ba:
 movzx  eax,BYTE PTR [edi+0x2d14]
.L4989c1:
 mov    BYTE PTR [ecx+0x99],al
.L4989c7:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4989cd:
 movzx  eax,BYTE PTR [edi+0x2d15]
.L4989d4:
 mov    BYTE PTR [ecx+0x9a],al
.L4989da:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4989e0:
 add    ecx,0x9b
.L4989e6:
 mov    al,BYTE PTR [edx]
.L4989e8:
 lea    edx,[edx+0x1]
.L4989eb:
 mov    BYTE PTR [ecx],al
.L4989ed:
 lea    ecx,[ecx+0x1]
.L4989f0:
 test   al,al
.L4989f2:
 jne .L4989e6
.L4989f4:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L4989fa:
 mov    eax,DWORD PTR [edi+0x2e18]
.L498a00:
 mov    DWORD PTR [ecx+0x19c],eax
.L498a06:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L498a0c:
 mov    eax,DWORD PTR [edi+0x2e1c]
.L498a12:
 mov    DWORD PTR [ecx+0x1a0],eax
.L498a18:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L498a1e:
 mov    al,BYTE PTR [edi+0x2e20]
.L498a24:
 mov    BYTE PTR [ecx+0x1a4],al
.L498a2a:
 mov    ecx,DWORD PTR [edi+0x2ccc]
.L498a30:
 mov    eax,DWORD PTR [edi+0x2e58]
.L498a36:
 mov    DWORD PTR [ecx+0x1a8],eax
.L498a3c:
 mov    DWORD PTR [edi+0x2d13],0x0
.L498a46:
 mov    DWORD PTR [edi+0x2e18],0x0
.L498a50:
 mov    DWORD PTR [edi+0x2e1c],0x0
.L498a5a:
 mov    BYTE PTR [edi+0x2e20],0x0
.L498a61:
 mov    DWORD PTR [edi+0x2e24],0x3f800000
.L498a6b:
 mov    DWORD PTR [edi+0x2e28],0x0
.L498a75:
 mov    DWORD PTR [edi+0x2e2c],0x0
.L498a7f:
 mov    DWORD PTR [edi+0x2e30],0x0
.L498a89:
 mov    DWORD PTR [edi+0x2e34],0x3f800000
.L498a93:
 mov    DWORD PTR [edi+0x2e38],0x0
.L498a9d:
 mov    DWORD PTR [edi+0x2e3c],0x0
.L498aa7:
 mov    DWORD PTR [edi+0x2e40],0x0
.L498ab1:
 mov    DWORD PTR [edi+0x2e44],0x3f800000
.L498abb:
 mov    DWORD PTR [edi+0x2e48],0x0
.L498ac5:
 mov    DWORD PTR [edi+0x2e4c],0x0
.L498acf:
 mov    DWORD PTR [edi+0x2e50],0x0
.L498ad9:
 mov    DWORD PTR [edi+0x2e54],0x0
.L498ae3:
 mov    DWORD PTR [edi+0x2e58],0x0
.L498aed:
 mov    ecx,DWORD PTR [esp+0x18]
.L498af1:
 mov    DWORD PTR fs:0x0,ecx
.L498af8:
 pop    ecx
.L498af9:
 pop    edi
.L498afa:
 pop    esi
.L498afb:
 pop    ebx
.L498afc:
 {load} mov    esp,ebp
.L498afe:
 pop    ebp
.L498aff:
 ret    0x4
.L498b02:
 mov    eax,[0xbfcc44]
.L498b07:
 mov    esi,DWORD PTR [eax+0x1b8]
.L498b0d:
 mov    eax,DWORD PTR [eax+0x1bc]
.L498b13:
 {load} cmp    esi,eax
.L498b15:
 mov    DWORD PTR [edi+0x2e18],0x1
.L498b1f:
 cmova  esi,eax
.L498b22:
 mov    eax,DWORD PTR [edi+0x2e54]
.L498b28:
 {load} cmp    eax,esi
.L498b2a:
 jbe .L498b45
.L498b2c:
 mov    edx,0x1
.L498b31:
 shr    eax,1
.L498b33:
 {load} add    edx,edx
.L498b35:
 {load} cmp    eax,esi
.L498b37:
 ja .L498b31
.L498b39:
 mov    DWORD PTR [edi+0x2e18],edx
.L498b3f:
 mov    DWORD PTR [edi+0x2e54],eax
.L498b45:
 mov    eax,DWORD PTR [edi+0x2e54]
.L498b4b:
 mov    DWORD PTR [ecx+0x78],0x0
.L498b52:
 mov    DWORD PTR [ecx+0x7c],0x0
.L498b59:
 movd   xmm0,eax
.L498b5d:
 cvtdq2pd xmm0,xmm0
.L498b61:
 shr    eax,0x1f
.L498b64:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L498b6d:
 cvtpd2ps xmm1,xmm0
.L498b71:
 movaps xmm0,xmm1
.L498b74:
 subss  xmm0,DWORD PTR [0xa06558]
.L498b7c:
 movss  DWORD PTR [ecx+0x80],xmm0
.L498b84:
 movss  DWORD PTR [ecx+0x84],xmm0
.L498b8c:
 movss  DWORD PTR [ecx+0x88],xmm1
.L498b94:
 movss  DWORD PTR [ecx+0x8c],xmm1
.L498b9c:
 movdqu xmm0,XMMWORD PTR [edi+0x2e24]
.L498ba4:
 movdqu XMMWORD PTR [ecx+0xa0],xmm0
.L498bac:
 movdqu xmm0,XMMWORD PTR [edi+0x2e34]
.L498bb4:
 movdqu XMMWORD PTR [ecx+0xb0],xmm0
.L498bbc:
 movdqu xmm0,XMMWORD PTR [edi+0x2e44]
.L498bc4:
 movdqu XMMWORD PTR [ecx+0xc0],xmm0
.L498bcc:
 movdqu xmm0,XMMWORD PTR [edi+0x2e24]
.L498bd4:
 movdqu XMMWORD PTR [ecx+0xd0],xmm0
.L498bdc:
 movdqu xmm0,XMMWORD PTR [edi+0x2e34]
.L498be4:
 movdqu XMMWORD PTR [ecx+0xe0],xmm0
.L498bec:
 movdqu xmm0,XMMWORD PTR [edi+0x2e44]
.L498bf4:
 mov    DWORD PTR [ecx+0x100],0x42b40000
.L498bfe:
 mov    DWORD PTR [ecx+0x104],0x42b40000
.L498c08:
 movdqu XMMWORD PTR [ecx+0xf0],xmm0
.L498c10:
 mov    DWORD PTR [ecx+0x108],0x3f800000
.L498c1a:
 jmp .L498994
.L498c1f:
 int3
.L498c20:
 cmp    DWORD PTR [0xbfcc34],0x0
.L498c27:
 push   esi
.L498c28:
 {load} mov    esi,ecx
.L498c2a:
 jne .L498c30
.L498c2c:
 {load} xor    al,al
.L498c2e:
 jmp .L498c3f
.L498c30:
 call   DWORD PTR [0x92d0ec]
.L498c36:
 cmp    eax,DWORD PTR [0xbfcc34]
.L498c3c:
 sete   al
.L498c3f:
 push   ebx
.L498c40:
 {load} xor    ebx,ebx
.L498c42:
 test   al,al
.L498c44:
 setne  bl
.L498c47:
 lea    eax,[ebx+0x4]
.L498c4a:
 lea    eax,[eax+eax*2]
.L498c4d:
 lea    ecx,[esi+eax*4]
.L498c50:
 mov    eax,DWORD PTR [ecx]
.L498c52:
 mov    DWORD PTR [ecx+0x4],eax
.L498c55:
 lea    eax,[ebx+0x6]
.L498c58:
 lea    eax,[eax+eax*2]
.L498c5b:
 lea    ecx,[esi+eax*4]
.L498c5e:
 mov    eax,DWORD PTR [ecx]
.L498c60:
 mov    DWORD PTR [ecx+0x4],eax
.L498c63:
 lea    eax,[ebx+0x8]
.L498c66:
 lea    eax,[eax+eax*2]
.L498c69:
 lea    ecx,[esi+eax*4]
.L498c6c:
 call target_49a940
.L498c71:
 cmp    DWORD PTR [0xbfcc34],0x0
.L498c78:
 mov    DWORD PTR [esi+ebx*4+0x90],0x4
.L498c83:
 pop    ebx
.L498c84:
 je .L498ca5
.L498c86:
 call   DWORD PTR [0x92d0ec]
.L498c8c:
 cmp    eax,DWORD PTR [0xbfcc34]
.L498c92:
 sete   al
.L498c95:
 test   al,al
.L498c97:
 je .L498ca5
.L498c99:
 mov    DWORD PTR [esi+0x2cc4],0x0
.L498ca3:
 pop    esi
.L498ca4:
 ret
.L498ca5:
 mov    eax,DWORD PTR [esi+0x2cd8]
.L498cab:
 add    eax,0x3b8
.L498cb0:
 lea    eax,[eax+eax*2]
.L498cb3:
 mov    DWORD PTR [esi+eax*4],0x0
.L498cba:
 pop    esi
.L498cbb:
 ret
.equ target_42bfd0,0x42bfd0
.equ target_4979f0,0x4979f0
.equ target_498cc0,0x498cc0
.equ target_49a940,0x49a940
