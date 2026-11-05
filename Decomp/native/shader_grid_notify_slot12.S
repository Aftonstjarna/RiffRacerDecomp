# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x52f560..0x52f5a3 exclusive; subsequent INT3 bytes are padding.
# ECX=this; no stack arguments. Calls non-null entries through vtable +0x0c.
.intel_syntax noprefix
.code32
.text
.global original_shader_grid_notify_slot12
original_shader_grid_notify_slot12:
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 push esi
 push edi
 lea ebx,[ecx+0xe1c]
 mov DWORD PTR [ebp-4],0x118
.Lcolumn:
 mov.s esi,ebx
 mov edi,0x6
 jmp .Lrow
 {disp8} lea ecx,[ecx+0]
.Lrow:
 mov ecx,DWORD PTR [esi]
 test ecx,ecx
 je .Lnext
 mov eax,DWORD PTR [ecx]
 call DWORD PTR [eax+0x0c]
.Lnext:
 add esi,0x460
 dec edi
 jne .Lrow
 add ebx,4
 dec DWORD PTR [ebp-4]
 jne .Lcolumn
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
