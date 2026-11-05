# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x48c690,0x48c6d5); adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_window_handles_cleanup
original_window_handles_cleanup:
# ECX=this; no stack arguments; preserves EBX/ESI/EDI/EBP. EAX incidental.
 push ebx
 mov.s ebx,ecx
 push esi
 push edi
 mov edi,0x2
 lea esi,[ebx+0x4]
 {disp8} lea ecx,[ecx+0x0]
.Ldestroy_slot:
 mov eax,DWORD PTR [esi]
 test eax,eax
 je .Lclear_slot
 push eax
 call DWORD PTR [destroy_window_iat]
.Lclear_slot:
 mov DWORD PTR [esi],0x0
 add esi,0x4
 dec edi
 jne .Ldestroy_slot
# Slots +4 and +8 are cleared even if DestroyWindow returns failure.
 mov eax,DWORD PTR [ebx]
 test eax,eax
 je .Lfinish
 push eax
 push OFFSET FLAT:window_class_name
 call DWORD PTR [unregister_class_iat]
.Lfinish:
 pop edi
 pop esi
 mov DWORD PTR [ebx],0x0
 pop ebx
 ret
.equ destroy_window_iat,0x92d530
.equ unregister_class_iat,0x92d564
.equ window_class_name,0x9fbd8c
.section .note.GNU-stack,"",@progbits
