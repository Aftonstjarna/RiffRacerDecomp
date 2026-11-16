.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x557510, exclusive end 0x557549.
# ECX outer compiler context; EDX signed target active-local count.
.global original_script_remove_active_locals
original_script_remove_active_locals:
mov eax,DWORD PTR [ecx+0x1c]
push edi
mov.s edi,edx
movzx ecx,BYTE PTR [eax+0x32]
cmp.s ecx,edi
jle done
push esi
nop
loop_local:
dec BYTE PTR [eax+0x32]
movzx ecx,BYTE PTR [eax+0x32]
movzx ecx,WORD PTR [eax+ecx*2+0xac]
lea esi,[ecx+ecx*2]
mov ecx,DWORD PTR [eax]
mov edx,DWORD PTR [ecx+0x18]
mov ecx,DWORD PTR [eax+0x18]
mov DWORD PTR [edx+esi*4+0x8],ecx
movzx ecx,BYTE PTR [eax+0x32]
cmp.s ecx,edi
jg loop_local
pop esi
done:
pop edi
ret
.section .note.GNU-stack,"",@progbits
