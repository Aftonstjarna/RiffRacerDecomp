.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x438530, end-exclusive 0x438539.
.global original_object_field78_present
original_object_field78_present:
    xor.s eax,eax
    cmp DWORD PTR [ecx+0x78],eax
    setne al
    ret
.section .note.GNU-stack,"",@progbits
