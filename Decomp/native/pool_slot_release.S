# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x426be0..0x426cb3 exclusive; adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_pool_slot_release
original_pool_slot_release:
# ECX points to a 32-bit arena offset slot. No stack arguments; plain RET.
# Leaf: arena base is read from 0xbfcb38; EBX/ESI/EDI/EBP preserved.
.L426be0:
 push   ebp
.L426be1:
 {load} mov    ebp,esp
.L426be3:
 push   ecx
.L426be4:
 push   edi
.L426be5:
 {load} mov    edi,ecx
.L426be7:
 mov    DWORD PTR [ebp-0x4],edi
# A zero slot returns without touching the arena.
.L426bea:
 mov    ecx,DWORD PTR [edi]
.L426bec:
 test   ecx,ecx
.L426bee:
 je     .L426cae
.L426bf4:
 push   ebx
.L426bf5:
 push   esi
# Clear allocation bit and merge a free following block using 8-byte size units.
.L426bf6:
 mov    esi,DWORD PTR [arena_base]
.L426bfc:
 and    DWORD PTR [esi+ecx*1],0x7fffffff
.L426c03:
 {load} add    esi,ecx
.L426c05:
 mov    ebx,DWORD PTR [esi]
.L426c07:
 {load} mov    ecx,ebx
.L426c09:
 and    ecx,0x7fff
.L426c0f:
 shl    ecx,0x3
.L426c12:
 mov    edx,DWORD PTR [ecx+esi*1]
.L426c15:
 test   edx,edx
.L426c17:
 js     .L426c44
.L426c19:
 {load} mov    eax,edx
.L426c1b:
 and    edx,0x7fff
.L426c21:
 shr    eax,0x1e
.L426c24:
 lea    ecx,[ecx+edx*8]
.L426c27:
 {load} mov    edx,ecx
.L426c29:
 shr    edx,0x3
.L426c2c:
 {load} xor    edx,ebx
.L426c2e:
 and    edx,0x7fff
.L426c34:
 {load} xor    edx,ebx
.L426c36:
 mov    DWORD PTR [esi],edx
.L426c38:
 and    al,0x1
.L426c3a:
 je     .L426c44
.L426c3c:
 or     edx,0x40000000
.L426c42:
 mov    DWORD PTR [esi],edx
# Decode backward span and end flag; merge a free predecessor except at arena base.
.L426c44:
 mov    eax,DWORD PTR [esi]
.L426c46:
 {load} mov    edx,esi
.L426c48:
 {load} mov    ebx,eax
.L426c4a:
 shr    eax,0xc
.L426c4d:
 and    eax,0x3fff8
.L426c52:
 shr    ebx,0x1e
.L426c55:
 {load} sub    edx,eax
.L426c57:
 and    bl,0x1
.L426c5a:
 cmp    edx,DWORD PTR [arena_base]
.L426c60:
 je     .L426c92
.L426c62:
 mov    edi,DWORD PTR [edx]
.L426c64:
 test   edi,edi
.L426c66:
 js     .L426c8f
.L426c68:
 {load} mov    eax,edi
.L426c6a:
 and    eax,0x7fff
.L426c6f:
 lea    ecx,[ecx+eax*8]
.L426c72:
 {load} mov    eax,ecx
.L426c74:
 shr    eax,0x3
.L426c77:
 {load} xor    eax,edi
.L426c79:
 and    eax,0x7fff
.L426c7e:
 {load} xor    eax,edi
.L426c80:
 mov    DWORD PTR [edx],eax
.L426c82:
 test   bl,bl
.L426c84:
 je     .L426c8d
.L426c86:
 or     eax,0x40000000
.L426c8b:
 mov    DWORD PTR [edx],eax
.L426c8d:
 {load} mov    esi,edx
.L426c8f:
 mov    edi,DWORD PTR [ebp-0x4]
# Unless this is the terminal block, update the following backward-span field.
.L426c92:
 test   bl,bl
.L426c94:
 jne    .L426ca6
.L426c96:
 lea    eax,[ecx+esi*1]
.L426c99:
 shl    ecx,0xc
.L426c9c:
 xor    ecx,DWORD PTR [eax]
.L426c9e:
 and    ecx,0x3fff8000
.L426ca4:
 xor    DWORD PTR [eax],ecx
# Clear the released slot after updating arena metadata.
.L426ca6:
 pop    esi
.L426ca7:
 mov    DWORD PTR [edi],0x0
.L426cad:
 pop    ebx
.L426cae:
 pop    edi
.L426caf:
 {load} mov    esp,ebp
.L426cb1:
 pop    ebp
.L426cb2:
 ret
.equ arena_base,0xbfcb38
.section .note.GNU-stack,"",@progbits
