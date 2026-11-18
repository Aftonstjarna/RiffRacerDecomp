.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4909e0.
.equ clear_references,0x499710
.global original_worker_record_reset
original_worker_record_reset:
    push esi
    {load} mov esi,ecx
    mov eax,DWORD PTR [esi+0x1c]
    lea ecx,[esi+0x34]
    mov DWORD PTR [esi+0x20],eax
    mov eax,DWORD PTR [esi+0x28]
    mov DWORD PTR [esi+0x2c],eax
    call clear_references
    mov eax,DWORD PTR [esi+0x40]
    mov DWORD PTR [esi+0x44],eax
    mov eax,DWORD PTR [esi+0x4c]
    mov DWORD PTR [esi+0x50],eax
    mov eax,DWORD PTR [esi+0x58]
    mov DWORD PTR [esi+0x5c],eax
    mov eax,DWORD PTR [esi+0x64]
    mov DWORD PTR [esi+0x68],eax
    mov WORD PTR [esi+0x5f8],0
    mov DWORD PTR [esi+0x5f4],0
    mov BYTE PTR [esi+0x600],0x80
    mov DWORD PTR [esi+0x5f0],0x3f800000
    mov DWORD PTR [esi+0x28c],0
    mov DWORD PTR [esi+0x290],0
    mov DWORD PTR [esi+0x294],0
    mov DWORD PTR [esi+0x298],0
    mov BYTE PTR [esi+0x29c],0
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
