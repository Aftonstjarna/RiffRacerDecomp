# Provenance: mechanically transcribed from the supported original Game.exe.
# SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reference assembly only; not compiler-built matching high-level source.
# Boundaries/control flow reviewed against original objdump and targeted Ghidra
# ExportRecovery output. INT3 padding excluded; no embedded instruction data.
# No local SEH registration. Imported/runtime behavior is not reconstructed.
# ECX=destination, [entry ESP+4]=terminated UTF-16 pointer, RET 4.
# Scan to the first zero WCHAR, then call accepted wide_assign_range with
# pointer and length excluding the terminator. Empty input calls it with zero.
# EAX is the delegate result; EBP/ESI/EDI preserved. No null-pointer check.
# Ghidra omits the implicit ECX input; original instructions establish the ABI.
# Original VA range 0x44f790..0x44f7d1
.intel_syntax noprefix
.code32
.text
.global original_wide_assign_pointer
original_wide_assign_pointer:
.L44f790:
 push   ebp
.L44f791:
 {load} mov    ebp,esp
.L44f793:
 mov    edx,DWORD PTR [ebp+0x8]
.L44f796:
 push   esi
.L44f797:
 {load} mov    esi,ecx
.L44f799:
 cmp    WORD PTR [edx],0x0
.L44f79d:
 jne .L44f7ad
.L44f79f:
 {load} xor    eax,eax
.L44f7a1:
 push   eax
.L44f7a2:
 push   edx
.L44f7a3:
 call wide_assign_range
.L44f7a8:
 pop    esi
.L44f7a9:
 pop    ebp
.L44f7aa:
 ret    0x4
.L44f7ad:
 {load} mov    eax,edx
.L44f7af:
 push   edi
.L44f7b0:
 lea    edi,[eax+0x2]
.L44f7b3:
 mov    cx,WORD PTR [eax]
.L44f7b6:
 add    eax,0x2
.L44f7b9:
 test   cx,cx
.L44f7bc:
 jne .L44f7b3
.L44f7be:
 {load} sub    eax,edi
.L44f7c0:
 {load} mov    ecx,esi
.L44f7c2:
 pop    edi
.L44f7c3:
 sar    eax,1
.L44f7c5:
 push   eax
.L44f7c6:
 push   edx
.L44f7c7:
 call wide_assign_range
.L44f7cc:
 pop    esi
.L44f7cd:
 pop    ebp
.L44f7ce:
 ret    0x4
.equ wide_assign_range,0x44f9b0
.section .note.GNU-stack,"",@progbits
