# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original VA [0x4f4800,0x4f4864); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_lua_closure_allocate
.equ REALLOCATE,0x4f7d10
original_script_lua_closure_allocate:
 push ebp
 mov.s ebp,esp
 push ebx
 mov.s ebx,edx
 xor.s edx,edx
 push esi
 push edi
 mov.s esi,ecx
 lea eax,[ebx*4+0x14]
 push eax
 push 0
 call REALLOCATE
 mov edx,DWORD PTR [esi+0x10]
 mov.s edi,eax
 mov eax,DWORD PTR [ebp+8]
 add esp,8
 mov ecx,DWORD PTR [edx+0x1c]
 mov DWORD PTR [edi],ecx
 mov cl,BYTE PTR [edx+0x14]
 mov DWORD PTR [edx+0x1c],edi
 and cl,3
 mov BYTE PTR [edi+5],cl
 mov BYTE PTR [edi+4],6
 mov BYTE PTR [edi+6],0
 mov DWORD PTR [edi+0xc],eax
 mov BYTE PTR [edi+7],bl
 test ebx,ebx
 je .Lfinish
 lea eax,[ebx+5]
 lea eax,[edi+eax*4]
 nop
.Lclear:
 mov DWORD PTR [eax-4],0
 lea eax,[eax-4]
 dec ebx
 jne .Lclear
.Lfinish:
 mov.s eax,edi
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
