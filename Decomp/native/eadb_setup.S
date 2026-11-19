.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5249a0.
.equ alloc_entry, 0x8f87c8
.equ memset_thunk, 0x8f8d7e
.equ sqrt_bridge, 0x426d60
.equ half_constant, 0xa06508
.global original_eadb_setup
original_eadb_setup:
 push esi
 push edi
 {load} mov edi, ecx
 mov esi, [edi+0x3c]
 mov [edi+0x44], esi
 cmp DWORD PTR [esi], 0x42444145
 je valid_magic
invalid_header:
 mov DWORD PTR [edi+0x44], 0
fail:
 pop edi
 {load} xor al, al
 pop esi
 ret
valid_magic:
 cmp DWORD PTR [esi+4], 0x26
 jne invalid_header
 cmp DWORD PTR [esi+0xc], 0
 je fail
 cmp DWORD PTR [esi+0x18], 0
 je fail
 cmp DWORD PTR [esi+0x14], 0
 je fail
 mov eax, [esi+0x44]
 {load} add eax, esi
 mov [edi+0x48], eax
 cmp DWORD PTR [esi+0x10], 0
 je no_optional
 mov eax, [esi+0x48]
 {load} add eax, esi
 jmp set_optional
no_optional:
 {load} xor eax, eax
set_optional:
 mov [edi+0x4c], eax
 mov eax, [esi+0x54]
 {load} add eax, esi
 mov [edi+0x50], eax
 mov eax, [esi+0x4c]
 {load} add eax, esi
 mov [edi+0x54], eax
 mov eax, [esi+0x58]
 {load} add eax, esi
 mov [edi+0x58], eax
 mov eax, [esi+0x5c]
 {load} add eax, esi
 mov [edi+0x5c], eax
 mov eax, [esi+0x60]
 {load} add eax, esi
 mov [edi+0x60], eax
 mov esi, [esi+0x14]
 shr esi, 3
 inc esi
 push esi
 call alloc_entry
 push esi
 push 0xff
 push eax
 mov [edi+0x64], eax
 call memset_thunk
 mov ecx, [edi+0x44]
 add esp, 0xc
 movss xmm0, DWORD PTR [half_constant]
 mov eax, [ecx+0x7c]
 mov [edi+0x68], eax
 movss xmm2, DWORD PTR [ecx+0x64]
 movss xmm3, DWORD PTR [ecx+0x68]
 movss xmm1, DWORD PTR [ecx+0x6c]
 mulss xmm3, xmm0
 mulss xmm2, xmm0
 mulss xmm3, xmm3
 mulss xmm2, xmm2
 mulss xmm1, xmm0
 addss xmm3, xmm2
 mulss xmm1, xmm1
 addss xmm3, xmm1
 movss DWORD PTR [esp], xmm3
 call sqrt_bridge
 add esp, 4
 mov al, 1
 fstp DWORD PTR [edi+0x6c]
 pop edi
 pop esi
 ret
