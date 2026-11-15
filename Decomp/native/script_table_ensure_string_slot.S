# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f0d10,0x4f0d73); surrounding INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_ensure_string_slot
.equ NEW_KEY,0x4f09e0
.equ NIL_VALUE,0x99a41c
original_script_table_ensure_string_slot:
 push ebp
 mov.s ebp,esp
 sub esp,0x10
 mov eax,1
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov.s ebx,ecx
 push edi
 mov.s edi,edx
 # Select the 20-byte node from the interned string hash.
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
 je .Lfound
.Lnext:
 mov eax,DWORD PTR [eax+0x10]
 test eax,eax
 jne .Lchain
 jmp .Linsert
.Lfound:
 cmp eax,NIL_VALUE
 jne .Lreturn
.Linsert:
 # New-key helper consumes a temporary tagged string key by address.
 lea eax,[ebp-0xc]
 mov DWORD PTR [ebp-0xc],esi
 push eax
 mov.s edx,edi
 mov DWORD PTR [ebp-8],4
 mov.s ecx,ebx
 call NEW_KEY
 add esp,4
.Lreturn:
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
