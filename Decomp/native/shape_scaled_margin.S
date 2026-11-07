.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level source recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4391c0; complete span [0x4391c0,0x4391c7).
.global original_shape_scaled_margin
original_shape_scaled_margin:
    fld DWORD PTR [ecx+0x1c]
    fmul DWORD PTR [ecx+0xc]
    ret
.section .note.GNU-stack,"",@progbits
