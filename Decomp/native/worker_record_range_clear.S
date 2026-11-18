# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x49a940.
.intel_syntax noprefix
.code32
.text
.global original_worker_record_range_clear
original_worker_record_range_clear:
 push ebx
 push esi
 push edi
 mov.s edi,ecx
 mov ebx,DWORD PTR [edi+4]
 mov esi,DWORD PTR [edi]
 cmp.s esi,ebx
 je .Lempty
 mov.s edi,edi
.Lloop:
 mov edx,DWORD PTR [esi]
 test edx,edx
 je .Lnext
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 add.s ecx,edx
 dec DWORD PTR [ecx+4]
 jne .Lnext
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lnext:
 add esi,0x18
 cmp.s esi,ebx
 jne .Lloop
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 ret
.Lempty:
 mov.s eax,esi
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 ret
.section .note.GNU-stack,"",@progbits
