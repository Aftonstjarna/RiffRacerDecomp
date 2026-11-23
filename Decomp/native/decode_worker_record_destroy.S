# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x4f8a90,0x4f8da8); instruction-contiguous extent, INT3 padding excluded.
# Decode worker record destruction: releases the worker-owned buffers and runtime objects with the original cleanup order and stack-cookie frame. Called from the decode worker dispatch.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x4f8a90..0x4f8da8
.intel_syntax noprefix
.code32
.text
.global original_decode_worker_record_destroy
original_decode_worker_record_destroy:
.L4f8a90:
 push   ebp
.L4f8a91:
 {load} mov    ebp,esp
.L4f8a93:
 sub    esp,0x318
.L4f8a99:
 mov    eax,[0xbaabc0]
.L4f8a9e:
 {load} xor    eax,ebp
.L4f8aa0:
 mov    DWORD PTR [ebp-0x8],eax
.L4f8aa3:
 mov    eax,DWORD PTR [ebp+0xc]
.L4f8aa6:
 push   ebx
.L4f8aa7:
 push   esi
.L4f8aa8:
 push   edi
.L4f8aa9:
 mov    DWORD PTR [ebp-0x2e8],eax
.L4f8aaf:
 sub    esp,0x10
.L4f8ab2:
 mov    eax,DWORD PTR [ebp+0x10]
.L4f8ab5:
 mov    DWORD PTR [ebp-0x2e4],eax
.L4f8abb:
 {load} mov    eax,esp
.L4f8abd:
 mov    DWORD PTR [ebp-0x30c],0x4f8ff0
.L4f8ac7:
 sub    esp,0x8
.L4f8aca:
 mov    DWORD PTR [ebp-0x308],0x4f9030
.L4f8ad4:
 mov    DWORD PTR [ebp-0x304],0x0
.L4f8ade:
 mov    DWORD PTR [ebp-0x300],0x4f9070
.L4f8ae8:
 movdqu xmm0,XMMWORD PTR [ebp-0x30c]
.L4f8af0:
 mov    DWORD PTR [ebp-0x318],ecx
.L4f8af6:
 lea    ecx,[ebp-0x318]
.L4f8afc:
 mov    DWORD PTR [ebp-0x314],edx
.L4f8b02:
 lea    edx,[ebp-0x2dc]
.L4f8b08:
 mov    DWORD PTR [ebp-0x310],0x0
.L4f8b12:
 movdqu XMMWORD PTR [eax],xmm0
.L4f8b16:
 call target_564210
.L4f8b1b:
 add    esp,0x18
.L4f8b1e:
 test   eax,eax
.L4f8b20:
 jns .L4f8b35
.L4f8b22:
 {load} xor    al,al
.L4f8b24:
 pop    edi
.L4f8b25:
 pop    esi
.L4f8b26:
 pop    ebx
.L4f8b27:
 mov    ecx,DWORD PTR [ebp-0x8]
.L4f8b2a:
 {load} xor    ecx,ebp
.L4f8b2c:
 call target_8f8958
.L4f8b31:
 {load} mov    esp,ebp
.L4f8b33:
 pop    ebp
.L4f8b34:
 ret
.L4f8b35:
 cmp    DWORD PTR [ebp-0x2d8],0x0
.L4f8b3c:
 je .L4f8b58
.L4f8b3e:
 cmp    DWORD PTR [ebp-0x284],0x3
.L4f8b45:
 jl .L4f8b58
.L4f8b47:
 mov    ebx,DWORD PTR [ebp-0x27c]
.L4f8b4d:
 shl    ebx,0x5
.L4f8b50:
 add    ebx,DWORD PTR [ebp-0x294]
.L4f8b56:
 jmp .L4f8b5e
.L4f8b58:
 mov    ebx,DWORD PTR [ebp-0x294]
.L4f8b5e:
 or     edx,0xffffffff
.L4f8b61:
 lea    ecx,[ebp-0x2dc]
.L4f8b67:
 call target_564290
.L4f8b6c:
 mov    ecx,DWORD PTR [ebp+0x8]
.L4f8b6f:
 {load} mov    edi,eax
.L4f8b71:
 {load} mov    esi,edx
.L4f8b73:
 movd   xmm0,ecx
.L4f8b77:
 cvtdq2pd xmm0,xmm0
.L4f8b7b:
 shr    ecx,0x1f
.L4f8b7e:
 addsd  xmm0,QWORD PTR [ecx*8+0xa071b0]
.L4f8b87:
 cvtpd2ps xmm1,xmm0
.L4f8b8b:
 movd   xmm0,DWORD PTR [ebx+0x8]
.L4f8b90:
 cvtdq2ps xmm0,xmm0
.L4f8b93:
 divss  xmm1,xmm0
.L4f8b97:
 cvtps2pd xmm0,xmm1
