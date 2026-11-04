/* Provenance: depot SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
 * Evidence: /tmp/cloud-string-reset/{exports,narrow_storage_swap.asm}.
 * thiscall ECX lhs, stack rhs, ret 4. Four SSO/heap cases exchange storage only; caller swaps size/capacity. Mixed cases copy length+1 through 0x8f8d66, preserving zero wrap case; both inline calls 0x451d10. No exception frame or embedded data.
 */
# Reviewed symbolic reconstruction; instruction encodings checked by native-check.
# Original VA range 0x451b60..0x451bd5
.intel_syntax noprefix
.code32
.text
.global original_narrow_storage_swap
original_narrow_storage_swap:
.L451b60:
 push   ebp
.L451b61:
 {load} mov    ebp,esp
.L451b63:
 push   esi
.L451b64:
 {load} mov    esi,ecx
.L451b66:
 push   edi
.L451b67:
 cmp    DWORD PTR [esi+0x14],0x10
.L451b6b:
 jb .L451ba1
.L451b6d:
 mov    edi,DWORD PTR [ebp+0x8]
.L451b70:
 cmp    DWORD PTR [edi+0x14],0x10
.L451b74:
 jb .L451b84
.L451b76:
 mov    edx,DWORD PTR [esi]
.L451b78:
 mov    eax,DWORD PTR [edi]
.L451b7a:
 mov    DWORD PTR [esi],eax
.L451b7c:
 mov    DWORD PTR [edi],edx
.L451b7e:
 pop    edi
.L451b7f:
 pop    esi
.L451b80:
 pop    ebp
.L451b81:
 ret    0x4
.L451b84:
 mov    eax,DWORD PTR [edi+0x10]
.L451b87:
 push   ebx
.L451b88:
 mov    ebx,DWORD PTR [esi]
.L451b8a:
 inc    eax
.L451b8b:
 je .L451b98
.L451b8d:
 push   eax
.L451b8e:
 push   edi
.L451b8f:
 push   esi
.L451b90:
 call target_8f8d66
.L451b95:
 add    esp,0xc
.L451b98:
 mov    DWORD PTR [edi],ebx
.L451b9a:
 pop    ebx
.L451b9b:
 pop    edi
.L451b9c:
 pop    esi
.L451b9d:
 pop    ebp
.L451b9e:
 ret    0x4
.L451ba1:
 mov    eax,DWORD PTR [ebp+0x8]
.L451ba4:
 cmp    DWORD PTR [eax+0x14],0x10
.L451ba8:
 jae .L451bba
.L451baa:
 push   eax
.L451bab:
 push   esi
.L451bac:
 call target_451d10
.L451bb1:
 add    esp,0x8
.L451bb4:
 pop    edi
.L451bb5:
 pop    esi
.L451bb6:
 pop    ebp
.L451bb7:
 ret    0x4
.L451bba:
 mov    ecx,DWORD PTR [esi+0x10]
.L451bbd:
 mov    edi,DWORD PTR [eax]
.L451bbf:
 inc    ecx
.L451bc0:
 je .L451bcd
.L451bc2:
 push   ecx
.L451bc3:
 push   esi
.L451bc4:
 push   eax
.L451bc5:
 call target_8f8d66
.L451bca:
 add    esp,0xc
.L451bcd:
 mov    DWORD PTR [esi],edi
.L451bcf:
 pop    edi
.L451bd0:
 pop    esi
.L451bd1:
 pop    ebp
.L451bd2:
 ret    0x4
.equ target_451d10,0x451d10
.equ target_8f8d66,0x8f8d66
