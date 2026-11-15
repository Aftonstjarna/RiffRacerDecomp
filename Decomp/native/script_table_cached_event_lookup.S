.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f5ca0, 81 bytes; padding and next function excluded.
.equ NIL_VALUE,0x99a41c
.global original_script_table_cached_event_lookup
original_script_table_cached_event_lookup:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov eax,1
 push edi
 mov.s edi,ecx
 mov.s ebx,edx
 mov cl,BYTE PTR [edi+7]
 shl eax,cl
 dec eax
 and eax,DWORD PTR [esi+8]
 lea edx,[eax+eax*4]
 mov eax,DWORD PTR [edi+0x10]
 lea eax,[eax+edx*4]
.Lchain:
 cmp DWORD PTR [eax+0xc],4
 jne .Lnext
 cmp DWORD PTR [eax+8],esi
 je .Lvalue
.Lnext:
 mov eax,DWORD PTR [eax+0x10]
 test eax,eax
 jne .Lchain
 mov eax,OFFSET FLAT:NIL_VALUE
.Lvalue:
 cmp DWORD PTR [eax+4],0
 jne .Lreturn
 mov al,1
 mov.s ecx,ebx
 shl al,cl
 or BYTE PTR [edi+6],al
 xor.s eax,eax
.Lreturn:
 pop edi
 pop esi
 pop ebx
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
