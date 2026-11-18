.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x499710.
.global original_worker_reference_range_clear
original_worker_reference_range_clear:
 push ebx
 push esi
 push edi
 {load} mov edi,ecx
 mov ebx,DWORD PTR [edi+4]
 mov esi,DWORD PTR [edi]
 {load} cmp esi,ebx
 je .Lempty
 {load} mov edi,edi
.Lloop:
 mov ecx,DWORD PTR [esi]
 test ecx,ecx
 je .Lnext
 mov eax,DWORD PTR [ecx+4]
 add ecx,4
 mov eax,DWORD PTR [eax+4]
 {load} add ecx,eax
 dec DWORD PTR [ecx+4]
 jne .Lnext
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lnext:
 add esi,4
 {load} cmp esi,ebx
 jne .Lloop
 mov eax,DWORD PTR [edi]
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 ret
.Lempty:
 {load} mov eax,esi
 mov DWORD PTR [edi+4],eax
 pop edi
 pop esi
 pop ebx
 ret
