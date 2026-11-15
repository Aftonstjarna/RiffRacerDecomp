.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f5ff0,0x4f6032); both return paths included.
.global original_script_stream_refill
original_script_stream_refill:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 mov.s esi,ecx
 lea eax,[ebp-4]
 push eax
 push DWORD PTR [esi+0xc]
 mov eax,DWORD PTR [esi+8]
 push DWORD PTR [esi+0x10]
 call eax
 mov.s edx,eax
 add esp,0xc
 test edx,edx
 je .Leof
 mov ecx,DWORD PTR [ebp-4]
 test ecx,ecx
 je .Leof
 dec ecx
 mov DWORD PTR [esi+4],edx
 mov DWORD PTR [esi],ecx
 lea ecx,[edx+1]
 movzx eax,BYTE PTR [edx]
 mov DWORD PTR [esi+4],ecx
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.Leof:
 or eax,-1
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
