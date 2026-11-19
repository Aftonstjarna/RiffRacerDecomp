# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x5991e0.
.intel_syntax noprefix
.code32
.text
.global original_archive_component_lookup
original_archive_component_lookup:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+0xc]
 mov edx,0xffff
 push ebx
 push esi
 push edi
 movzx eax,WORD PTR [eax+4]
 cmp.s ax,dx
 je .missing
 mov edi,DWORD PTR [ecx]
 mov ebx,DWORD PTR [ecx+0x18]
 {disp8} lea esp,[esp+0]
.loop:
 mov edx,DWORD PTR [ebp+8]
 movzx eax,ax
 movzx ecx,WORD PTR [edi+eax*8]
 lea esi,[edi+eax*8]
 movzx eax,WORD PTR [esi+6]
 and eax,0xc000
 shl eax,2
 or.s eax,ecx
 add.s eax,ebx
 {disp8} lea ecx,[ecx+0]
.compare:
 mov cl,BYTE PTR [eax]
 cmp cl,BYTE PTR [edx]
 jne .different
 test cl,cl
 je .equal
 mov cl,BYTE PTR [eax+1]
 cmp cl,BYTE PTR [edx+1]
 jne .different
 add eax,2
 add edx,2
 test cl,cl
 jne .compare
.equal:
 xor.s eax,eax
 jmp .tested
.different:
 sbb.s eax,eax
 or eax,1
.tested:
 test eax,eax
 je .found
 movzx eax,WORD PTR [esi+2]
 mov ecx,0xffff
 cmp.s ax,cx
 jne .loop
.missing:
 pop edi
 pop esi
 xor.s eax,eax
 pop ebx
 pop ebp
 ret 8
.found:
 pop edi
 mov.s eax,esi
 pop esi
 pop ebx
 pop ebp
 ret 8
.section .note.GNU-stack,"",@progbits
