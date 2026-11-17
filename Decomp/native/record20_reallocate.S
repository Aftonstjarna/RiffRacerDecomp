.intel_syntax noprefix
.code32
.text
.global original_record20_reallocate
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x52c750.
.equ copy_records,0x4b3e80
original_record20_reallocate:
 push ebp
 mov.s ebp,esp
 push ebx
 push esi
 mov esi,DWORD PTR [ebp+8]
 mov.s ebx,ecx
 push edi
 xor.s edi,edi
 test esi,esi
 je allocated
 cmp esi,0xccccccc
 ja failure
 lea eax,[esi+esi*4]
 shl eax,2
 push eax
 call DWORD PTR ds:0x92d4b4
 mov.s edi,eax
 add esp,4
 test edi,edi
 jne allocated
failure:
 call DWORD PTR ds:0x92d164
allocated:
 push DWORD PTR [ebp+8]
 mov edx,DWORD PTR [ebx+4]
 mov ecx,DWORD PTR [ebx]
 sub esp,8
 push edi
 call copy_records
 mov ecx,DWORD PTR [ebx+4]
 mov eax,0x66666667
 sub ecx,DWORD PTR [ebx]
 add esp,0x10
 imul ecx
 mov eax,DWORD PTR [ebx]
 sar edx,3
 mov.s ecx,edx
 shr ecx,0x1f
 add.s ecx,edx
 mov DWORD PTR [ebp+8],ecx
 test eax,eax
 je update
 push eax
 call DWORD PTR ds:0x92d4b0
 mov ecx,DWORD PTR [ebp+8]
 add esp,4
update:
 lea eax,[esi+esi*4]
 mov DWORD PTR [ebx],edi
 lea eax,[edi+eax*4]
 mov DWORD PTR [ebx+8],eax
 lea eax,[ecx+ecx*4]
 lea eax,[edi+eax*4]
 pop edi
 pop esi
 mov DWORD PTR [ebx+4],eax
 pop ebx
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
