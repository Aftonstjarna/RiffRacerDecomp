# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b3df0,0x4b3e32); both returns included; INT3 padding excluded.
# ECX=source begin, EDX=source end; [entry ESP+4]=destination.
# Caller cleans stack. EAX=advanced destination. EBP/ESI/EDI preserved.
.intel_syntax noprefix
.code32
.text
.global original_record16_range_copy
original_record16_range_copy:
 push ebp
 mov.s ebp,esp
 cmp.s ecx,edx
 je .Lempty
 push esi
 mov esi,DWORD PTR [ebp+8]
 push edi
 lea edi,[ecx+8]
 nop
.Lloop:
 test esi,esi
 je .Ladvance
 mov eax,DWORD PTR [edi-8]
 mov DWORD PTR [esi],eax
 mov eax,DWORD PTR [edi-4]
 mov DWORD PTR [esi+4],eax
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [esi+8],eax
 mov eax,DWORD PTR [edi+4]
 mov DWORD PTR [esi+12],eax
.Ladvance:
 add edi,16
 add esi,16
 lea ecx,[edi-8]
 cmp.s ecx,edx
 jne .Lloop
 pop edi
 mov.s eax,esi
 pop esi
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
