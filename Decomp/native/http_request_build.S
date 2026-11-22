# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5c1790,0x5c1d66); instruction-contiguous extent, INT3 padding excluded.
# HTTP request construction: the body references the literal GET/POST, Host, User-Agent,
# Content-Length and OctaneHTTP/5.1 strings; original vtable and helper calls retained.
# Identification rests on those literals and the worker resource-state caller; the full
# network path is not traced here. Reference-assembly evidence only, no source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x5c1790..0x5c1d66
.intel_syntax noprefix
.code32
.text
.global original_http_request_build
original_http_request_build:
.L5c1790:
 push   ebp
.L5c1791:
 {load} mov    ebp,esp
.L5c1793:
 push   0xffffffff
.L5c1795:
 push   0x9091ba
.L5c179a:
 mov    eax,fs:0x0
.L5c17a0:
 push   eax
.L5c17a1:
 sub    esp,0x1c4
.L5c17a7:
 mov    eax,[0xbaabc0]
.L5c17ac:
 {load} xor    eax,ebp
.L5c17ae:
 mov    DWORD PTR [ebp-0x10],eax
.L5c17b1:
 push   ebx
.L5c17b2:
 push   esi
.L5c17b3:
 push   edi
.L5c17b4:
 push   eax
.L5c17b5:
 lea    eax,[ebp-0xc]
.L5c17b8:
 mov    fs:0x0,eax
.L5c17be:
 {load} mov    edi,ecx
.L5c17c0:
 mov    eax,DWORD PTR [edi+0x68]
.L5c17c3:
 test   eax,eax
.L5c17c5:
 jne .L5c1a6c
.L5c17cb:
 {load} xor    ecx,ecx
.L5c17cd:
 mov    DWORD PTR [ebp-0x118],eax
.L5c17d3:
 cmp    BYTE PTR [0xa06028],cl
.L5c17d9:
 mov    BYTE PTR [ebp-0x128],al
.L5c17df:
 mov    eax,0xe
.L5c17e4:
 cmove  eax,ecx
.L5c17e7:
 mov    DWORD PTR [ebp-0x114],0xf
.L5c17f1:
 push   eax
.L5c17f2:
 push   0xa06028
.L5c17f7:
 lea    ecx,[ebp-0x128]
.L5c17fd:
 call target_416520
.L5c1802:
 lea    eax,[edi+0x6c]
.L5c1805:
 mov    DWORD PTR [ebp-0x4],0x0
.L5c180c:
 push   eax
.L5c180d:
 lea    eax,[ebp-0x188]
.L5c1813:
 push   0xa06074
.L5c1818:
 push   eax
.L5c1819:
 call target_4b2e60
.L5c181e:
 push   0xa06060
.L5c1823:
 push   eax
.L5c1824:
 lea    eax,[ebp-0x170]
.L5c182a:
 mov    BYTE PTR [ebp-0x4],0x1
.L5c182e:
 push   eax
.L5c182f:
 call target_4b2f50
.L5c1834:
 lea    ecx,[edi+0x84]
.L5c183a:
 mov    BYTE PTR [ebp-0x4],0x2
.L5c183e:
 push   ecx
.L5c183f:
 push   eax
.L5c1840:
 lea    eax,[ebp-0x158]
.L5c1846:
 push   eax
.L5c1847:
 call target_5c21d0
.L5c184c:
 push   0xa0603c
.L5c1851:
 push   eax
.L5c1852:
 lea    eax,[ebp-0x140]
.L5c1858:
 mov    BYTE PTR [ebp-0x4],0x3
.L5c185c:
 push   eax
.L5c185d:
 call target_4b2f50
.L5c1862:
 lea    ecx,[ebp-0x128]
.L5c1868:
 mov    BYTE PTR [ebp-0x4],0x4
.L5c186c:
 push   ecx
.L5c186d:
 {load} mov    edx,eax
.L5c186f:
 lea    ecx,[ebp-0x1a0]
.L5c1875:
 call target_576e80
.L5c187a:
 push   0xa06038
.L5c187f:
 push   eax
.L5c1880:
 lea    eax,[ebp-0x1b8]
.L5c1886:
 mov    BYTE PTR [ebp-0x4],0x5
.L5c188a:
 push   eax
.L5c188b:
 call target_4b2f50
.L5c1890:
 add    esp,0x40
