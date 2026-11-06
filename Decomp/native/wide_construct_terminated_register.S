# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44f490,0x44f4e2). Padding and next SEH function excluded.
.intel_syntax noprefix
.code32
.text
.global original_wide_construct_terminated_register
.equ wide_assign_range,0x44f9b0
original_wide_construct_terminated_register:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 mov.s esi,edx
 mov DWORD PTR [ebp-4],0
 push edi
 mov.s edi,ecx
 lea ecx,[esi+2]
.Lscan:
 mov ax,WORD PTR [esi]
 add esi,2
 test ax,ax
 jne .Lscan
 sub.s esi,ecx
 mov DWORD PTR [edi+20],7
 sar esi,1
 xor.s ecx,ecx
 mov DWORD PTR [edi+16],0
 mov WORD PTR [edi],cx
 lea eax,[edx+esi*2]
 cmp.s edx,eax
 je .Ldone
 sub.s eax,edx
 mov.s ecx,edi
 sar eax,1
 push eax
 push edx
 call wide_assign_range
.Ldone:
 mov.s eax,edi
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
