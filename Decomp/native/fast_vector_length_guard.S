# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x561740,0x5617a5); instruction-contiguous extent, INT3 padding excluded.
# vectorfast length guard: compares the requested element count against the container capacity and throws through the original std::length_error import. No allocation is performed here.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x561740..0x5617a5
.intel_syntax noprefix
.code32
.text
.global original_fast_vector_length_guard
original_fast_vector_length_guard:
.L561740:
 mov    edx,DWORD PTR [ecx+0x8]
.L561743:
 {load} mov    eax,edx
.L561745:
 push   esi
.L561746:
 mov    esi,DWORD PTR [ecx+0x4]
.L561749:
 {load} sub    eax,esi
.L56174b:
 sar    eax,0x2
.L56174e:
 cmp    eax,0x1
.L561751:
 jae .L5617a1
.L561753:
 sub    esi,DWORD PTR [ecx]
.L561755:
 push   edi
.L561756:
 mov    edi,0x3fffffff
.L56175b:
 sar    esi,0x2
.L56175e:
 {load} mov    eax,edi
.L561760:
 {load} sub    eax,esi
.L561762:
 cmp    eax,0x1
.L561765:
 jae .L561772
.L561767:
 push   0x9fdf88
.L56176c:
 call   DWORD PTR [0x92d168]
.L561772:
 sub    edx,DWORD PTR [ecx]
.L561774:
 inc    esi
.L561775:
 sar    edx,0x2
.L561778:
 {load} mov    eax,edx
.L56177a:
 shr    eax,1
.L56177c:
 {load} sub    edi,eax
.L56177e:
 {load} cmp    edi,edx
.L561780:
 pop    edi
.L561781:
 jae .L561794
.L561783:
 {load} xor    edx,edx
.L561785:
 {load} cmp    edx,esi
.L561787:
 cmovb  edx,esi
.L56178a:
 push   edx
.L56178b:
 call target_426800
.L561790:
 pop    esi
.L561791:
 ret    0x4
.L561794:
 {load} add    edx,eax
.L561796:
 {load} cmp    edx,esi
.L561798:
 cmovb  edx,esi
.L56179b:
 push   edx
.L56179c:
 call target_426800
.L5617a1:
 pop    esi
.L5617a2:
 ret    0x4
.equ target_426800,0x426800
