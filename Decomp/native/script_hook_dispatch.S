# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f5020, exclusive end 0x4f50f7.
.intel_syntax noprefix
.code32
.text
.global original_script_hook_dispatch
.equ stack_resize,0x4f4ef0
.equ cookie_check,0x8f8958
original_script_hook_dispatch:
 push ebp
 {load} mov ebp,esp
 sub esp,0x70
 mov eax,DWORD PTR ds:0xbaabc0
 {load} xor eax,ebp
 mov DWORD PTR [ebp-4],eax
 push esi
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [esi+0x44]
 test edi,edi
 je .Lexit
 cmp BYTE PTR [esi+0x39],0
 je .Lexit
 mov ecx,DWORD PTR [esi+8]
 sub ecx,DWORD PTR [esi+0x20]
 mov eax,DWORD PTR [ebp+8]
 mov DWORD PTR [ebp-0x6c],ecx
 mov ecx,DWORD PTR [esi+0x14]
 push ebx
 mov ebx,DWORD PTR [ecx+8]
 sub ebx,DWORD PTR [esi+0x20]
 mov DWORD PTR [ebp-0x70],ebx
 mov DWORD PTR [ebp-0x68],edx
 mov DWORD PTR [ebp-0x54],eax
 cmp edx,4
 jne .Lindex
 mov DWORD PTR [ebp-8],0
 jmp .Lspace
.Lindex:
 sub ecx,DWORD PTR [esi+0x28]
 mov eax,0x2aaaaaab
 imul ecx
 sar edx,2
 {load} mov eax,edx
 shr eax,0x1f
 {load} add eax,edx
 mov DWORD PTR [ebp-8],eax
.Lspace:
 mov eax,DWORD PTR [esi+0x1c]
 sub eax,DWORD PTR [esi+8]
 pop ebx
 cmp eax,0xa0
 jg .Linvoke
 mov edx,DWORD PTR [esi+0x2c]
 {load} mov ecx,esi
 cmp edx,0x14
 jl .Lsmall
 {load} add edx,edx
 jmp .Lresize
.Lsmall:
 add edx,0x14
.Lresize:
 call stack_resize
.Linvoke:
 mov eax,DWORD PTR [esi+0x14]
 mov ecx,DWORD PTR [esi+8]
 add ecx,0xa0
 mov DWORD PTR [eax+8],ecx
 lea eax,[ebp-0x68]
 push eax
 push esi
 mov BYTE PTR [esi+0x39],0
 call edi
 mov eax,DWORD PTR [esi+0x14]
 add esp,8
 mov ecx,DWORD PTR [esi+0x20]
 add ecx,DWORD PTR [ebp-0x70]
 mov BYTE PTR [esi+0x39],1
 mov DWORD PTR [eax+8],ecx
 mov eax,DWORD PTR [esi+0x20]
 add eax,DWORD PTR [ebp-0x6c]
 mov DWORD PTR [esi+8],eax
.Lexit:
 mov ecx,DWORD PTR [ebp-4]
 pop edi
 {load} xor ecx,ebp
 pop esi
 call cookie_check
 {load} mov esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
