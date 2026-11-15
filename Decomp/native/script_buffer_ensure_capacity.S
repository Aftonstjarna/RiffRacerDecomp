# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f6140,0x4f61a0); all three returns, no padding or embedded data.
.intel_syntax noprefix
.code32
.text
.global original_script_buffer_ensure_capacity
.equ REALLOCATE,0x4f7d10
.equ RUNTIME_ERROR,0x486ab0
.equ TOO_LARGE_MESSAGE,0x9fdb34
original_script_buffer_ensure_capacity:
 push ebp
 mov.s ebp,esp
 and esp,-8
 push esi
 mov.s esi,edx
 push edi
 mov edi,DWORD PTR [ebp+8]
 mov edx,DWORD PTR [esi+8]
 cmp.s edi,edx
 jbe sufficient
 mov eax,0x20
 cmp.s edi,eax
 cmovb edi,eax
 lea eax,[edi+1]
 cmp eax,-3
 ja too_large
 push edi
 push edx
 mov edx,DWORD PTR [esi]
 call REALLOCATE
 add esp,8
 mov DWORD PTR [esi],eax
 mov DWORD PTR [esi+8],edi
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
too_large:
 push TOO_LARGE_MESSAGE
 push ecx
 call RUNTIME_ERROR
 add esp,8
 mov DWORD PTR [esi+8],edi
 xor.s eax,eax
 mov DWORD PTR [esi],eax
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
sufficient:
 mov eax,DWORD PTR [esi]
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
