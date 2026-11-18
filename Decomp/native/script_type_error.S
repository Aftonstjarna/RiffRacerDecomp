# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4868c0,0x486942); includes both returns.
.intel_syntax noprefix
.code32
.text
.global original_script_type_error
.equ debug_name,0x486680
.equ raise_format,0x486ab0
original_script_type_error:
 push ebp
 mov.s ebp,esp
 push ecx
 mov eax,DWORD PTR [edx+4]
 push ebx
 push esi
 push edi
 mov ebx,DWORD PTR [eax*4+0x99a538]
 mov.s edi,ecx
 mov DWORD PTR [ebp-4],0
 mov ecx,DWORD PTR [edi+0x14]
 mov eax,DWORD PTR [ecx]
 mov esi,DWORD PTR [ecx+8]
 cmp.s eax,esi
 jae .generic
.scan:
 cmp.s edx,eax
 je .found
 add eax,8
 cmp.s eax,esi
 jb .scan
.generic:
 push ebx
 push DWORD PTR [ebp+8]
 push 0x9fb660
 push edi
 call raise_format
 add esp,0x10
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.found:
 sub edx,DWORD PTR [edi+0xc]
 lea eax,[ebp-4]
 sar edx,3
 push eax
 push edx
 mov.s edx,ecx
 mov.s ecx,edi
 call debug_name
 add esp,8
 test eax,eax
 je .generic
 push ebx
 push DWORD PTR [ebp-4]
 push eax
 push DWORD PTR [ebp+8]
 push 0x9fb690
 push edi
 call raise_format
 add esp,0x18
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
