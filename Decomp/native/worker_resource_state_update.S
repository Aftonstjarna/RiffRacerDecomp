# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x59efd0.
.intel_syntax noprefix
.code32
.text
.global original_worker_resource_state_update
.equ state_one,0x5c1790
.equ state_two,0x5c1d70
original_worker_resource_state_update:
 push ebx
 mov.s ebx,ecx
 push esi
 push edi
 xor.s edi,edi
 mov eax,[ebx+8]
 sub eax,[ebx+4]
 sar eax,2
 test.s eax,eax
 je .Lend
 jmp .Lloop
 {disp32} lea ebx,[ebx+0]
.Lloop:
 mov esi,[ebx+4]
 mov esi,[esi+edi*4]
 mov eax,[esi+0x64]
 dec eax
 je .Lstate1
 dec eax
 jne .Lnext
 mov eax,[esi+8]
 lea ecx,[esi+8]
 push 0
 call DWORD PTR [eax+0x20]
 cmp eax,2
 jne .Ltest1
 mov eax,[esi+8]
 lea ecx,[esi+8]
 call DWORD PTR [eax+0x38]
 mov ecx,[esi+0xc0]
 mov [esi+0xc4],ecx
 mov BYTE PTR [esi+0xd0],1
 mov [esi+0xd4],eax
 mov DWORD PTR [esi+0x64],0
 jmp .Lnext
.Ltest1:
 cmp eax,1
 jne .Lnext
 mov.s ecx,esi
 call state_two
 jmp .Lnext
.Lstate1:
 mov eax,[esi+8]
 lea ecx,[esi+8]
 call DWORD PTR [eax+8]
 cmp eax,1
 je .Lnext
 cmp eax,3
 je .Lspecial
 mov eax,[esi+8]
 lea ecx,[esi+8]
 call DWORD PTR [eax+0x38]
 mov ecx,[esi+0xc0]
 mov [esi+0xc4],ecx
 mov BYTE PTR [esi+0xd0],1
 mov [esi+0xd4],eax
 mov DWORD PTR [esi+0x64],0
 jmp .Lnext
.Lspecial:
 mov.s ecx,esi
 call state_one
 mov DWORD PTR [esi+0x64],2
.Lnext:
 mov eax,[ebx+8]
 inc edi
 sub eax,[ebx+4]
 sar eax,2
 cmp.s edi,eax
 jb .Lloop
.Lend:
 pop edi
 pop esi
 pop ebx
 ret
