# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426880,0x4268b2); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.equ ALLOCATE_SLOT,0x92d4b4
.equ FAILURE_SLOT,0x92d164
.global original_u32_allocate
original_u32_allocate:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 xor.s ecx,ecx
 test eax,eax
 je done
 cmp eax,0x3fffffff
 ja failure
 shl eax,2
 push eax
 call DWORD PTR [ALLOCATE_SLOT]
 mov.s ecx,eax
 add esp,4
 test ecx,ecx
 jne done
failure:
 call DWORD PTR [FAILURE_SLOT]
done:
 mov.s eax,ecx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
