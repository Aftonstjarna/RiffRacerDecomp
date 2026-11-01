# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump instructions and private Ghidra Strings export
# /tmp/cloud-string-batch/exports; Ghidra inclusive body end 0x0053606f.
# VA [0x536030,0x536070); no inline data; excludes following INT3 padding.
# ECX=destination; stack source pointer; EAX=destination; ret 4.
# Self-assignment bypasses release/reset/copy. Otherwise capacity >=8 frees
# old buffer through IAT 0x92d4b0, resets inline capacity=7 and length=0,
# stores UTF-16 NUL, then calls unresolved copy helper 0x44f890.
# ESI/EBP preserved. No cookie or SEH frame; callee exceptions propagate.
.intel_syntax noprefix
.code32
.text
.global original_wide_assign
original_wide_assign:
.L536030:
 push   ebp
.L536031:
 {load} mov    ebp,esp
.L536033:
 push   esi
.L536034:
 {load} mov    esi,ecx
.L536036:
 cmp    esi,DWORD PTR [ebp+0x8]
.L536039:
 je .L536069
.L53603b:
 cmp    DWORD PTR [esi+0x14],0x8
.L53603f:
 jb .L53604c
.L536041:
 push   DWORD PTR [esi]
.L536043:
 call   DWORD PTR [0x92d4b0]
.L536049:
 add    esp,0x4
.L53604c:
 push   DWORD PTR [ebp+0x8]
.L53604f:
 {load} xor    eax,eax
.L536051:
 mov    DWORD PTR [esi+0x14],0x7
.L536058:
 mov    DWORD PTR [esi+0x10],0x0
.L53605f:
 {load} mov    ecx,esi
.L536061:
 mov    WORD PTR [esi],ax
.L536064:
 call target_44f890
.L536069:
 {load} mov    eax,esi
.L53606b:
 pop    esi
.L53606c:
 pop    ebp
.L53606d:
 ret    0x4
.equ target_44f890,0x44f890
