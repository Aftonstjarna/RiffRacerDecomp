# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x561c80,0x561d33); instruction-contiguous extent, INT3 padding excluded.
# Wide-entry (28-byte record) vector reallocation: allocates count*28 through operator new
# (IAT 0x92D4B4), transfers elements through 0x5620E0/0x562260 and releases the old storage.
# Zero count clears the vector without allocation; overflow and failure paths preserved.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x561c80..0x561d33
.intel_syntax noprefix
.code32
.text
.global original_wide_entry_vector_reallocate
original_wide_entry_vector_reallocate:
.L561c80:
 push   ebp
.L561c81:
 {load} mov    ebp,esp
.L561c83:
 push   ebx
.L561c84:
 push   esi
.L561c85:
 mov    esi,DWORD PTR [ebp+0x8]
.L561c88:
 {load} mov    ebx,ecx
.L561c8a:
 push   edi
.L561c8b:
 {load} xor    edi,edi
.L561c8d:
 test   esi,esi
.L561c8f:
 je .L561cbb
.L561c91:
 cmp    esi,0x9249249
.L561c97:
 ja .L561cb5
.L561c99:
 lea    eax,[esi*8+0x0]
.L561ca0:
 {load} sub    eax,esi
.L561ca2:
 shl    eax,0x2
.L561ca5:
 push   eax
.L561ca6:
 call   DWORD PTR [0x92d4b4]
.L561cac:
 {load} mov    edi,eax
.L561cae:
 add    esp,0x4
.L561cb1:
 test   edi,edi
.L561cb3:
 jne .L561cbb
.L561cb5:
 call   DWORD PTR [0x92d164]
.L561cbb:
 push   DWORD PTR [ebp+0x8]
.L561cbe:
 mov    edx,DWORD PTR [ebx+0x4]
.L561cc1:
 mov    ecx,DWORD PTR [ebx]
.L561cc3:
 sub    esp,0x8
.L561cc6:
 push   edi
.L561cc7:
 call target_562260
.L561ccc:
 mov    ecx,DWORD PTR [ebx+0x4]
.L561ccf:
 mov    eax,0x92492493
.L561cd4:
 sub    ecx,DWORD PTR [ebx]
.L561cd6:
 add    esp,0x10
.L561cd9:
 imul   ecx
.L561cdb:
 mov    eax,DWORD PTR [ebx]
.L561cdd:
 {load} add    edx,ecx
.L561cdf:
 sar    edx,0x4
.L561ce2:
 {load} mov    ecx,edx
.L561ce4:
 shr    ecx,0x1f
.L561ce7:
 {load} add    ecx,edx
.L561ce9:
 mov    DWORD PTR [ebp+0x8],ecx
.L561cec:
 test   eax,eax
.L561cee:
 je .L561d0c
.L561cf0:
 push   DWORD PTR [ebp+0x8]
.L561cf3:
 mov    edx,DWORD PTR [ebx+0x4]
.L561cf6:
 push   ecx
.L561cf7:
 {load} mov    ecx,eax
.L561cf9:
 call target_5620e0
.L561cfe:
 push   DWORD PTR [ebx]
.L561d00:
 call   DWORD PTR [0x92d4b0]
.L561d06:
 mov    ecx,DWORD PTR [ebp+0x8]
.L561d09:
 add    esp,0xc
.L561d0c:
 lea    eax,[esi*8+0x0]
.L561d13:
 mov    DWORD PTR [ebx],edi
.L561d15:
 {load} sub    eax,esi
.L561d17:
 lea    eax,[edi+eax*4]
.L561d1a:
 mov    DWORD PTR [ebx+0x8],eax
.L561d1d:
 lea    eax,[ecx*8+0x0]
.L561d24:
 {load} sub    eax,ecx
.L561d26:
 lea    eax,[edi+eax*4]
.L561d29:
 pop    edi
.L561d2a:
 pop    esi
.L561d2b:
 mov    DWORD PTR [ebx+0x4],eax
.L561d2e:
 pop    ebx
.L561d2f:
 pop    ebp
.L561d30:
 ret    0x4
.equ target_5620e0,0x5620e0
.equ target_562260,0x562260
