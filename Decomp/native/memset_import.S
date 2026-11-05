# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f8d7e..0x8f8d84 exclusive. One tail jump; no local return.
.intel_syntax noprefix
.code32
.text
.global original_memset_import
original_memset_import:
# cdecl memset(void *destination, int value, size_t count); caller cleans stack.
# Tail transfer preserves the caller's return address and arguments unchanged.
# Loader-resolved IAT slot; the external CRT supplies EAX and all side effects.
 jmp DWORD PTR [memset_iat]
.equ memset_iat,0x92d484
.section .note.GNU-stack,"",@progbits
