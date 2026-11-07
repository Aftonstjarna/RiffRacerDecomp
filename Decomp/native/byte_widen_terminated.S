# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x425c40,0x425c7b). Both returns included; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_byte_widen_terminated
original_byte_widen_terminated:
# Caller-cleaned arguments: destination, source, destination size in bytes.
 push ebp
 mov.s ebp,esp
 mov ecx,DWORD PTR [ebp+0xc]
 mov edx,DWORD PTR [ebp+0x10]
 shr edx,1
 cmp BYTE PTR [ecx],0
 je .Lempty
 push esi
 mov esi,DWORD PTR [ebp+8]
.Lloop:
 cmp edx,1
 jbe .Lterminate
 movzx eax,BYTE PTR [ecx]
 dec edx
 inc ecx
 mov WORD PTR [esi],ax
 add esi,2
 cmp BYTE PTR [ecx],0
 jne .Lloop
.Lterminate:
 xor.s eax,eax
 mov WORD PTR [esi],ax
 pop esi
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 xor.s ecx,ecx
 mov WORD PTR [eax],cx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
