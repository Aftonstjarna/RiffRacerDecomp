.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x8f9a16; complete six-byte import tail thunk.
.global original_crt_exception_filter_thunk
original_crt_exception_filter_thunk:
    jmp DWORD PTR ds:[0x92d2ac]
.section .note.GNU-stack,"",@progbits