.L5c1893:
 cmp    DWORD PTR [ebp-0x18c],0x10
.L5c189a:
 mov    esi,DWORD PTR [0x92d4b0]
.L5c18a0:
 jb .L5c18ad
.L5c18a2:
 push   DWORD PTR [ebp-0x1a0]
.L5c18a8:
 call   esi
.L5c18aa:
 add    esp,0x4
.L5c18ad:
 mov    DWORD PTR [ebp-0x18c],0xf
.L5c18b7:
 mov    DWORD PTR [ebp-0x190],0x0
.L5c18c1:
 mov    BYTE PTR [ebp-0x1a0],0x0
.L5c18c8:
 cmp    DWORD PTR [ebp-0x12c],0x10
.L5c18cf:
 jb .L5c18dc
.L5c18d1:
 push   DWORD PTR [ebp-0x140]
.L5c18d7:
 call   esi
.L5c18d9:
 add    esp,0x4
.L5c18dc:
 mov    DWORD PTR [ebp-0x12c],0xf
.L5c18e6:
 mov    DWORD PTR [ebp-0x130],0x0
.L5c18f0:
 mov    BYTE PTR [ebp-0x140],0x0
.L5c18f7:
 cmp    DWORD PTR [ebp-0x144],0x10
.L5c18fe:
 jb .L5c190b
.L5c1900:
 push   DWORD PTR [ebp-0x158]
.L5c1906:
 call   esi
.L5c1908:
 add    esp,0x4
.L5c190b:
 mov    DWORD PTR [ebp-0x144],0xf
.L5c1915:
 mov    DWORD PTR [ebp-0x148],0x0
.L5c191f:
 mov    BYTE PTR [ebp-0x158],0x0
.L5c1926:
 cmp    DWORD PTR [ebp-0x15c],0x10
.L5c192d:
 jb .L5c193a
.L5c192f:
 push   DWORD PTR [ebp-0x170]
.L5c1935:
 call   esi
.L5c1937:
 add    esp,0x4
.L5c193a:
 mov    DWORD PTR [ebp-0x15c],0xf
.L5c1944:
 mov    DWORD PTR [ebp-0x160],0x0
.L5c194e:
 mov    BYTE PTR [ebp-0x170],0x0
.L5c1955:
 cmp    DWORD PTR [ebp-0x174],0x10
.L5c195c:
 jb .L5c1969
.L5c195e:
 push   DWORD PTR [ebp-0x188]
.L5c1964:
 call   esi
.L5c1966:
 add    esp,0x4
.L5c1969:
 mov    DWORD PTR [ebp-0x174],0xf
.L5c1973:
 mov    DWORD PTR [ebp-0x178],0x0
.L5c197d:
 mov    BYTE PTR [ebp-0x188],0x0
.L5c1984:
 mov    BYTE PTR [ebp-0x4],0xc
.L5c1988:
 cmp    DWORD PTR [ebp-0x114],0x10
.L5c198f:
 jb .L5c199c
.L5c1991:
 push   DWORD PTR [ebp-0x128]
.L5c1997:
 call   esi
.L5c1999:
 add    esp,0x4
.L5c199c:
 push   0xffffffff
.L5c199e:
 push   0x0
.L5c19a0:
 lea    eax,[edi+0x9c]
.L5c19a6:
 mov    DWORD PTR [ebp-0x114],0xf
.L5c19b0:
 push   eax
.L5c19b1:
 lea    ecx,[ebp-0x1b8]
.L5c19b7:
 mov    DWORD PTR [ebp-0x118],0x0
.L5c19c1:
 mov    BYTE PTR [ebp-0x128],0x0
.L5c19c8:
 call target_4420b0
.L5c19cd:
 push   0x2
.L5c19cf:
 push   0xa06038
.L5c19d4:
 lea    ecx,[ebp-0x1b8]
.L5c19da:
 call target_442170
.L5c19df:
 cmp    DWORD PTR [ebp-0x1a4],0x10
.L5c19e6:
 lea    edx,[ebp-0x1b8]
.L5c19ec:
 mov    eax,DWORD PTR [edi+0x8]
.L5c19ef:
 lea    ecx,[edi+0x8]
.L5c19f2:
 push   DWORD PTR [ebp-0x1a8]
.L5c19f8:
 cmovae edx,DWORD PTR [ebp-0x1b8]
