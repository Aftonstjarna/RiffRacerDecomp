# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f6040,0x4f609b); both returns; padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_stream_peek
original_script_stream_peek:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 mov.s esi,ecx
 cmp DWORD PTR [esi],0
 jne .Lbuffered
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
 movzx eax,BYTE PTR [edx]
 inc edx
 mov DWORD PTR [esi+4],edx
 cmp eax,-1
 je .Leof
 lea eax,[ecx+1]
 mov DWORD PTR [esi],eax
 lea eax,[edx-1]
 mov DWORD PTR [esi+4],eax
.Lbuffered:
 mov eax,DWORD PTR [esi+4]
 pop esi
 movzx eax,BYTE PTR [eax]
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
