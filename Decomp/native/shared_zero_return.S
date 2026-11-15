.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x004142f0,0x004142f3); surrounding INT3 padding excluded.
# Shared no-argument integer-zero leaf; CRT direct call and shape vtable reuse.
.global original_shared_zero_return
original_shared_zero_return:
    xor.s eax,eax
    ret
.section .note.GNU-stack,"",@progbits