.L5c19ff:
 push   edx
.L5c1a00:
 mov    eax,DWORD PTR [eax+0x30]
.L5c1a03:
 call   eax
.L5c1a05:
 test   al,al
.L5c1a07:
 jne .L5c1a4f
.L5c1a09:
 mov    eax,DWORD PTR [edi+0x8]
.L5c1a0c:
 lea    ecx,[edi+0x8]
.L5c1a0f:
 call   DWORD PTR [eax+0x38]
.L5c1a12:
 cmp    DWORD PTR [ebp-0x1a4],0x10
.L5c1a19:
 mov    ecx,DWORD PTR [edi+0xc0]
.L5c1a1f:
 mov    DWORD PTR [edi+0xc4],ecx
.L5c1a25:
 mov    BYTE PTR [edi+0xd0],0x1
.L5c1a2c:
 mov    DWORD PTR [edi+0xd4],eax
.L5c1a32:
 mov    DWORD PTR [edi+0x64],0x0
.L5c1a39:
 jb .L5c1d4a
.L5c1a3f:
 push   DWORD PTR [ebp-0x1b8]
.L5c1a45:
 call   esi
.L5c1a47:
 add    esp,0x4
.L5c1a4a:
 jmp .L5c1d4a
.L5c1a4f:
 cmp    DWORD PTR [ebp-0x1a4],0x10
.L5c1a56:
 jb .L5c1d43
.L5c1a5c:
 push   DWORD PTR [ebp-0x1b8]
.L5c1a62:
 call   esi
.L5c1a64:
 add    esp,0x4
.L5c1a67:
 jmp .L5c1d43
.L5c1a6c:
 cmp    eax,0x1
.L5c1a6f:
 jne .L5c1d43
.L5c1a75:
 push   0xa06028
.L5c1a7a:
 lea    ecx,[ebp-0x128]
.L5c1a80:
 call target_415b00
.L5c1a85:
 {load} mov    esi,eax
.L5c1a87:
 lea    ecx,[edi+0x6c]
.L5c1a8a:
 mov    DWORD PTR [ebp-0x4],0xd
.L5c1a91:
 push   ecx
.L5c1a92:
 lea    eax,[ebp-0x1a0]
.L5c1a98:
 push   0xa0607c
.L5c1a9d:
 push   eax
.L5c1a9e:
 call target_4b2e60
.L5c1aa3:
 push   0xa06060
.L5c1aa8:
 push   eax
.L5c1aa9:
 lea    eax,[ebp-0x140]
.L5c1aaf:
 mov    BYTE PTR [ebp-0x4],0xe
.L5c1ab3:
 push   eax
.L5c1ab4:
 call target_4b2f50
.L5c1ab9:
 lea    ecx,[edi+0x84]
.L5c1abf:
 mov    BYTE PTR [ebp-0x4],0xf
.L5c1ac3:
 push   ecx
.L5c1ac4:
 push   eax
.L5c1ac5:
 lea    eax,[ebp-0x158]
.L5c1acb:
 push   eax
.L5c1acc:
 call target_5c21d0
.L5c1ad1:
 push   0xa0603c
.L5c1ad6:
 push   eax
.L5c1ad7:
 lea    eax,[ebp-0x170]
.L5c1add:
 mov    BYTE PTR [ebp-0x4],0x10
.L5c1ae1:
 push   eax
.L5c1ae2:
 call target_4b2f50
.L5c1ae7:
 push   esi
.L5c1ae8:
 {load} mov    edx,eax
.L5c1aea:
 mov    BYTE PTR [ebp-0x4],0x11
.L5c1aee:
 lea    ecx,[ebp-0x188]
.L5c1af4:
 call target_576e80
.L5c1af9:
 push   0xa06038
.L5c1afe:
 push   eax
.L5c1aff:
 lea    eax,[ebp-0x1d0]
.L5c1b05:
 mov    BYTE PTR [ebp-0x4],0x12
.L5c1b09:
 push   eax
.L5c1b0a:
 call target_4b2f50
.L5c1b0f:
 add    esp,0x40
.L5c1b12:
 cmp    DWORD PTR [ebp-0x174],0x10
.L5c1b19:
 mov    esi,DWORD PTR [0x92d4b0]
.L5c1b1f:
 jb .L5c1b2c
.L5c1b21:
 push   DWORD PTR [ebp-0x188]
