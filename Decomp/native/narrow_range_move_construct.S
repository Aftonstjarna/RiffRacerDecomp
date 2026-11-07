.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x426960, complete 138-byte function; INT3 padding excluded.
.equ memmove_iat,0x92d4a4
.global original_narrow_range_move_construct
original_narrow_range_move_construct:
 push   ebp
 {load} mov    ebp,esp
 push   ebx
 mov    ebx,DWORD PTR [ebp+0xc]
 push   esi
 mov    esi,DWORD PTR [ebp+0x8]
 {load} cmp    esi,ebx
 je empty_range
 push   edi
 mov    edi,DWORD PTR [ebp+0x10]
 add    esi,0x10
move_next:
 test   edi,edi
 je advance
 mov    DWORD PTR [edi+0x14],0xf
 mov    DWORD PTR [edi+0x10],0x0
 mov    BYTE PTR [edi],0x0
 cmp    DWORD PTR [esi+0x4],0x10
 jae transfer_heap
 mov    eax,DWORD PTR [esi]
 inc    eax
 je publish_and_reset
 push   eax
 lea    eax,[esi-0x10]
 push   eax
 push   edi
 call   DWORD PTR [memmove_iat]
 add    esp,0xc
 jmp publish_and_reset
transfer_heap:
 mov    eax,DWORD PTR [esi-0x10]
 mov    DWORD PTR [edi],eax
 mov    DWORD PTR [esi-0x10],0x0
publish_and_reset:
 mov    eax,DWORD PTR [esi]
 mov    DWORD PTR [edi+0x10],eax
 mov    eax,DWORD PTR [esi+0x4]
 mov    DWORD PTR [edi+0x14],eax
 mov    DWORD PTR [esi+0x4],0xf
 mov    DWORD PTR [esi],0x0
 mov    BYTE PTR [esi-0x10],0x0
advance:
 add    esi,0x18
 add    edi,0x18
 lea    ecx,[esi-0x10]
 {load} cmp    ecx,ebx
 jne move_next
 {load} mov    eax,edi
 pop    edi
 pop    esi
 pop    ebx
 pop    ebp
 ret
empty_range:
 mov    eax,DWORD PTR [ebp+0x10]
 pop    esi
 pop    ebx
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