.L4f8b9a:
 movapd xmm2,xmm0
.L4f8b9e:
 movsd  QWORD PTR [ebp-0x304],xmm0
.L4f8ba6:
 movaps xmm1,xmm0
.L4f8ba9:
 call target_5623e0
.L4f8bae:
 {load} mov    edx,esi
.L4f8bb0:
 mov    DWORD PTR [ebp-0x2f4],eax
.L4f8bb6:
 {load} mov    ecx,edi
.L4f8bb8:
 call target_8f92ef
.L4f8bbd:
 mulsd  xmm0,QWORD PTR [ebp-0x304]
.L4f8bc5:
 call target_8f9131
.L4f8bca:
 mov    ecx,DWORD PTR [ebp-0x2e4]
.L4f8bd0:
 mov    edx,0x4
.L4f8bd5:
 mov    DWORD PTR [ecx],eax
.L4f8bd7:
 {load} xor    ecx,ecx
.L4f8bd9:
 mul    edx
.L4f8bdb:
 seto   cl
.L4f8bde:
 neg    ecx
.L4f8be0:
 {load} or     ecx,eax
.L4f8be2:
 push   ecx
.L4f8be3:
 call target_8f87c8
.L4f8be8:
 mov    ecx,DWORD PTR [ebp-0x2e8]
.L4f8bee:
 add    esp,0x4
.L4f8bf1:
 push   0x40000
.L4f8bf6:
 mov    DWORD PTR [ecx],eax
.L4f8bf8:
 call target_8f87c8
.L4f8bfd:
 add    esp,0x4
.L4f8c00:
 mov    DWORD PTR [ebp-0x2ec],eax
.L4f8c06:
 {load} xor    ebx,ebx
.L4f8c08:
 lea    ecx,[ebp-0x2dc]
.L4f8c0e:
 {load} mov    edx,eax
.L4f8c10:
 mov    DWORD PTR [ebp-0x2e0],ebx
.L4f8c16:
 {load} xor    esi,esi
.L4f8c18:
 {load} mov    edi,eax
.L4f8c1a:
 push   0x8000
.L4f8c1f:
 call target_565430
.L4f8c24:
 {load} mov    edx,eax
.L4f8c26:
 add    esp,0x4
.L4f8c29:
 mov    DWORD PTR [ebp-0x2f0],edx
.L4f8c2f:
 test   edx,edx
.L4f8c31:
 jle .L4f8cf8
.L4f8c37:
 mov    eax,DWORD PTR [ebp-0x2e4]
.L4f8c3d:
 sub    esp,0x8
.L4f8c40:
 movsd  xmm0,QWORD PTR [ebp-0x304]
.L4f8c48:
 mov    ecx,DWORD PTR [eax]
.L4f8c4a:
 sub    ecx,DWORD PTR [ebp-0x2e0]
.L4f8c50:
 mov    eax,DWORD PTR [ebp-0x2e8]
.L4f8c56:
 movsd  QWORD PTR [esp],xmm0
.L4f8c5b:
 push   ecx
.L4f8c5c:
 mov    ecx,DWORD PTR [ebp-0x2e0]
.L4f8c62:
 mov    eax,DWORD PTR [eax]
.L4f8c64:
 lea    eax,[eax+ecx*4]
.L4f8c67:
 mov    ecx,DWORD PTR [ebp-0x2f4]
.L4f8c6d:
 push   eax
.L4f8c6e:
 lea    eax,[ebp-0x2f8]
.L4f8c74:
 push   eax
.L4f8c75:
 lea    eax,[edx+esi*1]
.L4f8c78:
 {load} mov    edx,edi
.L4f8c7a:
 push   0x0
.L4f8c7c:
 push   eax
.L4f8c7d:
 call target_562630
.L4f8c82:
 add    DWORD PTR [ebp-0x2e0],eax
.L4f8c88:
 add    esp,0x1c
.L4f8c8b:
 mov    ecx,DWORD PTR [ebp-0x2f8]
.L4f8c91:
 mov    esi,DWORD PTR [ebp-0x2f0]
.L4f8c97:
 {load} cmp    ecx,esi
.L4f8c99:
 jge .L4f8cc2
.L4f8c9b:
 {load} sub    esi,ecx
.L4f8c9d:
 xor    ebx,0x1
.L4f8ca0:
 lea    eax,[esi*4+0x0]
.L4f8ca7:
 push   eax
.L4f8ca8:
 lea    eax,[edi+ecx*4]
.L4f8cab:
 push   eax
.L4f8cac:
 {load} mov    eax,ebx
.L4f8cae:
 shl    eax,0x11
.L4f8cb1:
 add    eax,DWORD PTR [ebp-0x2ec]
.L4f8cb7:
 push   eax
