# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x490e50,0x490e5e); both returns retained; INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_nested_primary_record_count
original_nested_primary_record_count:
 mov eax,DWORD PTR [ecx+0x20]
 test eax,eax
 je .Labsent
 mov eax,DWORD PTR [eax+0x8]
 ret
.Labsent:
 xor.s eax,eax
 ret
.section .note.GNU-stack,"",@progbits
