# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b3e80,0x4b3eaf); adjacent INT3 padding excluded.
# ECX=source begin, EDX=source end, [entry ESP+4]=destination.
# Caller cleans stack; EAX=advanced destination. ESI and EBP preserved.
.intel_syntax noprefix
.code32
.text
.global original_record20_range_copy
original_record20_range_copy:
 push ebp
 mov.s ebp,esp
 mov eax,DWORD PTR [ebp+8]
 push esi
 mov.s esi,ecx
 cmp.s esi,edx
 je .Ldone
 lea.d8 ecx,[ecx+0]
.Lloop:
 test eax,eax
 je .Ladvance
 movdqu xmm0,XMMWORD PTR [esi]
 movdqu XMMWORD PTR [eax],xmm0
 mov ecx,DWORD PTR [esi+16]
 mov DWORD PTR [eax+16],ecx
.Ladvance:
 add esi,20
 add eax,20
 cmp.s esi,edx
 jne .Lloop
.Ldone:
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
