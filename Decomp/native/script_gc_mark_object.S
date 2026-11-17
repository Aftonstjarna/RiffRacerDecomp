# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0ef0,0x4f0fa2); external jump table at 0x4f0fa4.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_mark_object
.equ jump_table,0x4f0fa4
original_script_gc_mark_object:
 push esi
 mov.s esi,edx
 push edi
 mov.s edi,ecx
 movzx eax,BYTE PTR [esi+4]
 and BYTE PTR [esi+5],0xfc
 sub eax,4
 cmp eax,6
 ja .done
 {disp32} lea ebx,[ebx+0]
.dispatch:
 jmp DWORD PTR [eax*4+jump_table]
.list:
 mov edx,DWORD PTR [esi+8]
 or BYTE PTR [esi+5],4
 test edx,edx
 je .next
 test BYTE PTR [edx+5],3
 je .next
 mov.s ecx,edi
 call original_script_gc_mark_object
.next:
 mov esi,DWORD PTR [esi+0xc]
 test BYTE PTR [esi+5],3
 je .done
 and BYTE PTR [esi+5],0xfc
 movzx eax,BYTE PTR [esi+4]
 sub eax,4
 cmp eax,6
 jbe .dispatch
 pop edi
 pop esi
 ret
.indirect:
 mov eax,DWORD PTR [esi+8]
 cmp DWORD PTR [eax+4],4
 jl .check_inline
 mov edx,DWORD PTR [eax]
 test BYTE PTR [edx+5],3
 je .check_inline
 mov.s ecx,edi
 call original_script_gc_mark_object
.check_inline:
 lea eax,[esi+0xc]
 cmp DWORD PTR [esi+8],eax
 jne .done
 or BYTE PTR [esi+5],4
 pop edi
 pop esi
 ret
.link08:
 mov eax,DWORD PTR [edi+0x24]
 mov DWORD PTR [esi+8],eax
 mov DWORD PTR [edi+0x24],esi
 pop edi
 pop esi
 ret
.link18:
 mov eax,DWORD PTR [edi+0x24]
 mov DWORD PTR [esi+0x18],eax
 mov DWORD PTR [edi+0x24],esi
 pop edi
 pop esi
 ret
.link5c:
 mov eax,DWORD PTR [edi+0x24]
 mov DWORD PTR [esi+0x5c],eax
 mov DWORD PTR [edi+0x24],esi
 pop edi
 pop esi
 ret
.link44:
 mov eax,DWORD PTR [edi+0x24]
 mov DWORD PTR [esi+0x44],eax
 mov DWORD PTR [edi+0x24],esi
.done:
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
