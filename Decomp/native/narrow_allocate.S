# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4169f0,0x416a1d); INT3 padding excluded.
# Stack byte count, callee pops 4; ECX input unused; EAX result.
.intel_syntax noprefix
.code32
.text
.global original_narrow_allocate
original_narrow_allocate:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 xor.s ecx,ecx
 test eax,eax
 je .Lreturn
 # Preserve the original unsigned comparison, including its impossible JA.
 cmp eax,0xffffffff
 ja .Lbad_alloc
 push eax
 call DWORD PTR [0x92d4b4]
 mov.s ecx,eax
 add esp,4
 test ecx,ecx
 jne .Lreturn
.Lbad_alloc:
 call DWORD PTR [0x92d164]
.Lreturn:
 mov.s eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
