# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x485cd0,0x485d13); all three returns included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_frame_current_line
original_script_frame_current_line:
    push esi
    mov esi,DWORD PTR [edx+4]
    cmp DWORD PTR [esi+4],6
    jne unavailable
    mov eax,DWORD PTR [esi]
    cmp BYTE PTR [eax+6],0
    jne unavailable
    cmp edx,DWORD PTR [ecx+0x14]
    jne saved_pc_ready
    mov eax,DWORD PTR [ecx+0x18]
    mov DWORD PTR [edx+0xc],eax
saved_pc_ready:
    mov eax,DWORD PTR [esi]
    mov ecx,DWORD PTR [eax+0x10]
    mov eax,DWORD PTR [edx+0xc]
    sub eax,DWORD PTR [ecx+0xc]
    sar eax,2
    dec eax
    js unavailable
    mov ecx,DWORD PTR [ecx+0x14]
    test ecx,ecx
    je no_line_table
    mov eax,DWORD PTR [ecx+eax*4]
    pop esi
    ret
no_line_table:
    xor.s eax,eax
    pop esi
    ret
unavailable:
    or eax,0xffffffff
    pop esi
    ret
.section .note.GNU-stack,"",@progbits
