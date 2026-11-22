# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5d0e90,0x5d0eb4); instruction-contiguous extent, padding excluded.
# Typed JSON accessor: calls 0x5D0D00 for the value, returns its +4 payload only when the type tag is 2,
# otherwise returns the original empty-value sentinel at 0x9998BC. Both RET 4 paths preserved.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x5d0e90..0x5d0eb4
.intel_syntax noprefix
.code32
.text
.global original_json_typed_accessor
original_json_typed_accessor:
.L5d0e90:
 push   ebp
.L5d0e91:
 {load} mov    ebp,esp
.L5d0e93:
 push   DWORD PTR [ebp+0x8]
.L5d0e96:
 call target_5d0d00
.L5d0e9b:
 test   eax,eax
.L5d0e9d:
 jne .L5d0ea8
.L5d0e9f:
 mov    eax,0x9998bc
.L5d0ea4:
 pop    ebp
.L5d0ea5:
 ret    0x4
.L5d0ea8:
 cmp    DWORD PTR [eax],0x2
.L5d0eab:
 jne .L5d0e9f
.L5d0ead:
 mov    eax,DWORD PTR [eax+0x4]
.L5d0eb0:
 pop    ebp
.L5d0eb1:
 ret    0x4
.equ target_5d0d00,0x5d0d00
