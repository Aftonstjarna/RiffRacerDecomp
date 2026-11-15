# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x458100,0x458115); excludes surrounding INT3 padding.
# Register ABI: ECX=first four-byte slot, EDX=count; no stack arguments read.
.intel_syntax noprefix
.code32
.text
.global original_pointer_slot_range_zero_initialize
original_pointer_slot_range_zero_initialize:
    test edx,edx
    je .Ldone
.Lslot:
    test ecx,ecx
    je .Ladvance
    mov DWORD PTR [ecx],0
.Ladvance:
    add ecx,4
    dec edx
    jne .Lslot
.Ldone:
    ret
.section .note.GNU-stack,"",@progbits
