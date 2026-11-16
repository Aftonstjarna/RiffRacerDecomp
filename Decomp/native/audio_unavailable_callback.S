.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x58e5b0,0x58e5c5); padding excluded.
# Shared fallback for dispatch slots 0,2..9 in table 0xbaf470.
# Cdecl-compatible: first stack argument is the decoder; extra arguments ignored.
.global original_audio_unavailable_callback
original_audio_unavailable_callback:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+0x8]
    mov DWORD PTR [eax+0x6ed8],0x18
    or eax,0xffffffff
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
