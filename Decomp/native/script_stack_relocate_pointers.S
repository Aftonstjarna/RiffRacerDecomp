# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4e60,0x4f4eee); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_stack_relocate_pointers
original_script_stack_relocate_pointers:
# ECX = script state, EDX = old stack base; state+0x20 already holds new base.
    push ebx
    push esi
    push edi
    mov.s edi,ecx
    mov.s ebx,edx
    mov esi,DWORD PTR [edi+0x8]
    mov eax,DWORD PTR [edi+0x20]
    sub.s esi,ebx
    sar esi,0x3
    lea eax,[eax+esi*8]
    mov DWORD PTR [edi+0x8],eax
    mov eax,DWORD PTR [edi+0x58]
    test eax,eax
    je frames_begin
    nop
open_upvalue_loop:
    mov edx,DWORD PTR [eax+0x8]
    mov ecx,DWORD PTR [edi+0x20]
    sub.s edx,ebx
    sar edx,0x3
    lea ecx,[ecx+edx*8]
    mov DWORD PTR [eax+0x8],ecx
    mov eax,DWORD PTR [eax]
    test eax,eax
    jne open_upvalue_loop
frames_begin:
# Walk inclusive 24-byte frame range after the linked open-upvalue chain.
    mov edx,DWORD PTR [edi+0x28]
    cmp edx,DWORD PTR [edi+0x14]
    ja relocate_base
    nop
frame_loop:
    mov ecx,DWORD PTR [edx+0x8]
    mov eax,DWORD PTR [edi+0x20]
    sub.s ecx,ebx
    sar ecx,0x3
    lea eax,[eax+ecx*8]
    mov ecx,DWORD PTR [edx]
    mov DWORD PTR [edx+0x8],eax
    sub.s ecx,ebx
    mov eax,DWORD PTR [edi+0x20]
    sar ecx,0x3
    lea eax,[eax+ecx*8]
    mov ecx,DWORD PTR [edx+0x4]
    mov DWORD PTR [edx],eax
    sub.s ecx,ebx
    mov eax,DWORD PTR [edi+0x20]
    sar ecx,0x3
    lea eax,[eax+ecx*8]
    mov DWORD PTR [edx+0x4],eax
    add edx,0x18
    cmp edx,DWORD PTR [edi+0x14]
    jbe frame_loop
relocate_base:
    mov ecx,DWORD PTR [edi+0xc]
    mov eax,DWORD PTR [edi+0x20]
    sub.s ecx,ebx
    sar ecx,0x3
    lea eax,[eax+ecx*8]
    mov DWORD PTR [edi+0xc],eax
    pop edi
    pop esi
    pop ebx
    ret
.section .note.GNU-stack,"",@progbits
