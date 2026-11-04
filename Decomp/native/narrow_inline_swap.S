/* Provenance: depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
 * Evidence: /tmp/cloud-string-reset/{exports,narrow_inline_swap.asm}.
 * cdecl two pointers; swaps 16 inline bytes unless identical or unsigned end-pointer wrap. Preserves EBX/ESI/EDI, caller removes arguments. No calls, exception frame or embedded data.
 */
# Reviewed symbolic reconstruction; instruction encodings checked by native-check.
# Original VA range 0x451d10..0x451d50
.intel_syntax noprefix
.code32
.text
.global original_narrow_inline_swap
original_narrow_inline_swap:
.L451d10:
 push   ebp
.L451d11:
 {load} mov    ebp,esp
.L451d13:
 mov    eax,DWORD PTR [ebp+0x8]
.L451d16:
 push   edi
.L451d17:
 mov    edi,DWORD PTR [ebp+0xc]
.L451d1a:
 {load} cmp    eax,edi
.L451d1c:
 je .L451d4d
.L451d1e:
 push   ebx
.L451d1f:
 lea    ecx,[eax+0x10]
.L451d22:
 {load} xor    edx,edx
.L451d24:
 {load} mov    ebx,ecx
.L451d26:
 {load} sub    ebx,eax
.L451d28:
 push   esi
.L451d29:
 {load} xor    esi,esi
.L451d2b:
 {load} cmp    eax,ecx
.L451d2d:
 cmova  ebx,edx
.L451d30:
 test   ebx,ebx
.L451d32:
 je .L451d4b
.L451d34:
 {load} sub    edi,eax
.L451d36:
 mov    cl,BYTE PTR [edi+eax*1]
.L451d39:
 lea    eax,[eax+0x1]
.L451d3c:
 mov    dl,BYTE PTR [eax-0x1]
.L451d3f:
 inc    esi
.L451d40:
 mov    BYTE PTR [eax-0x1],cl
.L451d43:
 mov    BYTE PTR [edi+eax*1-0x1],dl
.L451d47:
 {load} cmp    esi,ebx
.L451d49:
 jne .L451d36
.L451d4b:
 pop    esi
.L451d4c:
 pop    ebx
.L451d4d:
 pop    edi
.L451d4e:
 pop    ebp
.L451d4f:
 ret
