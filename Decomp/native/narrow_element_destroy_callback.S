# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x426930,0x42695e); excludes subsequent INT3 padding.
.intel_syntax noprefix
.code32
.text
.equ DELETE_SLOT,0x92d4b0
.global original_narrow_element_destroy_callback
original_narrow_element_destroy_callback:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 cmp DWORD PTR [esi+0x14],0x10
 jb reset
 push DWORD PTR [esi]
 call DWORD PTR [DELETE_SLOT]
 add esp,4
reset:
 mov DWORD PTR [esi+0x14],0xf
 mov DWORD PTR [esi+0x10],0
 mov BYTE PTR [esi],0
 pop esi
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
