.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x536320,0x536339); both returns included, INT3 padding excluded.
.global original_device_indexed_handle_select
original_device_indexed_handle_select:
    cmp BYTE PTR [ecx+3],0
    mov eax,DWORD PTR [ecx+0x44c]
    je .Lalternate
    mov eax,DWORD PTR [ecx+eax*4+4]
    ret
.Lalternate:
    mov eax,DWORD PTR [ecx+eax*4+0x420]
    ret
.section .note.GNU-stack,"",@progbits
