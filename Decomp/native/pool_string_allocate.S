# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x426a30..0x426ae4 exclusive, both returns; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_pool_string_allocate
original_pool_string_allocate:
# ECX=offset destination slot, [entry ESP+4]=NUL-terminated string; thiscall RET 4.
# EBX/ESI/EDI/EBP preserved. EAX is incidental, no consistent return value.
.L426a30:
 push   ebp
.L426a31:
 {load} mov    ebp,esp
.L426a33:
 mov    edx,DWORD PTR [arena_base]
.L426a39:
 push   ebx
.L426a3a:
 {load} mov    ebx,ecx
.L426a3c:
 push   edi
.L426a3d:
 test   edx,edx
.L426a3f:
 jne    .L426a7d
# Lazy arena initialization: allocate and zero 128 KiB; no null check.
.L426a41:
 push   0x20000
.L426a46:
 call   target_8f87c8
.L426a4b:
 push   0x20000
.L426a50:
 push   0x0
.L426a52:
 push   eax
.L426a53:
 mov    [arena_base],eax
.L426a58:
 call   target_8f8d7e
.L426a5d:
 mov    eax,[arena_base]
.L426a62:
 add    esp,0x10
.L426a65:
 mov    DWORD PTR [eax],0x80000001
.L426a6b:
 mov    eax,[arena_base]
.L426a70:
 mov    DWORD PTR [eax+0x8],0x4000bfff
.L426a77:
 mov    edx,DWORD PTR [arena_base]
# Empty input clears the destination offset, after initialization.
.L426a7d:
 mov    edi,DWORD PTR [ebp+0x8]
.L426a80:
 cmp    BYTE PTR [edi],0x0
.L426a83:
 jne    .L426a91
.L426a85:
 pop    edi
.L426a86:
 mov    DWORD PTR [ebx],0x0
.L426a8c:
 pop    ebx
.L426a8d:
 pop    ebp
.L426a8e:
 ret    0x4
# Scan source and round length+5 up to 8 bytes (32-bit arithmetic).
.L426a91:
 {load} mov    ecx,edi
.L426a93:
 push   esi
.L426a94:
 lea    esi,[ecx+0x1]
.L426a97:
 mov    al,BYTE PTR [ecx]
.L426a99:
 inc    ecx
.L426a9a:
 test   al,al
.L426a9c:
 jne    .L426a97
.L426a9e:
 {load} sub    ecx,esi
.L426aa0:
 lea    esi,[ecx+0x5]
.L426aa3:
 {load} mov    ecx,esi
.L426aa5:
 and    ecx,0x7
.L426aa8:
 je     .L426ab3
.L426aaa:
 mov    eax,0x8
.L426aaf:
 {load} sub    eax,ecx
.L426ab1:
 {load} add    esi,eax
# First-fit scan: low 15 bits encode span in eight-byte units.
.L426ab3:
 mov    ecx,DWORD PTR [edx]
.L426ab5:
 {load} mov    eax,ecx
.L426ab7:
 and    eax,0x7fff
.L426abc:
 shl    eax,0x3
.L426abf:
 test   ecx,ecx
.L426ac1:
 js     .L426ac7
.L426ac3:
 {load} cmp    eax,esi
.L426ac5:
 jae    .L426ad3
# Terminal flag stops search; exhaustion leaves destination unchanged.
.L426ac7:
 test   ecx,0x40000000
.L426acd:
 jne    .L426add
.L426acf:
 {load} add    edx,eax
.L426ad1:
 jmp    .L426ab3
# Commit chosen block, using accepted pool-block-commit reference.
.L426ad3:
 push   esi
.L426ad4:
 push   edi
.L426ad5:
 push   edx
.L426ad6:
 {load} mov    ecx,ebx
.L426ad8:
 call   target_426af0
.L426add:
 pop    esi
.L426ade:
 pop    edi
.L426adf:
 pop    ebx
.L426ae0:
 pop    ebp
.L426ae1:
 ret    0x4
.equ arena_base,0xbfcb38
.equ target_8f87c8,0x8f87c8
.equ target_8f8d7e,0x8f8d7e
.equ target_426af0,0x426af0
.section .note.GNU-stack,"",@progbits
