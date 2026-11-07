# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b28d0,0x4b2962); both RET 4 paths included.
.intel_syntax noprefix
.code32
.text
.global original_record24_ensure_spare
.equ RECORD24_REALLOCATE,0x4b2840
.equ XLENGTH_SLOT,0x92d168
.equ TOO_LONG_TEXT,0x999938
original_record24_ensure_spare:
 push   esi
 mov    esi,DWORD PTR [ecx+0x4]
 mov    eax,0x2aaaaaab
 push   edi
 mov    edi,DWORD PTR [ecx+0x8]
 mov.s    edx,edi
 sub.s    edx,esi
 imul   edx
 sar    edx,0x2
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x1
 jae    .L4b295d
 sub    esi,DWORD PTR [ecx]
 mov    eax,0x2aaaaaab
 imul   esi
 push   ebx
 sar    edx,0x2
 mov    ebx,0xaaaaaaa
 mov.s    esi,edx
 mov.s    eax,ebx
 shr    esi,0x1f
 add.s    esi,edx
 sub.s    eax,esi
 cmp    eax,0x1
 jae    .L4b291f
 push   TOO_LONG_TEXT
 call   DWORD PTR [XLENGTH_SLOT]
.L4b291f:
 sub    edi,DWORD PTR [ecx]
 mov    eax,0x2aaaaaab
 imul   edi
 inc    esi
 sar    edx,0x2
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 mov.s    edx,eax
 shr    edx,1
 sub.s    ebx,edx
 cmp.s    ebx,eax
 pop    ebx
 jae    .L4b2950
 xor.s    eax,eax
 cmp.s    eax,esi
 cmovb  eax,esi
 push   eax
 call RECORD24_REALLOCATE
 pop    edi
 pop    esi
 ret    0x4
.L4b2950:
 add.s    eax,edx
 cmp.s    eax,esi
 cmovb  eax,esi
 push   eax
 call RECORD24_REALLOCATE
.L4b295d:
 pop    edi
 pop    esi
 ret    0x4
.section .note.GNU-stack,"",@progbits
