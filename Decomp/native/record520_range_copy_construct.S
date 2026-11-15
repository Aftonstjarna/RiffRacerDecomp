# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416a60,0x416a94); next bytes are INT3 padding.
# ECX=first, EDX=last, [ESP+4]=destination; caller cleanup; EAX=end.
.intel_syntax noprefix
.code32
.text
.global original_record520_range_copy_construct
original_record520_range_copy_construct:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push ebx
 mov.s ebx,edx
 mov.s edx,ecx
 cmp.s edx,ebx
 je .Ldone
 push esi
 push edi
.Lloop:
 test eax,eax
 je .Ladvance
 mov ecx,0x82
 mov.s esi,edx
 mov.s edi,eax
 rep movsd
.Ladvance:
 add edx,0x208
 add eax,0x208
 cmp.s edx,ebx
 jne .Lloop
 pop edi
 pop esi
.Ldone:
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
