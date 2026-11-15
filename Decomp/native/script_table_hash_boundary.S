.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4f0d80,0x4f0e84); both returns included.
.global original_script_table_hash_boundary
.equ GET_INTEGER,0x4f0ae0
.equ NIL_VALUE,0x99a41c
original_script_table_hash_boundary:
 push   ebp
 mov.s    ebp,esp
 sub    esp,0x8
 push   ebx
 push   esi
 push   edi
 mov.s    edi,edx
 mov    DWORD PTR [ebp-0x4],ecx
 mov.s    ebx,edi
 xorps  xmm2,xmm2
 inc    edi
 jmp    .L4f0d99
.L4f0d96:
 mov    ecx,DWORD PTR [ebp-0x4]
.L4f0d99:
 lea    eax,[edi-0x1]
 cmp    eax,DWORD PTR [ecx+0x1c]
 jae    .L4f0dac
 mov    eax,DWORD PTR [ecx+0xc]
 lea    ecx,[edi-0x1]
 lea    ecx,[eax+ecx*8]
 jmp    .L4f0e07
.L4f0dac:
 movd   xmm1,edi
 cvtdq2ps xmm1,xmm1
 ucomiss xmm1,xmm2
 movss  DWORD PTR [ebp-0x8],xmm1
 lahf
 test   ah,0x44
 jp     .L4f0dc6
 mov    ecx,DWORD PTR [ecx+0x10]
 jmp    .L4f0de7
.L4f0dc6:
 mov    cl,BYTE PTR [ecx+0x7]
 mov    esi,0x1
 mov    eax,DWORD PTR [ebp-0x8]
 xor.s    edx,edx
 shl    esi,cl
 dec    esi
 or     esi,0x1
 div    esi
 mov    eax,DWORD PTR [ebp-0x4]
 mov    eax,DWORD PTR [eax+0x10]
 lea    ecx,[edx+edx*4]
 lea    ecx,[eax+ecx*4]
.L4f0de7:
 cmp    DWORD PTR [ecx+0xc],0x3
 jne    .L4f0dfb
 movss  xmm0,DWORD PTR [ecx+0x8]
 ucomiss xmm0,xmm1
 lahf
 test   ah,0x44
 jnp    .L4f0e07
.L4f0dfb:
 mov    ecx,DWORD PTR [ecx+0x10]
 test   ecx,ecx
 jne    .L4f0de7
 mov    ecx,NIL_VALUE
.L4f0e07:
 cmp    DWORD PTR [ecx+0x4],0x0
 je     .L4f0e4e
 mov.s    ebx,edi
 add.s    edi,edi
 cmp    edi,0x7ffffffd
 jbe    .L4f0d96
 mov    ebx,DWORD PTR [ebp-0x4]
 mov    esi,0x1
 mov.s    edx,esi
 mov.s    ecx,ebx
 call   GET_INTEGER
 cmp    DWORD PTR [eax+0x4],0x0
 je     .L4f0e44
.L4f0e34:
 inc    esi
 mov.s    ecx,ebx
 mov.s    edx,esi
 call   GET_INTEGER
 cmp    DWORD PTR [eax+0x4],0x0
 jne    .L4f0e34
.L4f0e44:
 pop    edi
 lea    eax,[esi-0x1]
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.L4f0e4e:
 mov.s    eax,edi
 sub.s    eax,ebx
 cmp    eax,0x1
 jbe    .L4f0e7b
.L4f0e57:
 mov    ecx,DWORD PTR [ebp-0x4]
 lea    esi,[ebx+edi*1]
 shr    esi,1
 mov.s    edx,esi
 call   GET_INTEGER
 cmp    DWORD PTR [eax+0x4],0x0
 jne    .L4f0e70
 mov.s    edi,esi
 jmp    .L4f0e72
.L4f0e70:
 mov.s    ebx,esi
.L4f0e72:
 mov.s    ecx,edi
 sub.s    ecx,ebx
 cmp    ecx,0x1
 ja     .L4f0e57
.L4f0e7b:
 pop    edi
 pop    esi
 mov.s    eax,ebx
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
