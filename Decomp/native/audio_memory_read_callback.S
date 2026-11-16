.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x55dd50,0x55dd82); single return; following INT3 padding excluded.
# cdecl (state*, destination, unsigned requested); EAX = bytes copied.
.global original_audio_memory_read_callback
.equ memcpy_import,0x8f8d66
original_audio_memory_read_callback:
    push ebp
    mov.s ebp,esp
    push esi
    mov esi,DWORD PTR [ebp+8]
    push edi
    mov edi,DWORD PTR [ebp+0x10]
    mov eax,DWORD PTR [esi+0x30]
    sub eax,DWORD PTR [esi+0x34]
    mov ecx,DWORD PTR [esi+0x2c]
    cmp.s edi,eax
    cmova edi,eax
    add ecx,DWORD PTR [esi+0x34]
    push edi
    push ecx
    push DWORD PTR [ebp+0xc]
    call memcpy_import
    add esp,0xc
    mov.s eax,edi
    add DWORD PTR [esi+0x34],edi
    pop edi
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
