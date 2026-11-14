# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x438540,0x438553); adjacent INT3 padding excluded.
# ECX=allocation pointer. Null skips both counter and callback.
# Non-null callback is cdecl(pointer); volatile registers/flags are unspecified.
.intel_syntax noprefix
.code32
.text
.equ FREE_COUNT,0xbfcc18
.equ FREE_CALLBACK,0x99a0bc
.global original_physics_allocation_release
original_physics_allocation_release:
 test ecx,ecx
 je done
 inc DWORD PTR [FREE_COUNT]
 push ecx
 call DWORD PTR [FREE_CALLBACK]
 pop ecx
done:
 ret
.section .note.GNU-stack,"",@progbits
