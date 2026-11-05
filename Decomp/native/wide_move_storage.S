# Provenance: mechanically transcribed from the supported original Game.exe.
# SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reference assembly only; not compiler-built matching high-level source.
# Boundaries/control flow reviewed against original objdump and targeted Ghidra
# ExportRecovery output. INT3 padding excluded; no embedded instruction data.
# No local SEH registration. Imported/runtime behavior is not reconstructed.
# ECX=already-empty destination, [entry ESP+4]=mutable source, RET 4.
# Transfer inline contents via memmove or take heap ownership, then transfer
# length/capacity and reset source to empty inline storage. No destination
# disposal or self-move guard. EBP/ESI/EDI preserved; EAX ends as zero.
# The heap-path destination-null check only skips the pointer store: later
# metadata stores still dereference destination, so this is not null-safe.
# Called by 0x536030 after destination release/reset: this is a move, not a copy.
# Original VA range 0x44f890..0x44f8e9
.intel_syntax noprefix
.code32
.text
.global original_wide_move_storage
original_wide_move_storage:
.L44f890:
 push   ebp
.L44f891:
 {load} mov    ebp,esp
.L44f893:
 push   esi
.L44f894:
 mov    esi,DWORD PTR [ebp+0x8]
.L44f897:
 push   edi
.L44f898:
 {load} mov    edi,ecx
.L44f89a:
 cmp    DWORD PTR [esi+0x14],0x8
.L44f89e:
 jae .L44f8b6
.L44f8a0:
 mov    eax,DWORD PTR [esi+0x10]
.L44f8a3:
 inc    eax
.L44f8a4:
 je .L44f8c4
.L44f8a6:
 {load} add    eax,eax
.L44f8a8:
 push   eax
.L44f8a9:
 push   esi
.L44f8aa:
 push   edi
.L44f8ab:
 call   DWORD PTR [wide_memmove_iat]
.L44f8b1:
 add    esp,0xc
.L44f8b4:
 jmp .L44f8c4
.L44f8b6:
 test   edi,edi
.L44f8b8:
 je .L44f8be
.L44f8ba:
 mov    eax,DWORD PTR [esi]
.L44f8bc:
 mov    DWORD PTR [edi],eax
.L44f8be:
 mov    DWORD PTR [esi],0x0
.L44f8c4:
 mov    eax,DWORD PTR [esi+0x10]
.L44f8c7:
 mov    DWORD PTR [edi+0x10],eax
.L44f8ca:
 mov    eax,DWORD PTR [esi+0x14]
.L44f8cd:
 mov    DWORD PTR [edi+0x14],eax
.L44f8d0:
 {load} xor    eax,eax
.L44f8d2:
 mov    DWORD PTR [esi+0x14],0x7
.L44f8d9:
 mov    DWORD PTR [esi+0x10],0x0
.L44f8e0:
 pop    edi
.L44f8e1:
 mov    WORD PTR [esi],ax
.L44f8e4:
 pop    esi
.L44f8e5:
 pop    ebp
.L44f8e6:
 ret    0x4
.equ wide_memmove_iat,0x92d4a4
.section .note.GNU-stack,"",@progbits
