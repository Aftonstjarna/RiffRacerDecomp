# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x49fbd0,0x49fc41); following INT3 padding excluded.
# ECX=this: three 12-byte records; delete nonnull buffers in reverse order.
.intel_syntax noprefix
.code32
.text
.global original_shutdown_buffer_records_destroy
original_shutdown_buffer_records_destroy:
 push esi
 {load} mov esi,ecx
 push edi
 mov edi,DWORD PTR [0x92d4b0]
 mov eax,DWORD PTR [esi+0x18]
 test eax,eax
 je .Lsecond
 push eax
 call edi
 add esp,4
 mov DWORD PTR [esi+0x18],0
 mov DWORD PTR [esi+0x1c],0
 mov DWORD PTR [esi+0x20],0
.Lsecond:
 mov eax,DWORD PTR [esi+0xc]
 test eax,eax
 je .Lfirst
 push eax
 call edi
 add esp,4
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+0x10],0
 mov DWORD PTR [esi+0x14],0
.Lfirst:
 mov eax,DWORD PTR [esi]
 test eax,eax
 je .Ldone
 push eax
 call edi
 add esp,4
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
.Ldone:
 pop edi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
