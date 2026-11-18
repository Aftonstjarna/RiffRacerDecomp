# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f17e0.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_propagate_all
.equ dispatch_table,0x4f18e4
.equ visit_table,0x4f1180
.equ visit_closure,0x4f13d0
.equ visit_thread,0x4f1540
.equ visit_proto,0x4f1320
original_script_gc_propagate_all:
 push ebx
 push edi
 mov.s edi,ecx
 xor.s ebx,ebx
 cmp DWORD PTR [edi+0x24],ebx
 je .Ldone
 push esi
.Lloop:
 mov esi,DWORD PTR [edi+0x24]
 movzx eax,BYTE PTR [esi+4]
 or BYTE PTR [esi+5],4
 add eax,0xfffffffb
 cmp eax,4
 ja .Ldefault
 jmp DWORD PTR [eax*4+dispatch_table]
.Ltable:
 mov eax,DWORD PTR [esi+0x18]
 mov.s edx,esi
 mov.s ecx,edi
 mov DWORD PTR [edi+0x24],eax
 call visit_table
 test eax,eax
 je .Ltable_size
 and BYTE PTR [esi+5],0xfb
.Ltable_size:
 mov cl,BYTE PTR [esi+7]
 mov eax,1
 shl eax,cl
 lea ecx,[eax+eax*4]
 mov eax,DWORD PTR [esi+0x1c]
 lea eax,[eax*8+0x20]
 lea eax,[eax+ecx*4]
 jmp .Ladd
.Lclosure:
 mov eax,DWORD PTR [esi+8]
 mov.s edx,esi
 mov.s ecx,edi
 mov DWORD PTR [edi+0x24],eax
 call visit_closure
 cmp BYTE PTR [esi+6],0
 movzx eax,BYTE PTR [esi+7]
 je .Lclosure_other
 lea eax,[eax*8+0x14]
 jmp .Ladd
.Lclosure_other:
 lea eax,[eax*4+0x14]
 jmp .Ladd
.Lthread:
 mov eax,DWORD PTR [esi+0x5c]
 mov.s edx,esi
 mov DWORD PTR [edi+0x24],eax
 mov.s ecx,edi
 mov eax,DWORD PTR [edi+0x28]
 mov DWORD PTR [esi+0x5c],eax
 mov DWORD PTR [edi+0x28],esi
 and BYTE PTR [esi+5],0xfb
 call visit_thread
 mov eax,DWORD PTR [esi+0x30]
 lea eax,[eax+eax*2]
 add eax,DWORD PTR [esi+0x2c]
 lea eax,[eax*8+0x68]
 jmp .Ladd
.Lproto:
 mov eax,DWORD PTR [esi+0x44]
 mov.s edx,esi
 mov.s ecx,edi
 mov DWORD PTR [edi+0x24],eax
 call visit_proto
 mov eax,DWORD PTR [esi+0x38]
 lea ecx,[eax+eax*2]
 mov eax,DWORD PTR [esi+0x28]
 lea eax,[ecx+eax*2]
 add eax,DWORD PTR [esi+0x34]
 add eax,DWORD PTR [esi+0x30]
 add eax,DWORD PTR [esi+0x2c]
 add eax,DWORD PTR [esi+0x24]
 lea eax,[eax*4+0x4c]
 jmp .Ladd
.Ldefault:
 xor.s eax,eax
.Ladd:
 add.s ebx,eax
 cmp DWORD PTR [edi+0x24],0
 jne .Lloop
 pop esi
.Ldone:
 pop edi
 mov.s eax,ebx
 pop ebx
 ret
