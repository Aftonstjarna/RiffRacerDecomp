.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x439220, complete span [0x439220,0x439287).
.global original_four_record20_initialize
original_four_record20_initialize:
    mov    BYTE PTR [ecx+0x10],0x1
    mov.s  eax,ecx
    mov    DWORD PTR [ecx+0xc],0x0
    mov    DWORD PTR [ecx+0x4],0x0
    mov    DWORD PTR [ecx+0x8],0x0
    mov    BYTE PTR [ecx+0x24],0x1
    mov    DWORD PTR [ecx+0x20],0x0
    mov    DWORD PTR [ecx+0x18],0x0
    mov    DWORD PTR [ecx+0x1c],0x0
    mov    BYTE PTR [ecx+0x38],0x1
    mov    DWORD PTR [ecx+0x34],0x0
    mov    DWORD PTR [ecx+0x2c],0x0
    mov    DWORD PTR [ecx+0x30],0x0
    mov    BYTE PTR [ecx+0x4c],0x1
    mov    DWORD PTR [ecx+0x48],0x0
    mov    DWORD PTR [ecx+0x40],0x0
    mov    DWORD PTR [ecx+0x44],0x0
    ret