.L5c1b27:
 call   esi
.L5c1b29:
 add    esp,0x4
.L5c1b2c:
 mov    DWORD PTR [ebp-0x174],0xf
.L5c1b36:
 mov    DWORD PTR [ebp-0x178],0x0
.L5c1b40:
 mov    BYTE PTR [ebp-0x188],0x0
.L5c1b47:
 cmp    DWORD PTR [ebp-0x15c],0x10
.L5c1b4e:
 jb .L5c1b5b
.L5c1b50:
 push   DWORD PTR [ebp-0x170]
.L5c1b56:
 call   esi
.L5c1b58:
 add    esp,0x4
.L5c1b5b:
 mov    DWORD PTR [ebp-0x15c],0xf
.L5c1b65:
 mov    DWORD PTR [ebp-0x160],0x0
.L5c1b6f:
 mov    BYTE PTR [ebp-0x170],0x0
.L5c1b76:
 cmp    DWORD PTR [ebp-0x144],0x10
.L5c1b7d:
 jb .L5c1b8a
.L5c1b7f:
 push   DWORD PTR [ebp-0x158]
.L5c1b85:
 call   esi
.L5c1b87:
 add    esp,0x4
.L5c1b8a:
 mov    DWORD PTR [ebp-0x144],0xf
.L5c1b94:
 mov    DWORD PTR [ebp-0x148],0x0
.L5c1b9e:
 mov    BYTE PTR [ebp-0x158],0x0
.L5c1ba5:
 cmp    DWORD PTR [ebp-0x12c],0x10
.L5c1bac:
 jb .L5c1bb9
.L5c1bae:
 push   DWORD PTR [ebp-0x140]
.L5c1bb4:
 call   esi
.L5c1bb6:
 add    esp,0x4
.L5c1bb9:
 mov    DWORD PTR [ebp-0x12c],0xf
.L5c1bc3:
 mov    DWORD PTR [ebp-0x130],0x0
.L5c1bcd:
 mov    BYTE PTR [ebp-0x140],0x0
.L5c1bd4:
 cmp    DWORD PTR [ebp-0x18c],0x10
.L5c1bdb:
 jb .L5c1be8
.L5c1bdd:
 push   DWORD PTR [ebp-0x1a0]
.L5c1be3:
 call   esi
.L5c1be5:
 add    esp,0x4
.L5c1be8:
 mov    DWORD PTR [ebp-0x18c],0xf
.L5c1bf2:
 mov    DWORD PTR [ebp-0x190],0x0
.L5c1bfc:
 mov    BYTE PTR [ebp-0x1a0],0x0
.L5c1c03:
 mov    BYTE PTR [ebp-0x4],0x19
.L5c1c07:
 cmp    DWORD PTR [ebp-0x114],0x10
.L5c1c0e:
 jb .L5c1c1b
.L5c1c10:
 push   DWORD PTR [ebp-0x128]
.L5c1c16:
 call   esi
.L5c1c18:
 add    esp,0x4
.L5c1c1b:
 push   DWORD PTR [edi+0xb8]
.L5c1c21:
 lea    eax,[ebp-0x110]
.L5c1c27:
 mov    DWORD PTR [ebp-0x114],0xf
.L5c1c31:
 push   0xa06084
.L5c1c36:
 push   0x100
.L5c1c3b:
 push   eax
.L5c1c3c:
 mov    DWORD PTR [ebp-0x118],0x0
.L5c1c46:
 mov    BYTE PTR [ebp-0x128],0x0
.L5c1c4d:
 call target_452ca0
.L5c1c52:
 add    esp,0x10
.L5c1c55:
 cmp    BYTE PTR [ebp-0x110],0x0
.L5c1c5c:
 jne .L5c1c62
.L5c1c5e:
 {load} xor    ecx,ecx
.L5c1c60:
 jmp .L5c1c79
.L5c1c62:
 lea    ecx,[ebp-0x110]
.L5c1c68:
 lea    edx,[ecx+0x1]
.L5c1c6b:
 jmp .L5c1c70
.L5c1c6d:
 {disp8} lea    ecx,[ecx+0x0]
.L5c1c70:
 mov    al,BYTE PTR [ecx]
.L5c1c72:
 inc    ecx
.L5c1c73:
 test   al,al
.L5c1c75:
 jne .L5c1c70
