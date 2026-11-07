# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x43f250,0x43f26c); surrounding INT3 excluded.
# ECX=owner; stack argument=output slot; EAX=output slot; ret 4.
# Copy precedes conditional non-atomic increment through the dynamic offset table.
.intel_syntax noprefix
.code32
.text
.global original_owner_handle5c_acquire
original_owner_handle5c_acquire:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ecx+0x5c]
 mov DWORD PTR [eax],edx
 test edx,edx
 je L_done
 mov ecx,DWORD PTR [edx]
 mov ecx,DWORD PTR [ecx+4]
 inc DWORD PTR [ecx+edx+4]
L_done:
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
