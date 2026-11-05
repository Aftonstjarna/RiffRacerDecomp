# Provenance: mechanically transcribed from the supported original Game.exe.
# SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reference assembly only; not compiler-built matching high-level source.
# Boundaries/control flow reviewed against original objdump and targeted Ghidra
# ExportRecovery output. INT3 padding excluded; no embedded instruction data.
# No local SEH registration. Imported/runtime behavior is not reconstructed.
# ECX=string, [entry ESP+4]=new length, RET 4. Store length at +0x10;
# write UTF-16 NUL at buffer[length], selecting heap when capacity >=8.
# No allocation, range check, or capacity change. EBP preserved; EAX is not
# a uniform destination return (heap buffer on heap path, zero on inline path).
# Original VA range 0x44fab0..0x44fad5
.intel_syntax noprefix
.code32
.text
.global original_wide_set_length
original_wide_set_length:
.L44fab0:
 push   ebp
.L44fab1:
 {load} mov    ebp,esp
.L44fab3:
 cmp    DWORD PTR [ecx+0x14],0x8
.L44fab7:
 mov    edx,DWORD PTR [ebp+0x8]
.L44faba:
 mov    DWORD PTR [ecx+0x10],edx
.L44fabd:
 jb .L44facb
.L44fabf:
 mov    eax,DWORD PTR [ecx]
.L44fac1:
 {load} xor    ecx,ecx
.L44fac3:
 mov    WORD PTR [eax+edx*2],cx
.L44fac7:
 pop    ebp
.L44fac8:
 ret    0x4
.L44facb:
 {load} xor    eax,eax
.L44facd:
 mov    WORD PTR [ecx+edx*2],ax
.L44fad1:
 pop    ebp
.L44fad2:
 ret    0x4
.section .note.GNU-stack,"",@progbits
