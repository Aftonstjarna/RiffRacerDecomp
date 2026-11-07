# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x422580,0x4225b9), 57 bytes.
.intel_syntax noprefix
.code32
.text
.global original_record36_copy_range
original_record36_copy_range:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push esi
 mov.s esi,ecx
 cmp.s esi,edx
 je .Ldone
 {disp8} lea ecx,[ecx+0]
.Lloop:
 test eax,eax
 je .Ladvance
 movdqu xmm0,XMMWORD PTR [esi]
 movdqu XMMWORD PTR [eax],xmm0
 movdqu xmm0,XMMWORD PTR [esi+16]
 movdqu XMMWORD PTR [eax+16],xmm0
 mov ecx,DWORD PTR [esi+32]
 mov DWORD PTR [eax+32],ecx
.Ladvance:
 add esi,36
 add eax,36
 cmp.s esi,edx
 jne .Lloop
.Ldone:
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
