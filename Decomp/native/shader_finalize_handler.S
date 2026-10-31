# Reviewed original disassembly and Ghidra; see SHADERS.md.
# Original VA range 0x906264..0x90627f
.intel_syntax noprefix
.code32
.text
.global original_shader_finalize_handler
original_shader_finalize_handler:
.L906264:
 mov    edx,DWORD PTR [esp+0x8]
.L906268:
 lea    eax,[edx+0xc]
.L90626b:
 mov    ecx,DWORD PTR [edx-0x2c]
.L90626e:
 {load} xor    ecx,eax
.L906270:
 call target_8f8958
.L906275:
 mov    eax,0xb7d300
.L90627a:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
