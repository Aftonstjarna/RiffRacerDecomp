# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x5421b0..0x542222
.intel_syntax noprefix
.code32
.text
.global original_shader_base_ctor
original_shader_base_ctor:
.L5421b0:
 mov    DWORD PTR [ecx],0x9fe7e0
.L5421b6:
 {load} mov    eax,ecx
.L5421b8:
 mov    DWORD PTR [ecx+0xc],0x0
.L5421bf:
 mov    DWORD PTR [ecx+0x10],0x0
.L5421c6:
 mov    DWORD PTR [ecx+0x14],0x0
.L5421cd:
 mov    DWORD PTR [ecx+0x18],0x0
.L5421d4:
 mov    DWORD PTR [ecx+0x1c],0x0
.L5421db:
 mov    DWORD PTR [ecx+0x20],0x0
.L5421e2:
 mov    DWORD PTR [ecx+0x24],0x0
.L5421e9:
 mov    DWORD PTR [ecx+0x28],0x0
.L5421f0:
 mov    DWORD PTR [ecx+0x2c],0x0
.L5421f7:
 mov    DWORD PTR [ecx+0x30],0x0
.L5421fe:
 mov    DWORD PTR [ecx+0x34],0x0
.L542205:
 mov    DWORD PTR [ecx+0x38],0x0
.L54220c:
 mov    DWORD PTR [ecx+0x44],0x0
.L542213:
 mov    DWORD PTR [ecx+0x50],0x0
.L54221a:
 mov    DWORD PTR [ecx+0x54],0x0
.L542221:
 ret
