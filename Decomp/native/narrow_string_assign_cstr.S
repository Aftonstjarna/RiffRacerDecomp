# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x4b2f50,0x4b2f94); instruction-contiguous extent, INT3 padding excluded.
# Narrow-string assignment from a C string: measures the byte string, assigns through helper 0x442170 and returns the destination object from 0x416AF0. No allocation path of its own beyond helpers; called by HTTP request construction.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x4b2f50..0x4b2f94
.intel_syntax noprefix
.code32
.text
.global original_narrow_string_assign_cstr
original_narrow_string_assign_cstr:
.L4b2f50:
 push   ebp
.L4b2f51:
 {load} mov    ebp,esp
.L4b2f53:
 push   ecx
.L4b2f54:
 mov    edx,DWORD PTR [ebp+0x10]
.L4b2f57:
 push   esi
.L4b2f58:
 mov    DWORD PTR [ebp-0x4],0x0
.L4b2f5f:
 cmp    BYTE PTR [edx],0x0
.L4b2f62:
 jne .L4b2f68
.L4b2f64:
 {load} xor    eax,eax
.L4b2f66:
 jmp .L4b2f79
.L4b2f68:
 {load} mov    eax,edx
.L4b2f6a:
 lea    esi,[eax+0x1]
.L4b2f6d:
 {disp8} lea    ecx,[ecx+0x0]
.L4b2f70:
 mov    cl,BYTE PTR [eax]
.L4b2f72:
 inc    eax
.L4b2f73:
 test   cl,cl
.L4b2f75:
 jne .L4b2f70
.L4b2f77:
 {load} sub    eax,esi
.L4b2f79:
 mov    ecx,DWORD PTR [ebp+0xc]
.L4b2f7c:
 push   eax
.L4b2f7d:
 push   edx
.L4b2f7e:
 call target_442170
.L4b2f83:
 mov    ecx,DWORD PTR [ebp+0x8]
.L4b2f86:
 push   eax
.L4b2f87:
 call target_416af0
.L4b2f8c:
 mov    eax,DWORD PTR [ebp+0x8]
.L4b2f8f:
 pop    esi
.L4b2f90:
 {load} mov    esp,ebp
.L4b2f92:
 pop    ebp
.L4b2f93:
 ret
.equ target_416af0,0x416af0
.equ target_442170,0x442170
