.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58dad0,0x58db12), 66 bytes.
# All returns: 0x58daf1,0x58dafa,0x58db11. INT3 padding excluded.
# cdecl(stream*, uint32_t* accumulator), caller pops 8 bytes; EAX status.
# Preserves EBP/EBX/ESI/EDI; EAX/ECX/EDX/flags volatile.
# Backend +8 is cdecl(stream*, byte-destination, count). Count=1.
# Uses byte [ebp+11] in its own incoming first-argument slot as temporary.
# Table +0x10 at 0xbaf4a0,0xbaf4d0,0xbaf500,0xbaf530 points here.
.global original_audio_stream_shift_byte
original_audio_stream_shift_byte:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+8]
    lea edx,[ebp+0xb]
    push 1
    push edx
    push eax
    mov ecx,DWORD PTR [eax+0x6d3c]
    mov eax,DWORD PTR [ecx+8]
    call eax
    add esp,0xc
    cmp eax,-10
    jne .Lcheck_count
    pop ebp
    ret
.Lcheck_count:
    cmp eax,1
    je .Lappend
    xor.s eax,eax
    pop ebp
    ret
.Lappend:
    mov edx,DWORD PTR [ebp+0xc]
    movzx eax,BYTE PTR [ebp+0xb]
    mov ecx,DWORD PTR [edx]
    shl ecx,8
    or.s ecx,eax
    mov eax,1
    mov DWORD PTR [edx],ecx
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
