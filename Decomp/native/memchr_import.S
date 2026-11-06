# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8d8a,0x8f8d90): complete single indirect tail jump.
# MSVCR120.dll memchr import. No local branches, stack changes or return.
# cdecl arguments: [esp+4] buffer, [esp+8] character, [esp+12] byte count.
# External CRT returns pointer/null in EAX; caller cleans the arguments.
.intel_syntax noprefix
.code32
.text
.equ memchr_iat,0x92d474
.global original_memchr_import
original_memchr_import:
 jmp DWORD PTR [memchr_iat]
.section .note.GNU-stack,"",@progbits
