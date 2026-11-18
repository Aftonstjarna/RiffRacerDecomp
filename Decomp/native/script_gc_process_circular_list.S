# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f0fc0.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_process_circular_list
.equ mark_object,0x4f0ef0
original_script_gc_process_circular_list:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 push edi
 mov.s edi,ecx
 mov esi,[edi+0x30]
 test esi,esi
 je .Ldone
.Lloop:
 mov esi,[esi]
 movzx eax,BYTE PTR [esi+4]
 and BYTE PTR [esi+5],0xf8
 add eax,-4
 mov cl,[esi+5]
 cmp eax,6
 ja .Lnext
 jmp DWORD PTR [eax*4+0x4f1074]
.Ltype7:
 mov edx,[esi+8]
 or cl,4
 mov [esi+5],cl
 test edx,edx
 je .Lsecond
 test BYTE PTR [edx+5],3
 je .Lsecond
 mov.s ecx,edi
 call mark_object
.Lsecond:
 mov edx,[esi+0xc]
 test BYTE PTR [edx+5],3
 je .Lnext
 mov.s ecx,edi
 call mark_object
 jmp .Lnext
.Ltype10:
 mov eax,[esi+8]
 cmp DWORD PTR [eax+4],4
 jl .Lcheck_self
 mov edx,[eax]
 test BYTE PTR [edx+5],3
 je .Lcheck_self
 mov.s ecx,edi
 call mark_object
.Lcheck_self:
 lea eax,[esi+0xc]
 cmp [esi+8],eax
 jne .Lnext
 or BYTE PTR [esi+5],4
 jmp .Lnext
.Ltype6:
 mov eax,[edi+0x24]
 mov [esi+8],eax
 jmp .Llink
.Ltype5:
 mov eax,[edi+0x24]
 mov [esi+0x18],eax
 jmp .Llink
.Ltype8:
 mov eax,[edi+0x24]
 mov [esi+0x5c],eax
 jmp .Llink
.Ltype9:
 mov eax,[edi+0x24]
 mov [esi+0x44],eax
.Llink:
 mov [edi+0x24],esi
.Lnext:
 cmp esi,[edi+0x30]
 jne .Lloop
.Ldone:
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
