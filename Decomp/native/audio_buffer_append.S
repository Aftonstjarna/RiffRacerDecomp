.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58dfc0,0x58e0cc); returns at 0x58e0ba, 0x58e0c3, 0x58e0cb.
# ECX=buffer, EDX=source, stack=count; caller cleanup.
.equ memcpy_import,0x8f8d66
.equ malloc_iat,0x92d39c
.equ free_iat,0x92d3a4
.global original_audio_buffer_append
original_audio_buffer_append:
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 mov ebx,DWORD PTR [ebp+0x8]
 mov DWORD PTR [ebp-0x4],edx
 push edi
 mov.s edi,ecx
 test ebx,ebx
 jle .Lnonpositive_count
 push esi
.Lcopy_tail:
 mov eax,DWORD PTR [edi+0x4]
 test eax,eax
 je .Lcheck_remaining
 mov ecx,DWORD PTR [eax+0x4]
 mov esi,DWORD PTR [eax+0x8]
 cmp.s ecx,esi
 jge .Lcheck_remaining
 mov eax,DWORD PTR [eax]
 sub.s esi,ecx
 cmp.s esi,ebx
 cmovg esi,ebx
 add.s eax,ecx
 push esi
 push edx
 push eax
 call memcpy_import
 mov eax,DWORD PTR [edi+0x4]
 sub.s ebx,esi
 add esp,0xc
 mov DWORD PTR [ebp+0x8],ebx
 add DWORD PTR [eax+0x4],esi
 add DWORD PTR [edi+0x8],esi
 add DWORD PTR [ebp-0x4],esi
.Lcheck_remaining:
 test ebx,ebx
 jle .Lcopied_all
 mov esi,DWORD PTR [edi+0x24]
 test esi,esi
 je .Lallocate_node
 mov eax,DWORD PTR [esi+0xc]
 mov DWORD PTR [edi+0x24],eax
 mov DWORD PTR [esi+0xc],0x0
 mov DWORD PTR [esi+0x4],0x0
 dec DWORD PTR [edi+0x20]
 jmp .Lcheck_node
.Lallocate_node:
 mov ebx,DWORD PTR [edi+0x18]
 push 0x10
 call DWORD PTR [malloc_iat]
 mov.s esi,eax
 add esp,0x4
 test esi,esi
 je .Lrestore_remaining
 cmp DWORD PTR [ebp+0x8],ebx
 cmova ebx,DWORD PTR [ebp+0x8]
 push ebx
 mov DWORD PTR [esi+0x8],ebx
 call DWORD PTR [malloc_iat]
 add esp,0x4
 mov DWORD PTR [esi],eax
 test eax,eax
 jne .Linitialize_node
 push esi
 call DWORD PTR [free_iat]
 add esp,0x4
 xor.s esi,esi
 jmp .Lrestore_remaining
.Linitialize_node:
 mov DWORD PTR [esi+0x4],0x0
 mov DWORD PTR [esi+0xc],0x0
.Lrestore_remaining:
 mov ebx,DWORD PTR [ebp+0x8]
.Lcheck_node:
 test esi,esi
 je .Lallocation_failed
 mov eax,DWORD PTR [edi+0x4]
 test eax,eax
 je .Lfirst_node
 mov edx,DWORD PTR [ebp-0x4]
 mov DWORD PTR [eax+0xc],esi
 mov DWORD PTR [edi+0x4],esi
 jmp .Lcopy_tail
.Lfirst_node:
 cmp DWORD PTR [edi],0x0
 jne .Linstall_tail
 mov DWORD PTR [edi],esi
.Linstall_tail:
 mov edx,DWORD PTR [ebp-0x4]
 mov DWORD PTR [edi+0x4],esi
 jmp .Lcopy_tail
.Lallocation_failed:
 pop esi
 pop edi
 mov eax,0xfffffffe
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.Lcopied_all:
 pop esi
 pop edi
 xor.s eax,eax
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.Lnonpositive_count:
 pop edi
 xor.s eax,eax
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
