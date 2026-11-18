.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41da10.
.global original_worker_record12_reallocate
original_worker_record12_reallocate:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fdb30
 mov eax, DWORD PTR fs:[0]
 push eax
 sub esp,8
 push ebx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-12]
 mov DWORD PTR fs:[0],eax
 mov DWORD PTR [ebp-16],esp
 {load} mov ebx,ecx
 mov edi,DWORD PTR [ebp+8]
 {load} xor esi,esi
 mov DWORD PTR [ebp-20],esi
 test edi,edi
 je .Lallocated
 cmp edi,0x15555555
 ja .Lfailure
 lea eax,[edi+edi*2]
 shl eax,2
 push eax
 call DWORD PTR [0x92d4b4]
 {load} mov esi,eax
 add esp,4
 mov DWORD PTR [ebp-20],esi
 test esi,esi
 jne .Lallocated
.Lfailure:
 call DWORD PTR [0x92d164]
.Lallocated:
 mov DWORD PTR [ebp-4],0
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 mov ecx,DWORD PTR [ebx]
 sub esp,8
 push esi
 call copy_records
 mov DWORD PTR [ebp-4],-1
 mov eax,0x2aaaaaab
 mov ecx,DWORD PTR [ebx+4]
 add esp,16
 sub ecx,DWORD PTR [ebx]
 imul ecx
 mov eax,DWORD PTR [ebx]
 sar edx,1
 {load} mov ecx,edx
 shr ecx,31
 {load} add ecx,edx
 mov DWORD PTR [ebp+8],ecx
 test eax,eax
 je .Lupdate
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 push ecx
 {load} mov ecx,eax
 call destroy_records
 push DWORD PTR [ebx]
 call DWORD PTR [0x92d4b0]
 mov ecx,DWORD PTR [ebp+8]
 add esp,12
.Lupdate:
 lea eax,[edi+edi*2]
 mov DWORD PTR [ebx],esi
 lea eax,[esi+eax*4]
 mov DWORD PTR [ebx+8],eax
 lea eax,[ecx+ecx*2]
 lea eax,[esi+eax*4]
 mov DWORD PTR [ebx+4],eax
 mov ecx,DWORD PTR [ebp-12]
 mov DWORD PTR fs:[0],ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret 4
# Exception cleanup continuation follows the normal return.
 push DWORD PTR [ebp-20]
 call DWORD PTR [0x92d4b0]
 add esp,4
 push 0
 push 0
 call unwind_resume
.equ copy_records,0x41dcb0
.equ destroy_records,0x41db40
.equ unwind_resume,0x8f8d5a
.section .note.GNU-stack,"",@progbits
