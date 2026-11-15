# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4c90,0x4f4cec); external jump table starts at end.
.intel_syntax noprefix
.code32
.text
.global original_script_error_object_set
.equ ERROR_TABLE,0x4f4cec
.equ INTERN_STRING,0x4f5e40
original_script_error_object_set:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 add edx,-2
 push edi
 mov.s edi,ecx
 cmp edx,3
 ja .Lfinish
 jmp DWORD PTR [edx*4+ERROR_TABLE]
.Lmemory:
 push 17
 mov edx,0x9fb5a0
.Lintern:
 call INTERN_STRING
 mov DWORD PTR [esi],eax
 add esp,4
 lea eax,[esi+8]
 mov DWORD PTR [esi+4],4
 mov DWORD PTR [edi+8],eax
 pop edi
 pop esi
 pop ebp
 ret
.Lhandling:
 push 23
 mov edx,0x9fd87c
 jmp .Lintern
.Lcopy:
 mov ecx,DWORD PTR [edi+8]
 mov eax,DWORD PTR [ecx-8]
 mov DWORD PTR [esi],eax
 mov eax,DWORD PTR [ecx-4]
 mov DWORD PTR [esi+4],eax
.Lfinish:
 lea eax,[esi+8]
 mov DWORD PTR [edi+8],eax
 pop edi
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
