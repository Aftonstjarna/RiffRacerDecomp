# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x8f9eee,0x8f9ef4). Complete import tail thunk.
# Actual caller 0x8f9c62 in CRT FP initializer 0x8f9c54.
# Preserves caller stack/return address and forwards cdecl arguments unchanged.
.intel_syntax noprefix
.code32
.text
.global original_crt_controlfp_s_import
.equ controlfp_s_iat,0x92d30c
original_crt_controlfp_s_import:
    jmp DWORD PTR [controlfp_s_iat]
.section .note.GNU-stack,"",@progbits
