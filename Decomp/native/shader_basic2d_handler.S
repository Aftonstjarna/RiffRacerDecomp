# Reviewed original instructions and Ghidra; see SHADERS.md.
# Original VA range 0x905468..0x905483
.intel_syntax noprefix
.code32
.text
.global original_shader_basic2d_handler
original_shader_basic2d_handler:
.L905468:
 mov    edx,DWORD PTR [esp+0x8]
.L90546c:
 lea    eax,[edx+0xc]
.L90546f:
 mov    ecx,DWORD PTR [edx-0x10]
.L905472:
 {load} xor    ecx,eax
.L905474:
 call target_8f8958
.L905479:
 mov    eax,0xb7d1e0
.L90547e:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
