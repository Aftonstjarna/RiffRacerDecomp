# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x44f380,0x44f3de); both returns included, INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_error_code_narrow_construct
.equ error_text,0x401008
.equ narrow_assign,0x416520
original_error_code_narrow_construct:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 push edx
 mov.s esi,ecx
 mov DWORD PTR [ebp-4],0
 call error_text
 mov.s edx,eax
 mov DWORD PTR [esi+0x14],0xf
 mov DWORD PTR [esi+0x10],0
 mov BYTE PTR [esi],0
 cmp BYTE PTR [edx],0
 jne .nonempty
 xor.s ecx,ecx
 push ecx
 push edx
 mov.s ecx,esi
 call narrow_assign
 mov.s eax,esi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.nonempty:
 mov.s ecx,edx
 push edi
 lea edi,[ecx+1]
.scan:
 mov al,BYTE PTR [ecx]
 inc ecx
 test al,al
 jne .scan
 sub.s ecx,edi
 pop edi
 push ecx
 push edx
 mov.s ecx,esi
 call narrow_assign
 mov.s eax,esi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
