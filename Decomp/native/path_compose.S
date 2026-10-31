# Provenance: supported Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump and private Ghidra export 00536220 (42 bytes).
# Save-device exists/create/open/delete callers supply ECX=result, EDX=prefix,
# [entry ESP+4]=mutable suffix. Prepend prefix into suffix, then move-construct
# result via 0044f6f0 (heap ownership transfer or inline WCHAR copy).
# Ghidra misses the stack argument: preserve two unused argument slots passed
# to prepend and its ret 16; this wrapper returns result in EAX with plain ret.
# ESI is preserved. No local SEH registration, embedded data or cleanup handler;
# exceptions from prepend/move construction propagate to the caller.
.intel_syntax noprefix
.code32
.text
.global original_path_compose
original_path_compose:
.L536220:
 push   ebp
.L536221:
 {load} mov    ebp,esp
.L536223:
 push   ecx
.L536224:
 push   esi
.L536225:
 sub    esp,0x8
.L536228:
 mov    DWORD PTR [ebp-0x4],0x0
.L53622f:
 {load} mov    esi,ecx
.L536231:
 push   edx
.L536232:
 push   ecx
.L536233:
 mov    ecx,DWORD PTR [ebp+0x8]
.L536236:
 call wide_prepend
.L53623b:
 push   eax
.L53623c:
 {load} mov    ecx,esi
.L53623e:
 call wide_move_construct
.L536243:
 {load} mov    eax,esi
.L536245:
 pop    esi
.L536246:
 {load} mov    esp,ebp
.L536248:
 pop    ebp
.L536249:
 ret
.equ wide_move_construct,0x44f6f0
.equ wide_prepend,0x536250
