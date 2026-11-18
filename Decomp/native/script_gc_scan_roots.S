.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x4f1fe0; external dispatch table at 0x4f20b8.
.global original_script_gc_scan_roots
.equ mark_object,0x4f0ef0
.equ dispatch_table,0x4f20b8
original_script_gc_scan_roots:
 push ebp
 {load} mov ebp,esp
 push ecx
 push ebx
 {load} mov ebx,ecx
 mov ecx,9
 push esi
 push edi
 mov [ebp-4],ecx
 lea edi,[ebx+0x7c]
.Lloop:
 mov esi,[edi]
 test esi,esi
 je .Lnext
 test byte ptr [esi+5],3
 je .Lnext
 movzx eax,byte ptr [esi+4]
 and byte ptr [esi+5],0xfc
 add eax,-4
 mov dl,[esi+5]
 cmp eax,6
 ja .Lnext
 jmp dword ptr [eax*4+dispatch_table]
.Lcase_a:
 mov eax,[esi+8]
 or dl,4
 mov [esi+5],dl
 test eax,eax
 je .La2
 test byte ptr [eax+5],3
 je .La2
 {load} mov edx,eax
 {load} mov ecx,ebx
 call mark_object
 mov ecx,[ebp-4]
.La2:
 mov edx,[esi+0xc]
 test byte ptr [edx+5],3
 je .Lnext
 {load} mov ecx,ebx
 call mark_object
 mov ecx,[ebp-4]
 jmp .Lnext
.Lcase_b:
 mov eax,[esi+8]
 cmp dword ptr [eax+4],4
 jl .Lb2
 mov edx,[eax]
 test byte ptr [edx+5],3
 je .Lb2
 {load} mov ecx,ebx
 call mark_object
 mov ecx,[ebp-4]
.Lb2:
 lea eax,[esi+0xc]
 cmp [esi+8],eax
 jne .Lnext
 or byte ptr [esi+5],4
 jmp .Lnext
.Lcase_c:
 mov eax,[ebx+0x24]
 mov [esi+8],eax
 jmp .Linsert
.Lcase_d:
 mov eax,[ebx+0x24]
 mov [esi+0x18],eax
 jmp .Linsert
.Lcase_e:
 mov eax,[ebx+0x24]
 mov [esi+0x5c],eax
 jmp .Linsert
.Lcase_f:
 mov eax,[ebx+0x24]
 mov [esi+0x44],eax
.Linsert:
 mov [ebx+0x24],esi
.Lnext:
 add edi,4
 dec ecx
 mov [ebp-4],ecx
 jne .Lloop
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
