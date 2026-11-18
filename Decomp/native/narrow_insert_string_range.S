# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x47ac40.
.intel_syntax noprefix
.code32
.text
.global original_narrow_insert_string_range
.equ grow,0x416730
.equ set_length,0x416700
.equ copy_bytes,0x8f8d66
original_narrow_insert_string_range:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov.s esi,ecx
 push edi
 mov edx,DWORD PTR [esi+0x10]
 cmp edx,DWORD PTR [ebp+0x8]
 jb .L47ad5b
 mov ebx,DWORD PTR [ebp+0xc]
 mov eax,DWORD PTR [ebp+0x10]
 mov ecx,DWORD PTR [ebx+0x10]
 cmp.s ecx,eax
 jb .L47ad5b
 mov edi,DWORD PTR [ebp+0x14]
 sub.s ecx,eax
 cmp.s ecx,edi
 cmovb edi,ecx
 or eax,0xffffffff
 sub.s eax,edx
 cmp.s eax,edi
 ja .L47ac83
 push 0x99994c
 call DWORD PTR ds:0x92d168
.L47ac83:
 test edi,edi
 je .L47ad52
 lea eax,[edx+edi*1]
 mov.s ecx,esi
 push 0x0
 push eax
 mov DWORD PTR [ebp+0x14],eax
 call grow
 test al,al
 je .L47ad52
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L47acb2
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],ecx
 jmp .L47acb5
.L47acb2:
 mov DWORD PTR [ebp+0xc],esi
.L47acb5:
 cmp eax,0x10
 jb .L47acbe
 mov edx,DWORD PTR [esi]
 jmp .L47acc0
.L47acbe:
 mov.s edx,esi
.L47acc0:
 mov eax,DWORD PTR [esi+0x10]
 mov ecx,DWORD PTR [ebp+0x8]
 sub.s eax,ecx
 je .L47ace3
 push eax
 mov eax,DWORD PTR [ebp+0xc]
 add.s eax,ecx
 push eax
 lea eax,[edx+ecx*1]
 add.s eax,edi
 push eax
 call DWORD PTR ds:0x92d4a4
 mov ecx,DWORD PTR [ebp+0x8]
 add esp,0xc
.L47ace3:
 cmp.s esi,ebx
 jne .L47ad1d
 mov eax,DWORD PTR [ebp+0x10]
 cmp.s ecx,eax
 jae .L47acf0
 add.s eax,edi
.L47acf0:
 mov edx,DWORD PTR [esi+0x14]
 cmp edx,0x10
 jb .L47acfc
 mov ebx,DWORD PTR [esi]
 jmp .L47acfe
.L47acfc:
 mov.s ebx,esi
.L47acfe:
 cmp edx,0x10
 jb .L47ad07
 mov edx,DWORD PTR [esi]
 jmp .L47ad09
.L47ad07:
 mov.s edx,esi
.L47ad09:
 test edi,edi
 je .L47ad48
 add.s eax,ebx
 push edi
 push eax
 lea eax,[edx+ecx*1]
 push eax
 call DWORD PTR ds:0x92d4a4
 jmp .L47ad45
.L47ad1d:
 cmp DWORD PTR [ebx+0x14],0x10
 jb .L47ad25
 mov ebx,DWORD PTR [ebx]
.L47ad25:
 cmp DWORD PTR [esi+0x14],0x10
 jb .L47ad2f
 mov edx,DWORD PTR [esi]
 jmp .L47ad31
.L47ad2f:
 mov.s edx,esi
.L47ad31:
 test edi,edi
 je .L47ad48
 mov eax,DWORD PTR [ebp+0x10]
 add.s eax,ebx
 push edi
 push eax
 lea eax,[edx+ecx*1]
 push eax
 call copy_bytes
.L47ad45:
 add esp,0xc
.L47ad48:
 push DWORD PTR [ebp+0x14]
 mov.s ecx,esi
 call set_length
.L47ad52:
 pop edi
 mov.s eax,esi
 pop esi
 pop ebx
 pop ebp
 ret 0x10
.L47ad5b:
 push 0x99995c
 call DWORD PTR ds:0x92d16c
.section .note.GNU-stack,"",@progbits
