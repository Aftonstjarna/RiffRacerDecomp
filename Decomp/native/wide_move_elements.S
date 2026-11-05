# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44e140,0x44e15e); both returns included; INT3 padding excluded.
# ECX=destination, EDX=source, [entry ESP+4]=UTF-16 element count.
# Caller cleans count; nonzero path forwards doubled count to CRT memmove.
.intel_syntax noprefix
.code32
.text
.global original_wide_move_elements
original_wide_move_elements:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 test eax,eax
 jne .Lnonzero
 {load} mov eax,ecx
 pop ebp
 ret
.Lnonzero:
 {load} add eax,eax
 push eax
 push edx
 push ecx
 call DWORD PTR [0x92d4a4]
 add esp,12
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
