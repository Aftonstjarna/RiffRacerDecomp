# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4b31e0,0x4b3253); both return paths included, INT3 padding excluded.
# ECX=source begin, EDX=source end, [entry ESP+4]=destination.
# Caller cleans stack; returns advanced destination in EAX.
# Copies fields, not padding: dwords +0..+20,+28..+40 and byte +24.
.intel_syntax noprefix
.code32
.text
.global original_record44_copy_range
original_record44_copy_range:
 push ebp
 {load} mov ebp,esp
 push ebx
 {load} mov ebx,edx
 {load} cmp ecx,ebx
 je .Lempty
 mov edx,DWORD PTR [ebp+8]
 push esi
 push edi
 lea esi,[ecx+0x24]
 lea edi,[edx+0x24]
.Lcopy:
 mov eax,DWORD PTR [esi-0x24]
 lea esi,[esi+0x2c]
 mov DWORD PTR [edx],eax
 lea edi,[edi+0x2c]
 mov eax,DWORD PTR [esi-0x4c]
 add edx,0x2c
 mov DWORD PTR [edi-0x4c],eax
 mov eax,DWORD PTR [esi-0x48]
 mov DWORD PTR [edi-0x48],eax
 mov eax,DWORD PTR [esi-0x44]
 mov DWORD PTR [edi-0x44],eax
 mov eax,DWORD PTR [esi-0x40]
 mov DWORD PTR [edi-0x40],eax
 mov eax,DWORD PTR [esi-0x3c]
 mov DWORD PTR [edi-0x3c],eax
 mov al,BYTE PTR [esi-0x38]
 mov BYTE PTR [edi-0x38],al
 mov eax,DWORD PTR [esi-0x34]
 mov DWORD PTR [edi-0x34],eax
 mov eax,DWORD PTR [esi-0x30]
 mov DWORD PTR [edi-0x30],eax
 mov eax,DWORD PTR [esi-0x2c]
 mov DWORD PTR [edi-0x2c],eax
 mov ecx,DWORD PTR [esi-0x28]
 mov DWORD PTR [edi-0x28],ecx
 lea ecx,[esi-0x24]
 {load} cmp ecx,ebx
 jne .Lcopy
 pop edi
 pop esi
 {load} mov eax,edx
 pop ebx
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+8]
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
