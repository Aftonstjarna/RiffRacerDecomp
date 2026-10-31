# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x542230..0x542335
.intel_syntax noprefix
.code32
.text
.global original_shader_common_parameters
original_shader_common_parameters:
.L542230:
 push   esi
.L542231:
 {load} mov    esi,ecx
.L542233:
 push   0x9fffac
.L542238:
 push   DWORD PTR [esi+0x10]
.L54223b:
 call target_542340
.L542240:
 push   0x9fffac
.L542245:
 push   DWORD PTR [esi+0x14]
.L542248:
 mov    DWORD PTR [esi+0x18],eax
.L54224b:
 call target_542340
.L542250:
 push   0x9fff80
.L542255:
 push   DWORD PTR [esi+0x14]
.L542258:
 mov    DWORD PTR [esi+0x1c],eax
.L54225b:
 call target_542340
.L542260:
 push   0x9fff74
.L542265:
 push   DWORD PTR [esi+0x14]
.L542268:
 mov    DWORD PTR [esi+0x20],eax
.L54226b:
 call target_542340
.L542270:
 push   0x9fff98
.L542275:
 push   DWORD PTR [esi+0x14]
.L542278:
 mov    DWORD PTR [esi+0x24],eax
.L54227b:
 call target_542340
.L542280:
 push   0x9fff8c
.L542285:
 push   DWORD PTR [esi+0x14]
.L542288:
 mov    DWORD PTR [esi+0x28],eax
.L54228b:
 call target_542340
.L542290:
 push   0xa00008
.L542295:
 push   DWORD PTR [esi+0x14]
.L542298:
 mov    DWORD PTR [esi+0x30],eax
.L54229b:
 call target_542340
.L5422a0:
 push   0x9ffff8
.L5422a5:
 push   DWORD PTR [esi+0x14]
.L5422a8:
 mov    DWORD PTR [esi+0x34],eax
.L5422ab:
 call target_542340
.L5422b0:
 push   0xa00028
.L5422b5:
 push   DWORD PTR [esi+0x14]
.L5422b8:
 mov    DWORD PTR [esi+0x38],eax
.L5422bb:
 call target_542340
.L5422c0:
 push   0xa00018
.L5422c5:
 push   DWORD PTR [esi+0x14]
.L5422c8:
 mov    DWORD PTR [esi+0x3c],eax
.L5422cb:
 call target_542340
.L5422d0:
 push   0x9fffd0
.L5422d5:
 push   DWORD PTR [esi+0x14]
.L5422d8:
 mov    DWORD PTR [esi+0x40],eax
.L5422db:
 call target_542340
.L5422e0:
 push   0x9fffc0
.L5422e5:
 push   DWORD PTR [esi+0x10]
.L5422e8:
 mov    DWORD PTR [esi+0x44],eax
.L5422eb:
 call target_542340
.L5422f0:
 push   0x9fffec
.L5422f5:
 push   DWORD PTR [esi+0x14]
.L5422f8:
 mov    DWORD PTR [esi+0x2c],eax
.L5422fb:
 call target_542340
.L542300:
 push   0x9fffe0
.L542305:
 push   DWORD PTR [esi+0x14]
.L542308:
 mov    DWORD PTR [esi+0x48],eax
.L54230b:
 call target_542340
.L542310:
 push   0xa00048
.L542315:
 push   DWORD PTR [esi+0x10]
.L542318:
 mov    DWORD PTR [esi+0x4c],eax
.L54231b:
 call target_542340
.L542320:
 push   0xa00038
.L542325:
 push   DWORD PTR [esi+0x10]
.L542328:
 mov    DWORD PTR [esi+0x50],eax
.L54232b:
 call target_542340
.L542330:
 mov    DWORD PTR [esi+0x54],eax
.L542333:
 pop    esi
.L542334:
 ret
.equ target_542340,0x542340
