.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x598d50.
.equ component_lookup,0x5991e0
.equ cookie_check,0x8f8958
.global original_archive_index_lookup
original_archive_index_lookup:
 push ebp
 {load} mov ebp,esp
 sub esp,0x20c
 mov eax,DWORD PTR ds:0xbaabc0
 {load} xor eax,ebp
 mov DWORD PTR [ebp-4],eax
 mov edx,DWORD PTR [ebp+8]
 push ebx
 push esi
 {load} mov esi,edx
 mov DWORD PTR [ebp-0x208],ecx
 push edi
 lea edi,[esi+1]
.Llength:
 mov al,BYTE PTR [esi]
 inc esi
 test al,al
 jne .Llength
 lea ecx,[ebp-0x204]
 {load} sub esi,edi
 {load} sub ecx,edx
.Lcopy:
 mov al,BYTE PTR [edx]
 lea edx,[edx+1]
 mov BYTE PTR [ecx+edx-1],al
 test al,al
 jne .Lcopy
 {load} xor edi,edi
 {load} xor eax,eax
 test esi,esi
 je .Lstart
 {disp32} lea ebx,[ebx+0]
.Lsplit:
 cmp BYTE PTR [ebp+eax-0x204],0x5c
 jne .Lnext
 mov BYTE PTR [ebp+eax-0x204],0
 inc edi
.Lnext:
 inc eax
 {load} cmp eax,esi
 jb .Lsplit
.Lstart:
 mov eax,DWORD PTR [ebp-0x208]
 lea esi,[ebp-0x204]
 {load} xor ebx,ebx
 lea edx,[eax+0x24]
 {disp32} lea esp,[esp+0]
.Llookup:
 push edx
 push esi
 {load} mov ecx,eax
 call component_lookup
 {load} mov edx,eax
 test edx,edx
 je .Lmissing
 {load} mov ecx,esi
 lea eax,[ecx+1]
 mov DWORD PTR [ebp-0x20c],eax
 {disp32} lea ebx,[ebx+0]
.Lcomponent_length:
 mov al,BYTE PTR [ecx]
 inc ecx
 test al,al
 jne .Lcomponent_length
 sub ecx,DWORD PTR [ebp-0x20c]
 inc esi
 mov eax,DWORD PTR [ebp-0x208]
 inc ebx
 {load} add esi,ecx
 {load} cmp ebx,edi
 jbe .Llookup
 movzx eax,WORD PTR [edx+6]
 and eax,0x3fff
 pop edi
 pop esi
 pop ebx
 lea ecx,[eax*8]
 {load} sub ecx,eax
 mov eax,DWORD PTR [ebp-0x208]
 mov eax,DWORD PTR [eax+0xc]
 lea eax,[eax+ecx*4]
 mov ecx,DWORD PTR [ebp-4]
 {load} xor ecx,ebp
 call cookie_check
 {load} mov esp,ebp
 pop ebp
 ret 4
.Lmissing:
 mov ecx,DWORD PTR [ebp-4]
 {load} xor eax,eax
 pop edi
 pop esi
 {load} xor ecx,ebp
 pop ebx
 call cookie_check
 {load} mov esp,ebp
 pop ebp
 ret 4
