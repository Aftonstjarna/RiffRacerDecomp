# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x426af0..0x426bd5 exclusive; all three returns included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_pool_block_commit
original_pool_block_commit:
# ECX=output offset slot; stack args=block, terminated source, aligned allocation bytes.
# Leaf thiscall, ret 12; preserves EBX/ESI/EDI/EBP; reads arena base at 0xbfcb38.
.L426af0:
 push   ebp
.L426af1:
 {load} mov    ebp,esp
.L426af3:
 push   ecx
.L426af4:
 mov    edx,DWORD PTR [ebp+0xc]
.L426af7:
 push   ebx
.L426af8:
 push   esi
.L426af9:
 push   edi
.L426afa:
 mov    edi,DWORD PTR [ebp+0x8]
.L426afd:
 {load} mov    esi,edx
.L426aff:
 mov    DWORD PTR [ebp-0x4],ecx
.L426b02:
 mov    ecx,DWORD PTR [edi]
.L426b04:
 lea    ebx,[esi+0x1]
.L426b07:
 {load} mov    eax,ecx
.L426b09:
 shr    eax,0x1e
.L426b0c:
 and    eax,0xffffff01
.L426b11:
 mov    DWORD PTR [ebp+0x8],eax
# Scan full source length before copying.
.L426b14:
 mov    al,BYTE PTR [esi]
.L426b16:
 inc    esi
.L426b17:
 test   al,al
.L426b19:
 jne .L426b14
.L426b1b:
 mov    eax,DWORD PTR [ebp+0x10]
.L426b1e:
 {load} sub    esi,ebx
.L426b20:
 mov    ebx,DWORD PTR [edi]
.L426b22:
 and    ecx,0x7fff
.L426b28:
 shr    eax,0x3
.L426b2b:
 and    ebx,0x3fff8000
.L426b31:
 and    eax,0x7fff
.L426b36:
 shl    ecx,0x3
.L426b39:
 {load} or     eax,ebx
.L426b3b:
 or     eax,0x80000000
.L426b40:
 mov    DWORD PTR [edi],eax
.L426b42:
 lea    eax,[edi+0x4]
.L426b45:
 {load} sub    eax,edx
.L426b47:
 {load} mov    ebx,eax
.L426b49:
 {disp32} lea    esp,[esp+0x0]
# Copy includes the terminating NUL.
.L426b50:
 mov    al,BYTE PTR [edx]
.L426b52:
 lea    edx,[edx+0x1]
.L426b55:
 mov    BYTE PTR [ebx+edx*1-0x1],al
.L426b59:
 test   al,al
.L426b5b:
 jne .L426b50
.L426b5d:
 mov    edx,DWORD PTR [ebp-0x4]
.L426b60:
 mov    ebx,DWORD PTR [ebp+0x10]
.L426b63:
 mov    BYTE PTR [esi+edi*1+0x4],al
.L426b67:
 {load} mov    eax,edi
.L426b69:
 sub    eax,DWORD PTR [arena_base]
.L426b6f:
 mov    DWORD PTR [edx],eax
# Exact-size allocation versus remainder split.
.L426b71:
 {load} cmp    ebx,ecx
.L426b73:
 je .L426bc0
.L426b75:
 {load} sub    ecx,ebx
.L426b77:
 lea    edx,[edi+ebx*1]
.L426b7a:
 {load} mov    eax,ecx
.L426b7c:
 and    ebx,0x3fff8
.L426b82:
 shr    eax,0x3
.L426b85:
 and    eax,0x7fff
.L426b8a:
 shl    ebx,0xc
.L426b8d:
 {load} or     eax,ebx
.L426b8f:
 cmp    BYTE PTR [ebp+0x8],0x0
.L426b93:
 mov    DWORD PTR [edx],eax
.L426b95:
 je .L426ba7
.L426b97:
 pop    edi
.L426b98:
 or     eax,0x40000000
.L426b9d:
 pop    esi
.L426b9e:
 mov    DWORD PTR [edx],eax
.L426ba0:
 pop    ebx
.L426ba1:
 {load} mov    esp,ebp
.L426ba3:
 pop    ebp
.L426ba4:
 ret    0xc
# Nonterminal split updates the following backward-span bits.
.L426ba7:
 lea    eax,[edx+ecx*1]
.L426baa:
 shl    ecx,0xc
.L426bad:
 xor    ecx,DWORD PTR [eax]
.L426baf:
 pop    edi
.L426bb0:
 and    ecx,0x3fff8000
.L426bb6:
 xor    DWORD PTR [eax],ecx
.L426bb8:
 pop    esi
.L426bb9:
 pop    ebx
.L426bba:
 {load} mov    esp,ebp
.L426bbc:
 pop    ebp
.L426bbd:
 ret    0xc
# Exact-size path propagates the original terminal flag.
.L426bc0:
 cmp    BYTE PTR [ebp+0x8],0x0
.L426bc4:
 je .L426bcc
.L426bc6:
 or     DWORD PTR [edi],0x40000000
.L426bcc:
 pop    edi
.L426bcd:
 pop    esi
.L426bce:
 pop    ebx
.L426bcf:
 {load} mov    esp,ebp
.L426bd1:
 pop    ebp
.L426bd2:
 ret    0xc
.equ arena_base,0xbfcb38
.section .note.GNU-stack,"",@progbits
