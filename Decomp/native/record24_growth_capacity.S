# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x543310..0x543359 (exclusive), both return paths included.
# ECX=vector triple; stack argument=required count; EAX=result; RET 4.
# Reads begin at +0 and allocation end at +8; no stores, calls or globals.
# ESI/EBP preserved. EAX/ECX/EDX/flags clobbered.
.intel_syntax noprefix
.code32
.text
.global original_record24_growth_capacity
original_record24_growth_capacity:
 push ebp
 {load} mov ebp,esp
 mov edx,DWORD PTR [ecx+8]
 mov eax,0x2aaaaaab
 sub edx,DWORD PTR [ecx]
 imul edx
 push esi
 sar edx,2
 mov eax,0x0aaaaaaa
 {load} mov esi,edx
 shr esi,31
 {load} add esi,edx
 {load} mov ecx,esi
 shr ecx,1
 {load} sub eax,ecx
 {load} cmp eax,esi
 jae .Lgrow
 {load} xor esi,esi
 cmp esi,DWORD PTR [ebp+8]
 cmovb esi,DWORD PTR [ebp+8]
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 4
.Lgrow:
 {load} add esi,ecx
 cmp esi,DWORD PTR [ebp+8]
 cmovb esi,DWORD PTR [ebp+8]
 {load} mov eax,esi
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
