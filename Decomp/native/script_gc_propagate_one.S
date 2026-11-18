.intel_syntax noprefix
.code32
.text
.global original_script_gc_propagate_one
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f16f0..0x4f17c7.
.equ dispatch_table,0x4f17c8
.equ visit_table,0x4f1180
.equ visit_closure,0x4f13d0
.equ visit_thread,0x4f1540
.equ visit_proto,0x4f1320
original_script_gc_propagate_one:
 push esi
 mov esi,DWORD PTR [ecx+0x24]
 movzx eax,BYTE PTR [esi+0x4]
 or BYTE PTR [esi+0x5],0x4
 add eax,0xfffffffb
 cmp eax,0x4
 ja .Ldefault
 jmp DWORD PTR [eax*4+dispatch_table]
.Ltable:
 mov eax,DWORD PTR [esi+0x18]
 mov.s edx,esi
 mov DWORD PTR [ecx+0x24],eax
 call visit_table
 test eax,eax
 je .Ltable_size
 and BYTE PTR [esi+0x5],0xfb
.Ltable_size:
 mov cl,BYTE PTR [esi+0x7]
 mov eax,0x1
 shl eax,cl
 lea ecx,[eax+eax*4]
 mov eax,DWORD PTR [esi+0x1c]
 pop esi
 lea eax,[eax*8+0x20]
 lea eax,[eax+ecx*4]
 ret
.Lclosure:
 mov eax,DWORD PTR [esi+0x8]
 mov.s edx,esi
 mov DWORD PTR [ecx+0x24],eax
 call visit_closure
 cmp BYTE PTR [esi+0x6],0x0
 movzx eax,BYTE PTR [esi+0x7]
 je .Lclosure_small
 lea eax,[eax*8+0x14]
 pop esi
 ret
.Lclosure_small:
 lea eax,[eax*4+0x14]
 pop esi
 ret
.Lthread:
 mov eax,DWORD PTR [esi+0x5c]
 mov.s edx,esi
 mov DWORD PTR [ecx+0x24],eax
 mov eax,DWORD PTR [ecx+0x28]
 mov DWORD PTR [esi+0x5c],eax
 mov DWORD PTR [ecx+0x28],esi
 and BYTE PTR [esi+0x5],0xfb
 call visit_thread
 mov eax,DWORD PTR [esi+0x30]
 lea eax,[eax+eax*2]
 add eax,DWORD PTR [esi+0x2c]
 pop esi
 lea eax,[eax*8+0x68]
 ret
.Lproto:
 mov eax,DWORD PTR [esi+0x44]
 mov.s edx,esi
 mov DWORD PTR [ecx+0x24],eax
 call visit_proto
 mov eax,DWORD PTR [esi+0x38]
 lea ecx,[eax+eax*2]
 mov eax,DWORD PTR [esi+0x28]
 lea eax,[ecx+eax*2]
 add eax,DWORD PTR [esi+0x34]
 add eax,DWORD PTR [esi+0x30]
 add eax,DWORD PTR [esi+0x2c]
 add eax,DWORD PTR [esi+0x24]
 pop esi
 lea eax,[eax*4+0x4c]
 ret
.Ldefault:
 xor.s eax,eax
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
