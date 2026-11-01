# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump instructions and private Ghidra Strings export
# /tmp/cloud-string-batch/exports; Ghidra inclusive body end 0x00535ebd.
# VA [0x535e30,0x535ebe); no inline data; excludes following INT3 padding.
# ECX=secondary save-device interface; one narrow-name pointer on stack, ret 4.
# Calls 0x44f3e0 (codepage 1252 conversion), assigns UTF-16 string at this+0x24,
# frees heap temporary when capacity >=8, then refreshes path via this-8.
# Preserves EBX/ESI/EBP, aligns stack to 8 and checks cookie at 0x8f8958.
# No local SEH registration; conversion/assignment/path-refresh exceptions propagate.
# External helpers 0x44f3e0, 0x44f890, 0x535ec0 and delete IAT remain dependencies.
.intel_syntax noprefix
.code32
.text
.global original_save_device_set_name
original_save_device_set_name:
.L535e30:
 push   ebp
.L535e31:
 {load} mov    ebp,esp
.L535e33:
 and    esp,0xfffffff8
.L535e36:
 sub    esp,0x20
.L535e39:
 mov    eax,[0xbaabc0]
.L535e3e:
 {load} xor    eax,esp
.L535e40:
 mov    DWORD PTR [esp+0x1c],eax
.L535e44:
 mov    edx,DWORD PTR [ebp+0x8]
.L535e47:
 push   ebx
.L535e48:
 {load} mov    ebx,ecx
.L535e4a:
 lea    ecx,[esp+0x8]
.L535e4e:
 push   esi
.L535e4f:
 call target_44f3e0
.L535e54:
 lea    esi,[ebx+0x24]
.L535e57:
 mov    DWORD PTR [esp+0x8],eax
.L535e5b:
 {load} cmp    esi,eax
.L535e5d:
 je .L535e8f
.L535e5f:
 cmp    DWORD PTR [esi+0x14],0x8
.L535e63:
 jb .L535e74
.L535e65:
 push   DWORD PTR [esi]
.L535e67:
 call   DWORD PTR [0x92d4b0]
.L535e6d:
 mov    eax,DWORD PTR [esp+0xc]
.L535e71:
 add    esp,0x4
.L535e74:
 {load} xor    ecx,ecx
.L535e76:
 mov    DWORD PTR [esi+0x14],0x7
.L535e7d:
 mov    DWORD PTR [esi+0x10],0x0
.L535e84:
 mov    WORD PTR [esi],cx
.L535e87:
 {load} mov    ecx,esi
.L535e89:
 push   eax
.L535e8a:
 call target_44f890
.L535e8f:
 cmp    DWORD PTR [esp+0x20],0x8
.L535e94:
 jb .L535ea3
.L535e96:
 push   DWORD PTR [esp+0xc]
.L535e9a:
 call   DWORD PTR [0x92d4b0]
.L535ea0:
 add    esp,0x4
.L535ea3:
 lea    ecx,[ebx-0x8]
.L535ea6:
 call target_535ec0
.L535eab:
 mov    ecx,DWORD PTR [esp+0x24]
.L535eaf:
 pop    esi
.L535eb0:
 pop    ebx
.L535eb1:
 {load} xor    ecx,esp
.L535eb3:
 call target_8f8958
.L535eb8:
 {load} mov    esp,ebp
.L535eba:
 pop    ebp
.L535ebb:
 ret    0x4
.equ target_44f3e0,0x44f3e0
.equ target_44f890,0x44f890
.equ target_535ec0,0x535ec0
.equ target_8f8958,0x8f8958
