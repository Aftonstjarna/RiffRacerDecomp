.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4482b0.
.global original_ui_sprite_update_property
original_ui_sprite_update_property:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8ff5a8
 mov eax,fs:0
 push eax
 push ecx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov.s edi,ecx
 mov eax,DWORD PTR [ebp+8]
 cmp DWORD PTR [edi+0x38],eax
 je .Ldone
 mov esi,DWORD PTR [edi+0x1c]
 mov DWORD PTR [edi+0x38],eax
 mov DWORD PTR [ebp+8],esi
 test esi,esi
 je .Lheld
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+4]
 inc DWORD PTR [eax+esi+4]
.Lheld:
 mov DWORD PTR [ebp-4],0
 test esi,esi
 je .Lrefresh
 mov eax,DWORD PTR [edi]
 mov.s ecx,edi
 call DWORD PTR [eax+0x50]
.Lrefresh:
 mov eax,DWORD PTR [edi]
 mov.s ecx,edi
 call DWORD PTR [eax+0x74]
 test esi,esi
 je .Lrelease
 push ecx
 mov.s eax,esp
 mov.s ecx,edi
 mov DWORD PTR [eax],esi
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+4]
 inc DWORD PTR [eax+esi+4]
 mov eax,DWORD PTR [edi]
 call DWORD PTR [eax+0x4c]
.Lrelease:
 mov DWORD PTR [ebp-4],-1
 test esi,esi
 je .Ldone
 mov eax,DWORD PTR [esi]
 mov ecx,DWORD PTR [eax+4]
 add.s ecx,esi
 dec DWORD PTR [ecx+4]
 jne .Ldone
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.Ldone:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret 4
.section .note.GNU-stack,"",@progbits
