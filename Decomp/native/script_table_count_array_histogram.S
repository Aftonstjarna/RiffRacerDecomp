# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f03e0,0x4f0457); following INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_count_array_histogram
original_script_table_count_array_histogram:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push ebx
 push esi
 push edi
 xor.s eax,eax
 mov DWORD PTR [ebp-0xc],edx
 mov edi,1
 mov DWORD PTR [ebp-8],ecx
 mov DWORD PTR [ebp-4],eax
 xor.s ebx,ebx
 mov.s esi,edi
 {disp8} lea ecx,[ecx+0]
.Lbucket:
 mov ecx,DWORD PTR [ecx+0x1c]
 xor.s edx,edx
 mov.s eax,esi
 cmp.s esi,ecx
 jle .Lfull_bucket
 mov.s eax,ecx
 cmp.s edi,eax
 jle .Lscan_setup
 mov eax,DWORD PTR [ebp-4]
.Lreturn:
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.Lfull_bucket:
 cmp.s edi,esi
 jg .Laccumulate
.Lscan_setup:
 mov ecx,DWORD PTR [ebp-8]
 sub.s eax,edi
 inc eax
 mov ecx,DWORD PTR [ecx+0xc]
 lea ecx,[ecx+edi*8]
 add ecx,-4
 add.s edi,eax
.Lscan:
 cmp DWORD PTR [ecx],0
 je .Lnext_slot
 inc edx
.Lnext_slot:
 add ecx,8
 dec eax
 jne .Lscan
.Laccumulate:
 mov eax,DWORD PTR [ebp-0xc]
 add.s esi,esi
 add DWORD PTR [eax+ebx*4],edx
 inc ebx
 mov eax,DWORD PTR [ebp-4]
 add.s eax,edx
 mov DWORD PTR [ebp-4],eax
 cmp ebx,0x1a
 jg .Lreturn
 mov ecx,DWORD PTR [ebp-8]
 jmp .Lbucket
.section .note.GNU-stack,"",@progbits
