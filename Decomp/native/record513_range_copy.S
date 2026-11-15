# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416aa0,0x416ad5). Separate adjustor thunk starts at 0x416ad5.
# ECX=first, EDX=last, [ESP+4]=destination; caller cleanup, EAX=end.
# Requires DF clear, valid record range and accessible nonoverlapping destination.
.intel_syntax noprefix
.code32
.text
.global original_record513_range_copy
original_record513_range_copy:
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
 mov ecx,0x80
 mov.s esi,edx
 mov.s edi,eax
 rep movsd
 movsb
.Ladvance:
 add edx,0x201
 add eax,0x201
 cmp.s edx,ebx
 jne .Lloop
 pop edi
 pop esi
.Ldone:
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
