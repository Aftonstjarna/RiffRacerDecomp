# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x48fc70, complete 28-byte function, padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_owner_slot58_acquire
original_owner_slot58_acquire:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ecx+0x58]
 mov DWORD PTR [eax],edx
 test edx,edx
 je handle_ready
 # Preserve original access order: output store precedes vbtable lookup.
 mov ecx,DWORD PTR [edx]
 mov ecx,DWORD PTR [ecx+4]
 inc DWORD PTR [ecx+edx+4]
handle_ready:
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
