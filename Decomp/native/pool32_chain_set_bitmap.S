# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x453580,0x4535d6). Leaf, two conditional branches, one RET.
# cdecl: non-null chain head at [entry ESP+4]; next pointer at node+0xc.
# Requires initialized pool base, bitmap pointer and bit count; no allocation.
.intel_syntax noprefix
.code32
.text
.global original_pool32_chain_set_bitmap
.equ POOL_BASE,0xbfcc0c
.equ BITMAP_POINTER,0xc007b0
.equ BIT_COUNT,0xc007b4
original_pool32_chain_set_bitmap:
 push ebp
 mov.s ebp,esp
 push ebx
 mov ebx,DWORD PTR [POOL_BASE]
 push esi
 push edi
 mov edi,DWORD PTR [ebp+8]
 nop
.Lnode:
 mov.s ecx,edi
 sub.s ecx,ebx
 shr ecx,5
 add.s ecx,ecx
 cmp ecx,DWORD PTR [BIT_COUNT]
 jae .Lnext
 mov.s edx,ecx
 mov esi,1
 shr edx,5
 mov.s eax,edx
 shl eax,5
 sub.s ecx,eax
 mov eax,DWORD PTR [BITMAP_POINTER]
 shl esi,cl
 lea ecx,[eax+edx*4]
 mov.s eax,esi
 not eax
 and DWORD PTR [ecx],eax
 mov eax,DWORD PTR [BITMAP_POINTER]
 or DWORD PTR [eax+edx*4],esi
.Lnext:
 mov edi,DWORD PTR [edi+0xc]
 test edi,edi
 jne .Lnode
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
