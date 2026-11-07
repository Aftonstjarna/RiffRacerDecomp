# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b2840,0x4b28d0); complete function, no padding.
.intel_syntax noprefix
.code32
.text
.global original_record24_reallocate
.equ RECORD24_RANGE_COPY,0x4b3e40
original_record24_reallocate:
 push   ebp
 mov.s    ebp,esp
 push   ebx
 push   esi
 mov    esi,DWORD PTR [ebp+0x8]
 mov.s    ebx,ecx
 push   edi
 xor.s    edi,edi
 test   esi,esi
 je     .L4b2875
 cmp    esi,0xaaaaaaa
 ja     .L4b286f
 lea    eax,[esi+esi*2]
 shl    eax,0x3
 push   eax
 call   DWORD PTR 0x92d4b4
 mov.s    edi,eax
 add    esp,0x4
 test   edi,edi
 jne    .L4b2875
.L4b286f:
 call   DWORD PTR 0x92d164
.L4b2875:
 push   DWORD PTR [ebp+0x8]
 mov    edx,DWORD PTR [ebx+0x4]
 mov    ecx,DWORD PTR [ebx]
 sub    esp,0x8
 push   edi
 call RECORD24_RANGE_COPY
 mov    ecx,DWORD PTR [ebx+0x4]
 mov    eax,0x2aaaaaab
 sub    ecx,DWORD PTR [ebx]
 add    esp,0x10
 imul   ecx
 mov    eax,DWORD PTR [ebx]
 sar    edx,0x2
 mov.s    ecx,edx
 shr    ecx,0x1f
 add.s    ecx,edx
 mov    DWORD PTR [ebp+0x8],ecx
 test   eax,eax
 je     .L4b28b5
 push   eax
 call   DWORD PTR 0x92d4b0
 mov    ecx,DWORD PTR [ebp+0x8]
 add    esp,0x4
.L4b28b5:
 lea    eax,[esi+esi*2]
 mov    DWORD PTR [ebx],edi
 lea    eax,[edi+eax*8]
 mov    DWORD PTR [ebx+0x8],eax
 lea    eax,[ecx+ecx*2]
 lea    eax,[edi+eax*8]
 pop    edi
 pop    esi
 mov    DWORD PTR [ebx+0x4],eax
 pop    ebx
 pop    ebp
 ret    0x4
.section .note.GNU-stack,"",@progbits
