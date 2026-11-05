# Provenance: mechanically transcribed from the supported original Game.exe.
# SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reference assembly only; not compiler-built matching high-level source.
# Boundaries/control flow reviewed against original objdump and targeted Ghidra
# ExportRecovery output. INT3 padding excluded; no embedded instruction data.
# No local SEH registration. Imported/runtime behavior is not reconstructed.
# ECX=new destination, [entry ESP+4]=mutable source, EAX=destination, RET 4.
# Initialize empty destination. Source capacity <8 copies (length+1)*2 bytes
# including UTF-16 NUL using memmove; length+1 wrapping to zero skips the copy.
# Otherwise transfer the heap pointer and clear the source pointer. Transfer
# length/capacity, then reset source length=0, capacity=7 and first WCHAR=0.
# No destination disposal or self-move guard. EBP/ESI/EDI preserved.
# Original VA range 0x44f6f0..0x44f75a
.intel_syntax noprefix
.code32
.text
.global original_wide_move_construct
original_wide_move_construct:
.L44f6f0:
 push   ebp
.L44f6f1:
 {load} mov    ebp,esp
.L44f6f3:
 push   esi
.L44f6f4:
 mov    esi,DWORD PTR [ebp+0x8]
.L44f6f7:
 {load} xor    eax,eax
.L44f6f9:
 push   edi
.L44f6fa:
 {load} mov    edi,ecx
.L44f6fc:
 mov    DWORD PTR [edi+0x14],0x7
.L44f703:
 mov    DWORD PTR [edi+0x10],0x0
.L44f70a:
 mov    WORD PTR [edi],ax
.L44f70d:
 cmp    DWORD PTR [esi+0x14],0x8
.L44f711:
 jae .L44f729
.L44f713:
 mov    eax,DWORD PTR [esi+0x10]
.L44f716:
 inc    eax
.L44f717:
 je .L44f733
.L44f719:
 {load} add    eax,eax
.L44f71b:
 push   eax
.L44f71c:
 push   esi
.L44f71d:
 push   edi
.L44f71e:
 call   DWORD PTR [wide_memmove_iat]
.L44f724:
 add    esp,0xc
.L44f727:
 jmp .L44f733
.L44f729:
 mov    eax,DWORD PTR [esi]
.L44f72b:
 mov    DWORD PTR [edi],eax
.L44f72d:
 mov    DWORD PTR [esi],0x0
.L44f733:
 mov    eax,DWORD PTR [esi+0x10]
.L44f736:
 mov    DWORD PTR [edi+0x10],eax
.L44f739:
 mov    eax,DWORD PTR [esi+0x14]
.L44f73c:
 mov    DWORD PTR [edi+0x14],eax
.L44f73f:
 {load} xor    eax,eax
.L44f741:
 mov    DWORD PTR [esi+0x14],0x7
.L44f748:
 mov    DWORD PTR [esi+0x10],0x0
.L44f74f:
 mov    WORD PTR [esi],ax
.L44f752:
 {load} mov    eax,edi
.L44f754:
 pop    edi
.L44f755:
 pop    esi
.L44f756:
 pop    ebp
.L44f757:
 ret    0x4
.equ wide_memmove_iat,0x92d4a4
.section .note.GNU-stack,"",@progbits
