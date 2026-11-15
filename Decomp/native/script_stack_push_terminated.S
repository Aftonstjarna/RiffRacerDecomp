# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4efab0,0x4efb0f), both returns included; INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_stack_push_terminated
.equ INTERN_STRING,0x4f5e40
.equ RESIZE_STACK,0x4f4ef0
original_script_stack_push_terminated:
 push ebx
 push esi
 mov.s esi,ecx
 mov.s ecx,edx
 push edi
 mov edi,DWORD PTR [esi+8]
 lea ebx,[ecx+1]
 {disp8} lea ecx,[ecx+0]
scan:
 mov al,BYTE PTR [ecx]
 inc ecx
 test al,al
 jne scan
 sub.s ecx,ebx
 push ecx
 mov.s ecx,esi
 call INTERN_STRING
 mov DWORD PTR [edi],eax
 add esp,4
 mov DWORD PTR [edi+4],4
 mov eax,DWORD PTR [esi+0x1c]
 sub eax,DWORD PTR [esi+8]
 cmp eax,8
 jg advance
 mov edx,DWORD PTR [esi+0x2c]
 mov.s ecx,esi
 cmp edx,1
 jl grow_one
 add.s edx,edx
 call RESIZE_STACK
 add DWORD PTR [esi+8],8
 pop edi
 pop esi
 pop ebx
 ret
grow_one:
 inc edx
 call RESIZE_STACK
advance:
 add DWORD PTR [esi+8],8
 pop edi
 pop esi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
