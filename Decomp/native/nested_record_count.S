.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x490e60,0x490e6e); both returns included, INT3 padding excluded.
# ECX: valid owner; owner+0x44: nullable nested record descriptor.
# EAX: descriptor+0x14 field, or zero. No writes, calls or stack arguments.
.global original_nested_record_count
original_nested_record_count:
 mov eax,DWORD PTR [ecx+0x44]
 test eax,eax
 je .Lempty
 mov eax,DWORD PTR [eax+0x14]
 ret
.Lempty:
 xor.s eax,eax
 ret
.section .note.GNU-stack,"",@progbits
