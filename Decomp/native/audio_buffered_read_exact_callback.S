.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e2a0,0x58e2c8); sole return 0x58e2c7.
# INT3 gap 0x58e2c8..0x58e2cf excluded; next entry 0x58e2d0.
# cdecl(stream,destination,count), EAX result; buffer reader uses ECX/EDX/stack.
.equ buffer_read_range,0x58e0d0
.global original_audio_buffered_read_exact_callback
original_audio_buffered_read_exact_callback:
 push ebp
 mov.s ebp,esp
 mov ecx,DWORD PTR [ebp+8]
 push DWORD PTR [ebp+0x10]
 mov edx,DWORD PTR [ebp+0xc]
 lea ecx,[ecx+0x6d7c]
 call buffer_read_range
 add esp,4
 test eax,eax
 js .Lreturn
 cmp eax,DWORD PTR [ebp+0x10]
 je .Lreturn
 or eax,-1
.Lreturn:
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
