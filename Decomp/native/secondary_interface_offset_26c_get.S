# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x44f0d0,0x44f0d7); instruction-contiguous extent, padding excluded.
# Secondary-interface accessor: returns this+0x26C in EAX. Leaf, no calls or embedded data.
# Derived from original instructions; earns reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x44f0d0..0x44f0d7
.intel_syntax noprefix
.code32
.text
.global original_secondary_interface_offset_26c_get
original_secondary_interface_offset_26c_get:
.L44f0d0:
 lea    eax,[ecx+0x26c]
.L44f0d6:
 ret
