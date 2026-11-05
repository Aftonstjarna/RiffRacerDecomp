# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41c470,0x41c4e0); all paths, including both tail jumps.
.intel_syntax noprefix
.code32
.text
.global original_u16_vector_ensure_spare
.equ reallocate_u16,0x41c560
original_u16_vector_ensure_spare:
 push   ebp
 {load} mov    ebp,esp
 mov    edx,DWORD PTR [ecx+0x8]
 {load} mov    eax,edx
 push   esi
 mov    esi,DWORD PTR [ecx+0x4]
 {load} sub    eax,esi
 push   edi
 mov    edi,DWORD PTR [ebp+0x8]
 sar    eax,1
 {load} cmp    eax,edi
 jae    .L41c4da
 sub    esi,DWORD PTR [ecx]
 push   ebx
 mov    ebx,0x7fffffff
 sar    esi,1
 {load} mov    eax,ebx
 {load} sub    eax,esi
 {load} cmp    eax,edi
 jae    .L41c4a5
 push   0x999938
 call   DWORD PTR [0x92d168]
.L41c4a5:
 sub    edx,DWORD PTR [ecx]
 {load} add    esi,edi
 sar    edx,1
 {load} mov    eax,edx
 shr    eax,1
 {load} sub    ebx,eax
 {load} cmp    ebx,edx
 pop    ebx
 jae    .L41c4c8
 {load} xor    edx,edx
 {load} cmp    edx,esi
 pop    edi
 cmovb  edx,esi
 pop    esi
 mov    DWORD PTR [ebp+0x8],edx
 pop    ebp
 jmp    reallocate_u16
.L41c4c8:
 {load} add    edx,eax
 {load} cmp    edx,esi
 pop    edi
 cmovb  edx,esi
 pop    esi
 mov    DWORD PTR [ebp+0x8],edx
 pop    ebp
 jmp    reallocate_u16
.L41c4da:
 pop    edi
 pop    esi
 pop    ebp
 ret    0x4
.section .note.GNU-stack,"",@progbits
