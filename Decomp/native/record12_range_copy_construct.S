# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x437fe0,0x43801a), including both returns; padding excluded.
# ECX=source begin, EDX=source end, [entry ESP+4]=destination.
# Caller cleans stack; EAX=advanced destination; EDI/ESI/EBP preserved.
.intel_syntax noprefix
.code32
.text
.global original_record12_range_copy_construct
original_record12_range_copy_construct:
 push ebp
 mov.s ebp,esp
 push edi
 mov.s edi,ecx
 cmp.s edi,edx
 je .Lempty
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov.s edi,edi
.Lloop:
 test esi,esi
 je .Ladvance
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [esi],eax
 mov eax,DWORD PTR [edi+4]
 mov DWORD PTR [esi+4],eax
 mov ecx,DWORD PTR [edi+8]
 mov DWORD PTR [esi+8],ecx
.Ladvance:
 add edi,12
 add esi,12
 cmp.s edi,edx
 jne .Lloop
 mov.s eax,esi
 pop esi
 pop edi
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop edi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
