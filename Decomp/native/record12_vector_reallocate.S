.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x429b50.
.equ allocate_slot,0x92d4b4
.equ allocation_failure_slot,0x92d164
.equ delete_slot,0x92d4b0
.equ copy_records,0x42bb40
.global original_record12_vector_reallocate
original_record12_vector_reallocate:
 push ebp
 {load} mov ebp,esp
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 {load} mov ebx,ecx
 push edi
 {load} xor edi,edi
 test esi,esi
 je .Lallocated
 cmp esi,0x15555555
 ja .Lfailure
 lea eax,[esi+esi*2]
 shl eax,2
 push eax
 call DWORD PTR [allocate_slot]
 {load} mov edi,eax
 add esp,4
 test edi,edi
 jne .Lallocated
.Lfailure:
 call DWORD PTR [allocation_failure_slot]
.Lallocated:
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 mov ecx,DWORD PTR [ebx]
 sub esp,8
 push edi
 call copy_records
 mov ecx,DWORD PTR [ebx+4]
 mov eax,0x2aaaaaab
 sub ecx,DWORD PTR [ebx]
 add esp,0x10
 imul ecx
 mov eax,DWORD PTR [ebx]
 sar edx,1
 {load} mov ecx,edx
 shr ecx,0x1f
 {load} add ecx,edx
 mov DWORD PTR [ebp+8],ecx
 test eax,eax
 je .Lreplace
 push eax
 call DWORD PTR [delete_slot]
 mov ecx,DWORD PTR [ebp+8]
 add esp,4
.Lreplace:
 lea eax,[esi+esi*2]
 mov DWORD PTR [ebx],edi
 lea eax,[edi+eax*4]
 mov DWORD PTR [ebx+8],eax
 lea eax,[ecx+ecx*2]
 lea eax,[edi+eax*4]
 pop edi
 pop esi
 mov DWORD PTR [ebx+4],eax
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
