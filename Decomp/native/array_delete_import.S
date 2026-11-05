# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f8d54,0x8f8d5a). Adjacent import thunks excluded.
# MSVC x86 cdecl operator delete[](void*): stack argument and return address
# pass unchanged to MSVCR120.dll!??_V@YAXPAX@Z through its loader-bound IAT.
.intel_syntax noprefix
.code32
.text
.global original_array_delete_import
original_array_delete_import:
 jmp DWORD PTR [array_delete_iat]
.equ array_delete_iat,0x92d4a0
.section .note.GNU-stack,"",@progbits