.L4f8cb8:
 call target_8f8d66
.L4f8cbd:
 add    esp,0xc
.L4f8cc0:
 jmp .L4f8cc4
.L4f8cc2:
 {load} xor    esi,esi
.L4f8cc4:
 {load} mov    edi,ebx
.L4f8cc6:
 lea    ecx,[ebp-0x2dc]
.L4f8ccc:
 shl    edi,0x11
.L4f8ccf:
 mov    eax,0x8000
.L4f8cd4:
 add    edi,DWORD PTR [ebp-0x2ec]
.L4f8cda:
 {load} sub    eax,esi
.L4f8cdc:
 push   eax
.L4f8cdd:
 lea    edx,[edi+esi*4]
.L4f8ce0:
 call target_565430
.L4f8ce5:
 {load} mov    edx,eax
.L4f8ce7:
 mov    DWORD PTR [ebp-0x2f0],eax
.L4f8ced:
 add    esp,0x4
.L4f8cf0:
 test   edx,edx
.L4f8cf2:
 jg .L4f8c37
.L4f8cf8:
 mov    eax,DWORD PTR [ebp-0x2e4]
.L4f8cfe:
 sub    esp,0x8
.L4f8d01:
 mov    edi,DWORD PTR [ebp-0x2e0]
.L4f8d07:
 movsd  xmm0,QWORD PTR [ebp-0x304]
.L4f8d0f:
 shl    ebx,0x11
.L4f8d12:
 mov    eax,DWORD PTR [eax]
.L4f8d14:
 {load} sub    eax,edi
.L4f8d16:
 movsd  QWORD PTR [esp],xmm0
.L4f8d1b:
 push   eax
.L4f8d1c:
 mov    eax,DWORD PTR [ebp-0x2e8]
.L4f8d22:
 mov    eax,DWORD PTR [eax]
.L4f8d24:
 lea    eax,[eax+edi*4]
.L4f8d27:
 push   eax
.L4f8d28:
 lea    eax,[ebp-0x2f8]
.L4f8d2e:
 push   eax
.L4f8d2f:
 push   0x1
.L4f8d31:
 push   esi
.L4f8d32:
 mov    esi,DWORD PTR [ebp-0x2ec]
.L4f8d38:
 lea    edx,[esi+ebx*1]
.L4f8d3b:
 mov    ebx,DWORD PTR [ebp-0x2f4]
.L4f8d41:
 {load} mov    ecx,ebx
.L4f8d43:
 call target_562630
.L4f8d48:
 mov    ecx,DWORD PTR [ebp-0x2e4]
.L4f8d4e:
 add    esp,0x1c
.L4f8d51:
 {load} add    eax,edi
.L4f8d53:
 push   esi
.L4f8d54:
 mov    DWORD PTR [ecx],eax
.L4f8d56:
 call   DWORD PTR [0x92d4a0]
.L4f8d5c:
 mov    esi,DWORD PTR [0x92d3a4]
.L4f8d62:
 add    esp,0x4
.L4f8d65:
 push   DWORD PTR [ebx+0x2c]
.L4f8d68:
 call   esi
.L4f8d6a:
 add    esp,0x4
.L4f8d6d:
 push   DWORD PTR [ebx+0x40]
.L4f8d70:
 call   esi
.L4f8d72:
 add    esp,0x4
.L4f8d75:
 push   DWORD PTR [ebx]
.L4f8d77:
 call   esi
.L4f8d79:
 add    esp,0x4
.L4f8d7c:
 push   DWORD PTR [ebx+0x4]
.L4f8d7f:
 call   esi
.L4f8d81:
 add    esp,0x4
.L4f8d84:
 push   ebx
.L4f8d85:
 call   esi
.L4f8d87:
 add    esp,0x4
.L4f8d8a:
 lea    ecx,[ebp-0x2dc]
.L4f8d90:
 call target_5640c0
.L4f8d95:
 mov    ecx,DWORD PTR [ebp-0x8]
.L4f8d98:
 mov    al,0x1
.L4f8d9a:
 pop    edi
.L4f8d9b:
 pop    esi
.L4f8d9c:
 {load} xor    ecx,ebp
.L4f8d9e:
 pop    ebx
.L4f8d9f:
 call target_8f8958
.L4f8da4:
 {load} mov    esp,ebp
.L4f8da6:
 pop    ebp
.L4f8da7:
 ret
.equ target_5623e0,0x5623e0
.equ target_562630,0x562630
.equ target_5640c0,0x5640c0
.equ target_564210,0x564210
.equ target_564290,0x564290
.equ target_565430,0x565430
.equ target_8f87c8,0x8f87c8
.equ target_8f8958,0x8f8958
.equ target_8f8d66,0x8f8d66
.equ target_8f9131,0x8f9131
.equ target_8f92ef,0x8f92ef
