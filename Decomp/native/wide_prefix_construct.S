# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump instructions and private Ghidra Strings export
# /tmp/cloud-string-batch/exports; Ghidra inclusive body end 0x005360a6.
# VA [0x536070,0x5360a7); no inline data; excludes following INT3 padding.
# ECX=source string; stack arguments destination, unused slot, maximum count.
# Initializes destination capacity=7, length=0 and UTF-16 NUL, then calls
# 0x44fb30(destination=this, source, offset=0, count). Returns destination, ret 12.
# Source-register ABI confirmed at original caller 0x5359ce..0x5359dc;
# helper 0x44fb30 clips count to source length and has range/length throw paths.
# ESI/EBP preserved; no SEH frame. Stack local zero store retained exactly.
.intel_syntax noprefix
.code32
.text
.global original_wide_prefix_construct
original_wide_prefix_construct:
.L536070:
 push   ebp
.L536071:
 {load} mov    ebp,esp
.L536073:
 push   ecx
.L536074:
 push   esi
.L536075:
 mov    esi,DWORD PTR [ebp+0x8]
.L536078:
 {load} xor    eax,eax
.L53607a:
 push   DWORD PTR [ebp+0x10]
.L53607d:
 mov    DWORD PTR [ebp-0x4],0x0
.L536084:
 push   eax
.L536085:
 push   ecx
.L536086:
 mov    DWORD PTR [esi+0x14],0x7
.L53608d:
 {load} mov    ecx,esi
.L53608f:
 mov    DWORD PTR [esi+0x10],0x0
.L536096:
 mov    WORD PTR [esi],ax
.L536099:
 call target_44fb30
.L53609e:
 {load} mov    eax,esi
.L5360a0:
 pop    esi
.L5360a1:
 {load} mov    esp,ebp
.L5360a3:
 pop    ebp
.L5360a4:
 ret    0xc
.equ target_44fb30,0x44fb30
