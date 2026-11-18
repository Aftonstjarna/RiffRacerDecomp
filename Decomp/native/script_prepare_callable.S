# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f5380.
.intel_syntax noprefix
.code32
.text
.global original_script_prepare_callable
.equ lookup,0x4f5d00
.equ type_error,0x4868c0
.equ realloc_stack,0x4f7d10
.equ size_error,0x4f7cf0
.equ fix_stack,0x4f4e60
.equ error_literal,0x9fd838
original_script_prepare_callable:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push ebx
 push esi
 push edi
 push 0x10
 mov.s edi,edx
 mov.s esi,ecx
 call lookup
 mov.s ebx,eax
 add esp,4
 mov.s eax,edi
 sub eax,DWORD PTR [esi+0x20]
 mov DWORD PTR [ebp-0xc],eax
 cmp DWORD PTR [ebx+4],6
 je .Lshift
 push error_literal
 mov.s edx,edi
 mov.s ecx,esi
 call type_error
 add esp,4
.Lshift:
 mov edx,DWORD PTR [esi+8]
 cmp.s edx,edi
 jbe .Lspace
 nop
.Lloop:
 mov eax,DWORD PTR [edx-8]
 mov DWORD PTR [edx],eax
 mov eax,DWORD PTR [edx-4]
 mov DWORD PTR [edx+4],eax
 add edx,-8
 cmp.s edx,edi
 ja .Lloop
.Lspace:
 mov eax,DWORD PTR [esi+0x1c]
 sub eax,DWORD PTR [esi+8]
 cmp eax,8
 jg .Lfinish
 mov ecx,DWORD PTR [esi+0x2c]
 mov edx,DWORD PTR [esi+0x20]
 cmp ecx,1
 jl .Lsmall
 lea eax,[ecx+ecx]
 mov DWORD PTR [ebp-8],edx
 lea edi,[eax+6]
 mov DWORD PTR [ebp-4],eax
 lea eax,[edi+1]
 cmp eax,0x1fffffff
 ja .Llarge_error
 lea eax,[edi*8]
 push eax
 lea eax,[ecx*8]
 mov.s ecx,esi
 push eax
 call realloc_stack
 mov ecx,DWORD PTR [ebp-4]
 add esp,8
 mov edx,DWORD PTR [ebp-8]
 jmp .Lupdate
.Llarge_error:
 mov.s ecx,esi
 call size_error
 mov ecx,DWORD PTR [ebp-4]
 mov edx,DWORD PTR [ebp-8]
 jmp .Lupdate
.Lsmall:
 lea eax,[ecx+1]
 mov DWORD PTR [ebp-4],edx
 lea edi,[eax+6]
 mov DWORD PTR [ebp-8],eax
 lea eax,[edi+1]
 cmp eax,0x1fffffff
 ja .Lsmall_error
 lea eax,[edi*8]
 push eax
 lea eax,[ecx*8]
 mov.s ecx,esi
 push eax
 call realloc_stack
 add esp,8
 jmp .Lsmall_done
.Lsmall_error:
 mov.s ecx,esi
 call size_error
.Lsmall_done:
 mov ecx,DWORD PTR [ebp-8]
 mov edx,DWORD PTR [ebp-4]
.Lupdate:
 mov DWORD PTR [esi+0x20],eax
 lea eax,[eax+ecx*8]
 mov.s ecx,esi
 mov DWORD PTR [esi+0x2c],edi
 mov DWORD PTR [esi+0x1c],eax
 call fix_stack
.Lfinish:
 add DWORD PTR [esi+8],8
 mov eax,DWORD PTR [esi+0x20]
 add eax,DWORD PTR [ebp-0xc]
 mov ecx,DWORD PTR [ebx]
 pop edi
 pop esi
 mov DWORD PTR [eax],ecx
 mov ecx,DWORD PTR [ebx+4]
 mov DWORD PTR [eax+4],ecx
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