.L5c1c77:
 {load} sub    ecx,edx
.L5c1c79:
 push   ecx
.L5c1c7a:
 lea    eax,[ebp-0x110]
.L5c1c80:
 push   eax
.L5c1c81:
 lea    ecx,[ebp-0x1d0]
.L5c1c87:
 call target_442170
.L5c1c8c:
 push   0xffffffff
.L5c1c8e:
 push   0x0
.L5c1c90:
 lea    eax,[edi+0x9c]
.L5c1c96:
 push   eax
.L5c1c97:
 lea    ecx,[ebp-0x1d0]
.L5c1c9d:
 call target_4420b0
.L5c1ca2:
 push   0x2
.L5c1ca4:
 push   0xa06038
.L5c1ca9:
 lea    ecx,[ebp-0x1d0]
.L5c1caf:
 call target_442170
.L5c1cb4:
 cmp    DWORD PTR [ebp-0x1bc],0x10
.L5c1cbb:
 lea    edx,[ebp-0x1d0]
.L5c1cc1:
 mov    eax,DWORD PTR [edi+0x8]
.L5c1cc4:
 lea    ecx,[edi+0x8]
.L5c1cc7:
 push   DWORD PTR [ebp-0x1c0]
.L5c1ccd:
 cmovae edx,DWORD PTR [ebp-0x1d0]
.L5c1cd4:
 push   edx
.L5c1cd5:
 mov    eax,DWORD PTR [eax+0x30]
.L5c1cd8:
 call   eax
.L5c1cda:
 test   al,al
.L5c1cdc:
 lea    ecx,[edi+0x8]
.L5c1cdf:
 mov    eax,DWORD PTR [edi+0x8]
.L5c1ce2:
 je .L5c1cff
.L5c1ce4:
 push   DWORD PTR [edi+0xb8]
.L5c1cea:
 mov    eax,DWORD PTR [eax+0x30]
.L5c1ced:
 push   DWORD PTR [edi+0xb4]
.L5c1cf3:
 call   eax
.L5c1cf5:
 test   al,al
.L5c1cf7:
 jne .L5c1d38
.L5c1cf9:
 mov    eax,DWORD PTR [edi+0x8]
.L5c1cfc:
 lea    ecx,[edi+0x8]
.L5c1cff:
 call   DWORD PTR [eax+0x38]
.L5c1d02:
 cmp    DWORD PTR [ebp-0x1bc],0x10
.L5c1d09:
 mov    ecx,DWORD PTR [edi+0xc0]
.L5c1d0f:
 mov    DWORD PTR [edi+0xc4],ecx
.L5c1d15:
 mov    DWORD PTR [edi+0x64],0x0
.L5c1d1c:
 mov    DWORD PTR [edi+0xd4],eax
.L5c1d22:
 mov    BYTE PTR [edi+0xd0],0x1
.L5c1d29:
 jb .L5c1d4a
.L5c1d2b:
 push   DWORD PTR [ebp-0x1d0]
.L5c1d31:
 call   esi
.L5c1d33:
 add    esp,0x4
.L5c1d36:
 jmp .L5c1d4a
.L5c1d38:
 lea    ecx,[ebp-0x1d0]
.L5c1d3e:
 call target_415b60
.L5c1d43:
 mov    DWORD PTR [edi+0x64],0x2
.L5c1d4a:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5c1d4d:
 mov    DWORD PTR fs:0x0,ecx
.L5c1d54:
 pop    ecx
.L5c1d55:
 pop    edi
.L5c1d56:
 pop    esi
.L5c1d57:
 pop    ebx
.L5c1d58:
 mov    ecx,DWORD PTR [ebp-0x10]
.L5c1d5b:
 {load} xor    ecx,ebp
.L5c1d5d:
 call target_8f8958
.L5c1d62:
 {load} mov    esp,ebp
.L5c1d64:
 pop    ebp
.L5c1d65:
 ret
.equ target_415b00,0x415b00
.equ target_415b60,0x415b60
.equ target_416520,0x416520
.equ target_4420b0,0x4420b0
.equ target_442170,0x442170
.equ target_452ca0,0x452ca0
.equ target_4b2e60,0x4b2e60
.equ target_4b2f50,0x4b2f50
.equ target_576e80,0x576e80
.equ target_5c21d0,0x5c21d0
.equ target_8f8958,0x8f8958
