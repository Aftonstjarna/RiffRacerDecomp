# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x5436c0..0x5436eb inclusive; 44 bytes. Padding excluded.
# ECX: writable 24-byte record; EAX returns ECX. No stack arguments.
.intel_syntax noprefix
.code32
.text
.global original_resource_record24_construct
original_resource_record24_construct:
    mov DWORD PTR [ecx], 0
    {load} mov eax, ecx
    mov DWORD PTR [ecx+4], 0
    mov DWORD PTR [ecx+8], 0
    mov DWORD PTR [ecx+12], 0xffffffff
    mov DWORD PTR [ecx+16], 0
    mov DWORD PTR [ecx+20], 0
    ret
.section .note.GNU-stack,"",@progbits
