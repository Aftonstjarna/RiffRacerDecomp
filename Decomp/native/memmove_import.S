# Mechanically transcribed reference evidence, NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8d4e,0x8f8d54). Entire function: indirect tail jump.
# cdecl memmove(dst,src,byte_count): entry ESP+4,+8,+12; returns dst in EAX.
# Caller retains argument cleanup; CRT implementation and IAT binding external.
.intel_syntax noprefix
.code32
.text
.global original_memmove_import
original_memmove_import:
 jmp DWORD PTR [memmove_iat]
.equ memmove_iat,0x92d4a4
.section .note.GNU-stack,"",@progbits
