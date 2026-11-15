# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4869a0,0x486a22); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_error_add_location
.equ CURRENT_LINE,0x485cd0
.equ SOURCE_NAME,0x4eff60
.equ FORMAT_VARIADIC,0x4eff40
.equ CHECK_COOKIE,0x8f8958
original_script_error_add_location:
 push ebp
 mov.s ebp,esp
 sub esp,0x44
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 mov DWORD PTR [ebp-4],eax
 push ebx
 push esi
 mov.s esi,ecx
 mov.s ebx,edx
 push edi
 mov edx,DWORD PTR [esi+0x14]
 mov eax,DWORD PTR [edx+4]
 cmp DWORD PTR [eax+4],6
 jne finish
 mov eax,DWORD PTR [eax]
 cmp BYTE PTR [eax+6],0
 jne finish
 call CURRENT_LINE
 mov ecx,DWORD PTR [edx+4]
 mov.s edi,eax
 cmp DWORD PTR [ecx+4],6
 jne no_prototype
 mov ecx,DWORD PTR [ecx]
 cmp BYTE PTR [ecx+6],0
 jne no_prototype
 mov edx,DWORD PTR [ecx+0x10]
 jmp prototype_ready
no_prototype:
 xor.s edx,edx
prototype_ready:
 mov edx,DWORD PTR [edx+0x20]
 lea ecx,[ebp-0x40]
 push 0x3c
 add edx,0x10
 call SOURCE_NAME
 add esp,4
 lea eax,[ebp-0x40]
 push ebx
 push edi
 push eax
 push 0x9fb6d4
 push esi
 call FORMAT_VARIADIC
 add esp,0x14
finish:
 mov ecx,DWORD PTR [ebp-4]
 pop edi
 pop esi
 xor.s ecx,ebp
 pop ebx
 call CHECK_COOKIE
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
