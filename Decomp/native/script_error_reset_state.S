# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f4d00,0x4f4d78); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_error_reset_state
.equ CLOSE_UPVALUES,0x4f49b0
.equ SET_ERROR_OBJECT,0x4f4c90
.equ RESIZE_CALLINFO,0x4f4f50
original_script_error_reset_state:
 push ecx
 push esi
 push edi
 mov.s edi,ecx
 mov.s esi,edx
 mov edx,DWORD PTR [edi+0x28]
 mov DWORD PTR [edi+0x14],edx
 mov edx,DWORD PTR [edx]
 mov DWORD PTR [edi+0xc],edx
 call CLOSE_UPVALUES
 push DWORD PTR [edi+0xc]
 mov.s edx,esi
 mov.s ecx,edi
 call SET_ERROR_OBJECT
 mov ax,WORD PTR [edi+0x36]
 add esp,4
 cmp DWORD PTR [edi+0x30],0x4e20
 mov WORD PTR [edi+0x34],ax
 mov BYTE PTR [edi+0x39],1
 jle .Lclear
 mov ecx,DWORD PTR [edi+0x14]
 mov eax,0x2aaaaaab
 sub ecx,DWORD PTR [edi+0x28]
 imul ecx
 sar edx,2
 mov.s eax,edx
 shr eax,31
 inc eax
 add.s eax,edx
 cmp eax,0x4e20
 jge .Lclear
 mov edx,0x4e20
 mov.s ecx,edi
 call RESIZE_CALLINFO
.Lclear:
 mov DWORD PTR [edi+0x64],0
 mov DWORD PTR [edi+0x60],0
 pop edi
 pop esi
 pop ecx
 ret
.section .note.GNU-stack,"",@progbits
