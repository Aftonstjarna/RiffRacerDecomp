# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47d8e0,0x47d8e4); adjacent INT3 padding excluded.
# Compound vtable 0x9fb1d4 slot +0x28. ECX=this, result=x87 ST(0).
.intel_syntax noprefix
.code32
.text
.global original_compound_shape_margin
original_compound_shape_margin:
    fld DWORD PTR [ecx+0x48]
    ret
.section .note.GNU-stack,"",@progbits
