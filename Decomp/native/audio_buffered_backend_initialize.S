.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e1f0,0x58e24b), 91 bytes. Sole return: 0x58e24a.
# Previous return 0x58e1ed; INT3 gaps excluded; next entry 0x58e250.
# cdecl(stream*): one stack argument, caller cleanup; EAX=0.
# Preserves ESI/EBP and the other nonvolatile registers; ECX/EAX/EDX/flags volatile.
# Table slot 0xbaf500; indirect callers at 0x4f883f and 0x55dcdb.
.equ cache_rebalance,0x58deb0
.global original_audio_buffered_backend_initialize
original_audio_buffered_backend_initialize:
    push ebp
    mov.s ebp,esp
    push esi
    mov esi,DWORD PTR [ebp+8]
    lea ecx,[esi+0x6d7c]
    # Reset active-buffer pointers, byte counts and checkpoint/base positions.
    mov DWORD PTR [ecx],0
    mov DWORD PTR [ecx+4],0
    mov DWORD PTR [ecx+8],0
    mov DWORD PTR [ecx+0xc],0
    mov DWORD PTR [ecx+0x10],0
    mov DWORD PTR [ecx+0x14],0
    # Cache configuration at +0x18..+0x24 is retained. Return value is ignored.
    call cache_rebalance
    or DWORD PTR [esi+0x6d50],8
    xor.s eax,eax
    mov DWORD PTR [esi+0x6d40],0
    mov DWORD PTR [esi+0x6d44],0
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
