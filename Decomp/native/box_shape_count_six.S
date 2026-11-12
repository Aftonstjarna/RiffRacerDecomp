.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x438d00, exclusive end 0x438d06.
# Shared constant-six box virtual leaf; no calls, branches or data accesses.
.global original_box_shape_count_six
original_box_shape_count_six:
    mov eax, 6
    ret
.section .note.GNU-stack,"",@progbits
