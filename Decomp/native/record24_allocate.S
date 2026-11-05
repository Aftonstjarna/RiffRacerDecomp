# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x543360,0x543395). INT3 padding is excluded.
# One stack count, callee pops 4; ECX is scratch; EAX returns storage.
.intel_syntax noprefix
.code32
.text
.global original_record24_allocate
original_record24_allocate:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 {load} xor ecx,ecx
 test eax,eax
 je .Lreturn
 cmp eax,0x0aaaaaaa
 ja .Lbad_alloc
 lea eax,[eax+eax*2]
 shl eax,3
 push eax
 call DWORD PTR [0x92d4b4]
 {load} mov ecx,eax
 add esp,4
 test ecx,ecx
 jne .Lreturn
.Lbad_alloc:
 call DWORD PTR [0x92d164]
.Lreturn:
 {load} mov eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
