# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f54a0.
.intel_syntax noprefix
.code32
.text
.global original_script_pre_call
.equ target_4f4ef0,0x4f4ef0
.equ target_4f4fd0,0x4f4fd0
.equ target_4f5020,0x4f5020
.equ target_4f5100,0x4f5100
.equ target_4f5380,0x4f5380
.equ target_4f57a0,0x4f57a0
original_script_pre_call:
 push ebp
 mov.s ebp,esp
 sub esp,0x8
 mov.s eax,edx
 cmp DWORD PTR [eax+0x4],0x6
 push ebx
 push esi
 push edi
 mov.s esi,ecx
 je .L4f54b8
 call target_4f5380
.L4f54b8:
 mov edx,DWORD PTR [eax]
 mov.s ebx,eax
 mov ecx,DWORD PTR [esi+0x14]
 sub ebx,DWORD PTR [esi+0x20]
 mov eax,DWORD PTR [esi+0x18]
 mov DWORD PTR [ebp-0x4],ebx
 mov DWORD PTR [ecx+0xc],eax
 cmp BYTE PTR [edx+0x6],0x0
 jne .L4f55ca
 mov ebx,DWORD PTR [edx+0x10]
 mov ecx,DWORD PTR [esi+0x1c]
 sub ecx,DWORD PTR [esi+0x8]
 movzx edx,BYTE PTR [ebx+0x4b]
 lea eax,[edx*8+0x0]
 cmp.s ecx,eax
 jg .L4f5502
 mov eax,DWORD PTR [esi+0x2c]
 mov.s ecx,esi
 cmp.s edx,eax
 jg .L4f54fb
 lea edx,[eax+eax*1]
 jmp .L4f54fd
.L4f54fb:
 add.s edx,eax
.L4f54fd:
 call target_4f4ef0
.L4f5502:
 mov edi,DWORD PTR [esi+0x20]
 add edi,DWORD PTR [ebp-0x4]
 cmp BYTE PTR [ebx+0x4a],0x0
 jne .L4f5525
 movzx eax,BYTE PTR [ebx+0x49]
 lea ecx,[edi+0x8]
 mov DWORD PTR [ebp-0x8],ecx
 lea eax,[ecx+eax*8]
 cmp DWORD PTR [esi+0x8],eax
 jbe .L4f5544
 mov DWORD PTR [esi+0x8],eax
 jmp .L4f5544
.L4f5525:
 mov eax,DWORD PTR [esi+0x8]
 mov.s edx,ebx
 sub.s eax,edi
 mov.s ecx,esi
 sar eax,0x3
 dec eax
 push eax
 call target_4f5100
 mov edi,DWORD PTR [esi+0x20]
 add esp,0x4
 add edi,DWORD PTR [ebp-0x4]
 mov DWORD PTR [ebp-0x8],eax
.L4f5544:
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,DWORD PTR [esi+0x24]
 jne .L4f5557
 mov.s ecx,esi
 call target_4f4fd0
 mov.s ecx,eax
 jmp .L4f555d
.L4f5557:
 add ecx,0x18
 mov DWORD PTR [esi+0x14],ecx
.L4f555d:
 mov edx,DWORD PTR [ebp-0x8]
 mov DWORD PTR [ecx+0x4],edi
 mov DWORD PTR [ecx],edx
 mov DWORD PTR [esi+0xc],edx
 movzx eax,BYTE PTR [ebx+0x4b]
 lea eax,[edx+eax*8]
 mov DWORD PTR [ecx+0x8],eax
 mov eax,DWORD PTR [ebx+0xc]
 mov DWORD PTR [esi+0x18],eax
 mov eax,DWORD PTR [ebp+0x8]
 mov DWORD PTR [ecx+0x14],0x0
 mov DWORD PTR [ecx+0x10],eax
 mov eax,DWORD PTR [esi+0x8]
 cmp eax,DWORD PTR [ecx+0x8]
 jae .L4f559f
 {disp8} lea ecx,[ecx+0x0]
.L4f5590:
 mov DWORD PTR [eax+0x4],0x0
 add eax,0x8
 cmp eax,DWORD PTR [ecx+0x8]
 jb .L4f5590
.L4f559f:
 test BYTE PTR [esi+0x38],0x1
 mov eax,DWORD PTR [ecx+0x8]
 mov DWORD PTR [esi+0x8],eax
 je .L4f55c1
 add DWORD PTR [esi+0x18],0x4
 xor.s edx,edx
 push 0xffffffff
 mov.s ecx,esi
 call target_4f5020
 add esp,0x4
 add DWORD PTR [esi+0x18],0xfffffffc
.L4f55c1:
 xor.s eax,eax
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 
.L4f55ca:
 mov eax,DWORD PTR [esi+0x1c]
 sub eax,DWORD PTR [esi+0x8]
 cmp eax,0xa0
 jg .L4f55ed
 mov edx,DWORD PTR [esi+0x2c]
 mov.s ecx,esi
 cmp edx,0x14
 jl .L4f55e5
 add.s edx,edx
 jmp .L4f55e8
.L4f55e5:
 add edx,0x14
.L4f55e8:
 call target_4f4ef0
.L4f55ed:
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,DWORD PTR [esi+0x24]
 jne .L4f5600
 mov.s ecx,esi
 call target_4f4fd0
 mov.s ecx,eax
 jmp .L4f5606
.L4f5600:
 add ecx,0x18
 mov DWORD PTR [esi+0x14],ecx
.L4f5606:
 mov eax,DWORD PTR [esi+0x20]
 add.s eax,ebx
 mov DWORD PTR [ecx+0x4],eax
 add eax,0x8
 mov DWORD PTR [ecx],eax
 mov DWORD PTR [esi+0xc],eax
 mov eax,DWORD PTR [esi+0x8]
 add eax,0xa0
 mov DWORD PTR [ecx+0x8],eax
 mov eax,DWORD PTR [ebp+0x8]
 mov DWORD PTR [ecx+0x10],eax
 test BYTE PTR [esi+0x38],0x1
 je .L4f563b
 push 0xffffffff
 xor.s edx,edx
 mov.s ecx,esi
 call target_4f5020
 add esp,0x4
.L4f563b:
 mov eax,DWORD PTR [esi+0x14]
 push esi
 mov eax,DWORD PTR [eax+0x4]
 mov eax,DWORD PTR [eax]
 mov eax,DWORD PTR [eax+0x10]
 call eax
 add esp,0x4
 test eax,eax
 jns .L4f565c
 mov eax,0x2
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 
.L4f565c:
 mov edx,DWORD PTR [esi+0x8]
 mov.s ecx,esi
 shl eax,0x3
 sub.s edx,eax
 call target_4f57a0
 pop edi
 pop esi
 mov eax,0x1
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 
.section .note.GNU-stack,"",@progbits
