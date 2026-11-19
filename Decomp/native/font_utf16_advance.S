.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x456450.
.global original_font_utf16_advance
original_font_utf16_advance:
 push ebp
 {load} mov ebp,esp
 push ecx
 push ebx
 mov ebx,[ebp+8]
 push esi
 {load} mov esi,ecx
 test ebx,ebx
 jne .Lnonnull
 fldz
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
.Lnonnull:
 mov eax,[esi+0x68]
 {load} xor ecx,ecx
 test eax,eax
 xorps xmm1,xmm1
 movzx eax,word ptr [ebx]
 push edi
 lea edi,[ebp+0xb]
 movss [ebp-4],xmm1
 cmove edi,ecx
 test ax,ax
 je .Lreturn
.Lloop:
 movzx ecx,ax
 test edi,edi
 je .Lcharacter
 mov byte ptr [edi],0
.Lcharacter:
 cmp ecx,0xd
 je .Lspecial
 cmp ecx,0xa
 je .Lspecial
 mov eax,[esi+0x28]
 mov edx,[esi+0x2c]
 {load} cmp eax,edx
 je .Lalternate
.Lprimary:
 cmp word ptr [eax],cx
 je .Ladd
 add eax,0x2c
 {load} cmp eax,edx
 jne .Lprimary
.Lalternate:
 test edi,edi
 je .Lfallback
 mov eax,[esi+0x68]
 test eax,eax
 je .Lfallback
 mov edx,[esi+0x68]
 mov eax,[eax+0x28]
 mov edx,[edx+0x2c]
 {load} cmp eax,edx
 je .Lfallback
 {disp32} lea esp,[esp+0]
.Lscan_alternate:
 cmp word ptr [eax],cx
 je .Lfound_alternate
 add eax,0x2c
 {load} cmp eax,edx
 jne .Lscan_alternate
.Lfallback:
 mov eax,[esi+0x34]
 jmp .Ladd
.Lfound_alternate:
 mov byte ptr [edi],1
 jmp .Ladd
.Lspecial:
 lea eax,[esi+0x38]
.Ladd:
 addss xmm1,dword ptr [eax+0x24]
 movzx eax,word ptr [ebx+2]
 add ebx,2
 test ax,ax
 jne .Lloop
 movss [ebp-4],xmm1
.Lreturn:
 fld dword ptr [ebp-4]
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
