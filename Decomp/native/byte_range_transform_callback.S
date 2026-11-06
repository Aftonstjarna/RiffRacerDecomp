# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5c2740,0x5c279b), including both returns; INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_byte_range_transform_callback
original_byte_range_transform_callback:
 push ebp
 {load} mov ebp,esp
 push ecx
 push ebx
 push esi
 push edi
 {load} mov edi,edx
 mov DWORD PTR [ebp-4],ecx
 mov edx,DWORD PTR [ebp+8]
 {load} xor esi,esi
 {load} sub edx,edi
 {load} xor ebx,ebx
 cmp edi,DWORD PTR [ebp+8]
 cmova edx,esi
 mov DWORD PTR [ebp+8],edx
 test edx,edx
 je .Lempty
 mov esi,DWORD PTR [ebp+12]
.Lloop:
 movsx eax,BYTE PTR [edi]
 push eax
 call DWORD PTR [ebp+16]
 mov BYTE PTR [esi],al
 lea edi,[edi+1]
 mov esi,DWORD PTR [ebp+12]
 inc ebx
 inc esi
 add esp,4
 mov DWORD PTR [ebp+12],esi
 cmp ebx,DWORD PTR [ebp+8]
 jne .Lloop
 mov eax,DWORD PTR [ebp-4]
 pop edi
 mov DWORD PTR [eax],esi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.Lempty:
 mov eax,DWORD PTR [ebp+12]
 pop edi
 pop esi
 mov DWORD PTR [ecx],eax
 {load} mov eax,ecx
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
