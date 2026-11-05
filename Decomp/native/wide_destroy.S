# Provenance: mechanically transcribed from the supported original Game.exe.
# SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reference assembly only; not compiler-built matching high-level source.
# Boundaries/control flow reviewed against original objdump and targeted Ghidra
# ExportRecovery output. INT3 padding excluded; no embedded instruction data.
# No local SEH registration. Imported/runtime behavior is not reconstructed.
# ECX=string. Capacity >=8 calls scalar delete on the buffer; then reset
# capacity=7, length=0 and first WCHAR=0. Inline storage bypasses delete.
# ESI preserved; plain RET. No allocation or reference-count operation.
# Original VA range 0x44f760..0x44f789
.intel_syntax noprefix
.code32
.text
.global original_wide_destroy
original_wide_destroy:
.L44f760:
 push   esi
.L44f761:
 {load} mov    esi,ecx
.L44f763:
 cmp    DWORD PTR [esi+0x14],0x8
.L44f767:
 jb .L44f774
.L44f769:
 push   DWORD PTR [esi]
.L44f76b:
 call   DWORD PTR [wide_scalar_delete_iat]
.L44f771:
 add    esp,0x4
.L44f774:
 mov    DWORD PTR [esi+0x14],0x7
.L44f77b:
 {load} xor    eax,eax
.L44f77d:
 mov    DWORD PTR [esi+0x10],0x0
.L44f784:
 mov    WORD PTR [esi],ax
.L44f787:
 pop    esi
.L44f788:
 ret
.equ wide_scalar_delete_iat,0x92d4b0
.section .note.GNU-stack,"",@progbits
