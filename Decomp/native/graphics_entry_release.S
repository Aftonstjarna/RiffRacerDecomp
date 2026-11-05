# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x49ca20,0x49caa7); following int3 padding is excluded.
.intel_syntax noprefix
.code32
.text
.global original_graphics_entry_release
original_graphics_entry_release:
 push ebp
 {load} mov ebp,esp
 push esi
 {load} mov esi,ecx
 mov edx,DWORD PTR [esi+0x8]
 test edx,edx
 je .Lresult
 cmp DWORD PTR [esi],0
 je .Lunowned
 cmp BYTE PTR [ebp+0x8],0
 je .Lresult
 jmp .Lforce
.Lunowned:
 cmp BYTE PTR [ebp+0x8],0
 je .Lrelease
.Lforce:
 mov eax,DWORD PTR [edx+0x4]
 mov eax,DWORD PTR [eax+0x4]
 cmp DWORD PTR [eax+edx+0x8],1
 jbe .Lrelease
 {disp8} lea ecx,[ecx+0]
.Lloop:
 mov eax,DWORD PTR [edx+0x4]
 lea ecx,[edx+0x4]
 mov eax,DWORD PTR [eax+0x4]
 {load} add ecx,eax
 dec DWORD PTR [ecx+0x4]
 jne .Lreload
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lreload:
 mov edx,DWORD PTR [esi+0x8]
 mov eax,DWORD PTR [edx+0x4]
 mov eax,DWORD PTR [eax+0x4]
 cmp DWORD PTR [eax+edx+0x8],1
 ja .Lloop
.Lrelease:
 mov ecx,DWORD PTR [esi+0x8]
 test ecx,ecx
 je .Lresult
 mov eax,DWORD PTR [ecx+0x4]
 add ecx,0x4
 mov eax,DWORD PTR [eax+0x4]
 {load} add ecx,eax
 dec DWORD PTR [ecx+0x4]
 jne .Lclear
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Lclear:
 mov DWORD PTR [esi+0x8],0
.Lresult:
 {load} xor eax,eax
 cmp DWORD PTR [esi+0x8],eax
 pop esi
 sete al
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
