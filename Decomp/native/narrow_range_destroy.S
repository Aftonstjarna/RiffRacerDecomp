# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra exports in
# /tmp/cloud-cleanup-review/exports; caller 0x44eb10 and ctor 0x48d6e0.
# Cdecl [ebp+8,ebp+12) range, stride 24; ignores trailing caller tags.
# Empty range bypasses EBX save and import load; otherwise preserve EBX,
# ESI, EDI, EBP. Unsigned capacity +20 >=16 frees pointer via operator
# delete, then sets capacity=15, size=0 and inline first byte=0.
# Does not free range backing allocation; caller 0x44eb10 does that.
# Exact function bounds end at ret; no embedded data, SEH registration or
# local EH cleanup. Dependency failures propagate; no invented cleanup.
# Adjacent functions and alignment padding excluded.
# Original VA range 0x4268f0..0x426930
.intel_syntax noprefix
.code32
.text
.global original_narrow_range_destroy
original_narrow_range_destroy:
.L4268f0:
 push   ebp
.L4268f1:
 {load} mov    ebp,esp
.L4268f3:
 push   esi
.L4268f4:
 mov    esi,DWORD PTR [ebp+0x8]
.L4268f7:
 push   edi
.L4268f8:
 mov    edi,DWORD PTR [ebp+0xc]
.L4268fb:
 {load} cmp    esi,edi
.L4268fd:
 je .L42692c
.L4268ff:
 push   ebx
.L426900:
 mov    ebx,DWORD PTR [imported_operator_delete]
.L426906:
 cmp    DWORD PTR [esi+0x14],0x10
.L42690a:
 jb .L426913
.L42690c:
 push   DWORD PTR [esi]
.L42690e:
 call   ebx
.L426910:
 add    esp,0x4
.L426913:
 mov    DWORD PTR [esi+0x14],0xf
.L42691a:
 mov    DWORD PTR [esi+0x10],0x0
.L426921:
 mov    BYTE PTR [esi],0x0
.L426924:
 add    esi,0x18
.L426927:
 {load} cmp    esi,edi
.L426929:
 jne .L426906
.L42692b:
 pop    ebx
.L42692c:
 pop    edi
.L42692d:
 pop    esi
.L42692e:
 pop    ebp
.L42692f:
 ret
.equ imported_operator_delete,0x92d4b0
