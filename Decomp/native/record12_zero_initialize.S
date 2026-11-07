# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x437ed0,0x437ef3), excluding INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_record12_zero_initialize
original_record12_zero_initialize:
 test edx,edx
 je .done
.next:
 test ecx,ecx
 je .advance
 mov DWORD PTR [ecx],0
 mov DWORD PTR [ecx+4],0
 mov DWORD PTR [ecx+8],0
.advance:
 add ecx,12
 dec edx
 jne .next
.done:
 ret
.section .note.GNU-stack,"",@progbits
