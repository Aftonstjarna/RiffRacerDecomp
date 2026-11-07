# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5301b0,0x5301f5); all three returns included.
.intel_syntax noprefix
.code32
.text
.global original_shader_slot_select
original_shader_slot_select:
 push ebp
 mov.s ebp,esp
 cmp BYTE PTR [ecx+0x2862],0
 je .Lsecond_override
 mov eax,DWORD PTR [ecx+0xe18]
 mov eax,DWORD PTR [eax+0x390]
 pop ebp
 ret 4
.Lsecond_override:
 cmp BYTE PTR [ecx+0x2863],0
 je .Lindexed
 mov eax,DWORD PTR [ecx+0xe18]
 mov eax,DWORD PTR [eax+0x394]
 pop ebp
 ret 4
.Lindexed:
 mov ecx,DWORD PTR [ecx+0xe18]
 mov eax,DWORD PTR [ebp+8]
 mov eax,DWORD PTR [ecx+eax*4]
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
