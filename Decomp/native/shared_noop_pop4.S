.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4141c0,0x4141c3). Following INT3 padding excluded.
# Shared no-op leaf: returns to caller and discards one four-byte argument.
# No register, flag, object, pointed-to data, import or global accesses.
.global original_shared_noop_pop4
original_shared_noop_pop4:
    ret 4
.section .note.GNU-stack,"",@progbits
