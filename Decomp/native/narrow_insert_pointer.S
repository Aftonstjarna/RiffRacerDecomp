# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x47ab30.
.intel_syntax noprefix
.code32
.text
.global original_narrow_insert_pointer
.equ self_insert,0x47ac40
.equ grow,0x416730
.equ copy_bytes,0x8f8d66
.equ set_length,0x416700
original_narrow_insert_pointer:
 push ebp
 mov.s ebp,esp
 push esi
 push edi
 mov edi,DWORD PTR [ebp+0xc]
 mov.s esi,ecx
 test edi,edi
 je .external
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,0x10
 jb .inline1
 mov eax,DWORD PTR [esi]
 jmp .base1
.inline1:
 mov.s eax,esi
.base1:
 cmp.s edi,eax
 jb .external
 cmp ecx,0x10
 jb .inline2
 mov edx,DWORD PTR [esi]
 jmp .base2
.inline2:
 mov.s edx,esi
.base2:
 mov eax,DWORD PTR [esi+0x10]
 add.s eax,edx
 cmp.s eax,edi
 jbe .external
 cmp ecx,0x10
 jb .inline3
 mov eax,DWORD PTR [esi]
 jmp .base3
.inline3:
 mov.s eax,esi
.base3:
 push DWORD PTR [ebp+0x10]
 sub.s edi,eax
 mov.s ecx,esi
 push edi
 push esi
 push DWORD PTR [ebp+0x8]
 call self_insert
 pop edi
 pop esi
 pop ebp
 ret 0xc
.external:
 mov ecx,DWORD PTR [esi+0x10]
 cmp ecx,DWORD PTR [ebp+0x8]
 jae .position_ok
 push 0x99995c
 call DWORD PTR [0x92d16c]
.position_ok:
 or eax,-1
 push ebx
 mov ebx,DWORD PTR [ebp+0x10]
 sub.s eax,ecx
 cmp.s eax,ebx
 ja .length_ok
 push 0x99994c
 call DWORD PTR [0x92d168]
.length_ok:
 test ebx,ebx
 je .done
 lea eax,[ecx+ebx]
 mov.s ecx,esi
 push 0
 push eax
 mov DWORD PTR [ebp+0xc],eax
 call grow
 test al,al
 je .done
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .inline4
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],ecx
 jmp .base4
.inline4:
 mov DWORD PTR [ebp+0x10],esi
.base4:
 cmp eax,0x10
 jb .inline5
 mov edx,DWORD PTR [esi]
 jmp .base5
.inline5:
 mov.s edx,esi
.base5:
 mov eax,DWORD PTR [esi+0x10]
 mov ecx,DWORD PTR [ebp+0x8]
 sub.s eax,ecx
 je .no_shift
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add.s eax,ecx
 push eax
 lea eax,[edx+ecx]
 add.s eax,ebx
 push eax
 call DWORD PTR [0x92d4a4]
 mov ecx,DWORD PTR [ebp+0x8]
 add esp,0xc
.no_shift:
 cmp DWORD PTR [esi+0x14],0x10
 jb .inline6
 mov eax,DWORD PTR [esi]
 jmp .base6
.inline6:
 mov.s eax,esi
.base6:
 test ebx,ebx
 je .no_copy
 push ebx
 add.s eax,ecx
 push edi
 push eax
 call copy_bytes
 add esp,0xc
.no_copy:
 push DWORD PTR [ebp+0xc]
 mov.s ecx,esi
 call set_length
.done:
 pop ebx
 pop edi
 mov.s eax,esi
 pop esi
 pop ebp
 ret 0xc
.section .note.GNU-stack,"",@progbits
