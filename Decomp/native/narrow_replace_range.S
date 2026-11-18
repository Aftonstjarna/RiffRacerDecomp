# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x440ea0.
.intel_syntax noprefix
.code32
.text
.global original_narrow_replace_range
.equ helper_441040,0x441040
.equ helper_416730,0x416730
.equ helper_8f8d66,0x8f8d66
.equ helper_416700,0x416700
original_narrow_replace_range:
 push ebp
 mov.s ebp,esp
 sub esp,0x8
 push ebx
 mov ebx,DWORD PTR [ebp+0x10]
 push esi
 mov.s esi,ecx
 test ebx,ebx
 je .L440efe
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,0x10
 jb .L440ebd
 mov eax,DWORD PTR [esi]
 jmp .L440ebf
.L440ebd:
 mov.s eax,esi
.L440ebf:
 cmp.s ebx,eax
 jb .L440efe
 cmp ecx,0x10
 jb .L440ecc
 mov edx,DWORD PTR [esi]
 jmp .L440ece
.L440ecc:
 mov.s edx,esi
.L440ece:
 mov eax,DWORD PTR [esi+0x10]
 add.s eax,edx
 cmp.s eax,ebx
 jbe .L440efe
 cmp ecx,0x10
 jb .L440ee0
 mov eax,DWORD PTR [esi]
 jmp .L440ee2
.L440ee0:
 mov.s eax,esi
.L440ee2:
 push DWORD PTR [ebp+0x14]
 sub.s ebx,eax
 mov.s ecx,esi
 push ebx
 push esi
 push DWORD PTR [ebp+0xc]
 push DWORD PTR [ebp+0x8]
 call helper_441040
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 0x10
.L440efe:
 mov edx,DWORD PTR [esi+0x10]
 mov ecx,DWORD PTR [ebp+0x8]
 cmp.s edx,ecx
 jae .L440f13
 push 0x99995c
 call DWORD PTR 0x92d16c
.L440f13:
 mov.s eax,edx
 sub.s eax,ecx
 mov ecx,DWORD PTR [ebp+0x14]
 push edi
 mov edi,DWORD PTR [ebp+0xc]
 cmp.s eax,edi
 mov DWORD PTR [ebp-0x4],eax
 cmovb edi,eax
 or eax,0xffffffff
 sub.s edx,edi
 sub.s eax,ecx
 cmp.s eax,edx
 ja .L440f3c
 push 0x99994c
 call DWORD PTR 0x92d168
.L440f3c:
 mov eax,DWORD PTR [ebp-0x4]
 sub.s eax,edi
 mov DWORD PTR [ebp-0x4],eax
 cmp.s ecx,edi
 jae .L440f8f
 mov edx,DWORD PTR [esi+0x14]
 cmp edx,0x10
 jb .L440f5a
 mov ebx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],ebx
 mov ebx,DWORD PTR [ebp+0x10]
 jmp .L440f5d
.L440f5a:
 mov DWORD PTR [ebp+0xc],esi
.L440f5d:
 cmp edx,0x10
 jb .L440f69
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],edx
 jmp .L440f6c
.L440f69:
 mov DWORD PTR [ebp+0x10],esi
.L440f6c:
 test eax,eax
 je .L440f8f
 push eax
 mov eax,DWORD PTR [ebp+0xc]
 add eax,DWORD PTR [ebp+0x8]
 add.s eax,edi
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add eax,DWORD PTR [ebp+0x8]
 add.s eax,ecx
 push eax
 call DWORD PTR 0x92d4a4
 mov ecx,DWORD PTR [ebp+0x14]
 add esp,0xc
.L440f8f:
 test ecx,ecx
 jne .L440f9b
 test edi,edi
 je .L441027
.L440f9b:
 sub.s ecx,edi
 add ecx,DWORD PTR [esi+0x10]
 push 0x0
 mov DWORD PTR [ebp-0x8],ecx
 push ecx
 mov.s ecx,esi
 call helper_416730
 test al,al
 je .L441027
 mov ecx,DWORD PTR [ebp+0x14]
 cmp.s edi,ecx
 jae .L440fff
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L440fc7
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],edx
 jmp .L440fca
.L440fc7:
 mov DWORD PTR [ebp+0xc],esi
.L440fca:
 cmp eax,0x10
 jb .L440fd6
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],edx
 jmp .L440fd9
.L440fd6:
 mov DWORD PTR [ebp+0x10],esi
.L440fd9:
 mov eax,DWORD PTR [ebp-0x4]
 test eax,eax
 je .L440fff
 push eax
 mov eax,DWORD PTR [ebp+0xc]
 add eax,DWORD PTR [ebp+0x8]
 add.s eax,edi
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add eax,DWORD PTR [ebp+0x8]
 add.s eax,ecx
 push eax
 call DWORD PTR 0x92d4a4
 mov ecx,DWORD PTR [ebp+0x14]
 add esp,0xc
.L440fff:
 cmp DWORD PTR [esi+0x14],0x10
 jb .L441009
 mov eax,DWORD PTR [esi]
 jmp .L44100b
.L441009:
 mov.s eax,esi
.L44100b:
 test ecx,ecx
 je .L44101d
 add eax,DWORD PTR [ebp+0x8]
 push ecx
 push ebx
 push eax
 call helper_8f8d66
 add esp,0xc
.L44101d:
 push DWORD PTR [ebp-0x8]
 mov.s ecx,esi
 call helper_416700
.L441027:
 pop edi
 mov.s eax,esi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 0x10
.section .note.GNU-stack,"",@progbits
