# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4223a0,0x4223a9), excludes adjacent INT3 padding.
# ECX = writable four-byte slot; EAX = same address. Plain RET, no stack args.
# No branches, calls, global data, imports, allocation or ownership release.
# Used as element constructor by array_construct_with_cleanup (0x8f94bf).
.intel_syntax noprefix
.code32
.text
.global original_pointer_slot_zero_construct
original_pointer_slot_zero_construct:
 mov DWORD PTR [ecx],0
 mov.s eax,ecx
 ret
.section .note.GNU-stack,"",@progbits
