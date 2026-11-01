# Reviewed against /tmp/cloud-request-review/exception.asm and Ghidra
# exports/00901778.txt; supported original SHA256 in original.sha256.
# MSVC EH entry: registration pointer at ESP+8; reconstruct frame base +0xc,
# XOR saved cookie at registration-0x10, call security check 8f8958.
# EAX=external FuncInfo b799dc; tail-jump to __CxxFrameHandler3 at 8f8968.
# FuncInfo magic 19930522, one unwind entry at b79a00: (-1,901770).
# No try blocks/IP map. Metadata is inspected, not registered or copied.
# Body ends 901793 before INT3 padding. Runtime handler remains external.
# Original VA range 0x901778..0x901793
.intel_syntax noprefix
.code32
.text
.global original_decode_request_handler
original_decode_request_handler:
.L901778:
 mov    edx,DWORD PTR [esp+0x8]
.L90177c:
 lea    eax,[edx+0xc]
.L90177f:
 mov    ecx,DWORD PTR [edx-0x10]
.L901782:
 {load} xor    ecx,eax
.L901784:
 call target_8f8958
.L901789:
 mov    eax,0xb799dc
.L90178e:
 jmp target_8f8968
.equ target_8f8958,0x8f8958
.equ target_8f8968,0x8f8968
