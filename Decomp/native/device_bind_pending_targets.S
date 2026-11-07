# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4a4f30,0x4a4faa); both returns included; INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_device_bind_pending_targets
.equ prepare_targets,0x4a4d80
.equ release_targets,0x4a4ea0
original_device_bind_pending_targets:
 push esi
 mov.s esi,ecx
 cmp BYTE PTR [esi],0
 je .failure
 mov BYTE PTR [esi],0
 call prepare_targets
 test al,al
 je .failure
 cmp BYTE PTR [esi+2],0
 je .default_index
 mov edx,DWORD PTR [esi+0x450]
 jmp .bind_color
.default_index:
 xor.s edx,edx
.bind_color:
 mov eax,DWORD PTR [esi+0x78]
 push DWORD PTR [esi+edx*4+0xc]
 push 0
 mov ecx,DWORD PTR [eax]
 push eax
 call DWORD PTR [ecx+0x94]
 test eax,eax
 js .cleanup
 mov eax,DWORD PTR [esi+0x78]
 push DWORD PTR [esi+0x14]
 push eax
 mov ecx,DWORD PTR [eax]
 call DWORD PTR [ecx+0x9c]
 test eax,eax
 js .cleanup
 mov ecx,DWORD PTR [esi+0x78]
 lea eax,[esi+0x1c]
 push eax
 push ecx
 mov edx,DWORD PTR [ecx]
 call DWORD PTR [edx+0xbc]
 test eax,eax
 js .cleanup
 mov al,BYTE PTR [esi+2]
 mov BYTE PTR [esi+3],al
 mov al,1
 mov BYTE PTR [esi+1],1
 pop esi
 ret
.cleanup:
 mov.s ecx,esi
 call release_targets
.failure:
 xor.s al,al
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
