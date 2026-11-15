.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256:
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x427090, file offset 0x26490, complete span [0x427090,0x427094).
# Shared leaf: ECX points to object; EAX receives its DWORD at +0x14.
# Dispatcher use: internal manifold-array pointer; other vtables share this code.
.global original_dispatcher_manifold_array_pointer
original_dispatcher_manifold_array_pointer:
    mov eax, DWORD PTR [ecx+0x14]
    ret
.section .note.GNU-stack,"",@progbits
