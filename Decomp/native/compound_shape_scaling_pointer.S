# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x47d8b0,0x47d8b4): compound vtable 0x9fb1d4 slot +0x18.
# thiscall: ECX=this; EAX=&this->localScaling (offset 0x4c).
# No loads, branches, calls or writes; adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_compound_shape_scaling_pointer
original_compound_shape_scaling_pointer:
 lea eax,[ecx+0x4c]
 ret
.section .note.GNU-stack,"",@progbits
