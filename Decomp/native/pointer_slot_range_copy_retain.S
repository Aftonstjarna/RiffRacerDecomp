# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44be60,0x44be8c); adjacent INT3 padding excluded.
# ECX=source begin, EDX=source end, [entry ESP+4]=destination.
.intel_syntax noprefix
.code32
.text
.global original_pointer_slot_range_copy_retain
original_pointer_slot_range_copy_retain:
    push ebp
    mov.s ebp,esp
    mov eax,DWORD PTR [ebp+8]
    push esi
    mov.s esi,edx
    cmp.s ecx,esi
    je done
    {disp8} lea ecx,[ecx+0]
loop_slots:
    test eax,eax
    je next_slot
    mov edx,DWORD PTR [ecx]
    mov DWORD PTR [eax],edx
    test edx,edx
    je next_slot
    inc DWORD PTR [edx+4]
next_slot:
    add ecx,4
    add eax,4
    cmp.s ecx,esi
    jne loop_slots
done:
    pop esi
    pop ebp
    ret
.section .note.GNU-stack,"",@progbits
