# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA [0x4f5680,0x4f5797).
.intel_syntax noprefix
.code32
.text
.global original_script_return_hook
.equ hook_dispatch,0x4f5020
.equ stack_grow,0x4f4ef0
.equ cookie_check,0x8f8958
original_script_return_hook:
.L4f5680:
 push ebp
.L4f5681:
 mov.s ebp,esp
.L4f5683:
 sub esp,0x70
.L4f5686:
 mov eax,DWORD PTR ds:0xbaabc0
.L4f568b:
 xor.s eax,ebp
.L4f568d:
 mov DWORD PTR [ebp-0x4],eax
.L4f5690:
 push ebx
.L4f5691:
 push esi
.L4f5692:
 mov.s esi,ecx
.L4f5694:
 mov.s ebx,edx
.L4f5696:
 push 0xffffffff
.L4f5698:
 mov edx,0x1
.L4f569d:
 sub ebx,DWORD PTR [esi+0x20]
.L4f56a0:
 mov DWORD PTR [ebp-0x6c],ebx
.L4f56a3:
 call hook_dispatch
.L4f56a8:
 mov eax,DWORD PTR [esi+0x14]
.L4f56ab:
 add esp,0x4
.L4f56ae:
 mov eax,DWORD PTR [eax+0x4]
.L4f56b1:
 mov eax,DWORD PTR [eax]
.L4f56b3:
 cmp BYTE PTR [eax+0x6],0x0
.L4f56b7:
 jne .L4f5782
.L4f56bd:
 test BYTE PTR [esi+0x38],0x2
.L4f56c1:
 je .L4f5782
.L4f56c7:
 push edi
.L4f56c8:
 jmp .L4f56d0
.L4f56ca:
 {disp32} lea ebx,[ebx+0x0]
.L4f56d0:
 mov edx,DWORD PTR [esi+0x14]
.L4f56d3:
 mov ecx,DWORD PTR [edx+0x14]
.L4f56d6:
 lea eax,[ecx-0x1]
.L4f56d9:
 mov DWORD PTR [edx+0x14],eax
.L4f56dc:
 test ecx,ecx
.L4f56de:
 je .L4f577e
.L4f56e4:
 mov edi,DWORD PTR [esi+0x44]
.L4f56e7:
 test edi,edi
.L4f56e9:
 je .L4f5774
.L4f56ef:
 cmp BYTE PTR [esi+0x39],0x0
.L4f56f3:
 je .L4f5774
.L4f56f5:
 mov eax,DWORD PTR [esi+0x14]
.L4f56f8:
 mov ebx,DWORD PTR [esi+0x8]
.L4f56fb:
 sub ebx,DWORD PTR [esi+0x20]
.L4f56fe:
 mov eax,DWORD PTR [eax+0x8]
.L4f5701:
 sub eax,DWORD PTR [esi+0x20]
.L4f5704:
 mov DWORD PTR [ebp-0x70],eax
.L4f5707:
 mov eax,DWORD PTR [esi+0x1c]
.L4f570a:
 sub eax,DWORD PTR [esi+0x8]
.L4f570d:
 mov DWORD PTR [ebp-0x68],0x4
.L4f5714:
 mov DWORD PTR [ebp-0x54],0xffffffff
.L4f571b:
 mov DWORD PTR [ebp-0x8],0x0
.L4f5722:
 cmp eax,0xa0
.L4f5727:
 jg .L4f573f
.L4f5729:
 mov edx,DWORD PTR [esi+0x2c]
.L4f572c:
 mov.s ecx,esi
.L4f572e:
 cmp edx,0x14
.L4f5731:
 jl .L4f5737
.L4f5733:
 add.s edx,edx
.L4f5735:
 jmp .L4f573a
.L4f5737:
 add edx,0x14
.L4f573a:
 call stack_grow
.L4f573f:
 mov eax,DWORD PTR [esi+0x14]
.L4f5742:
 mov ecx,DWORD PTR [esi+0x8]
.L4f5745:
 add ecx,0xa0
.L4f574b:
 mov DWORD PTR [eax+0x8],ecx
.L4f574e:
 lea eax,[ebp-0x68]
.L4f5751:
 push eax
.L4f5752:
 push esi
.L4f5753:
 mov BYTE PTR [esi+0x39],0x0
.L4f5757:
 call edi
.L4f5759:
 mov eax,DWORD PTR [esi+0x14]
.L4f575c:
 add esp,0x8
.L4f575f:
 mov ecx,DWORD PTR [esi+0x20]
.L4f5762:
 add ecx,DWORD PTR [ebp-0x70]
.L4f5765:
 mov BYTE PTR [esi+0x39],0x1
.L4f5769:
 mov DWORD PTR [eax+0x8],ecx
.L4f576c:
 mov eax,DWORD PTR [esi+0x20]
.L4f576f:
 add.s eax,ebx
.L4f5771:
 mov DWORD PTR [esi+0x8],eax
.L4f5774:
 test BYTE PTR [esi+0x38],0x2
.L4f5778:
 jne .L4f56d0
.L4f577e:
 mov ebx,DWORD PTR [ebp-0x6c]
.L4f5781:
 pop edi
.L4f5782:
 mov eax,DWORD PTR [esi+0x20]
.L4f5785:
 mov ecx,DWORD PTR [ebp-0x4]
.L4f5788:
 add.s eax,ebx
.L4f578a:
 pop esi
.L4f578b:
 xor.s ecx,ebp
.L4f578d:
 pop ebx
.L4f578e:
 call cookie_check
.L4f5793:
 mov.s esp,ebp
.L4f5795:
 pop ebp
.L4f5796:
 ret 
.section .note.GNU-stack,"",@progbits
