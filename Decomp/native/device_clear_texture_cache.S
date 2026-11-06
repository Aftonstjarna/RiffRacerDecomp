# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4add20,0x4add59): complete loop and ret 4; excludes INT3 padding.
# ECX=this; one unused stack argument; device/vtable remains external.
.intel_syntax noprefix
.code32
.text
.global original_device_clear_texture_cache
original_device_clear_texture_cache:
 push ebx
 {load} mov ebx,ecx
 push esi
 push edi
 {load} xor edi,edi
 lea esi,[ebx+0x9ec]
 {disp8} lea ecx,[ecx+0]
.Lslot:
 cmp DWORD PTR [esi],0
 je .Lclear
 mov eax,DWORD PTR [ebx+0x78]
 push 0
 push edi
 push eax
 mov ecx,DWORD PTR [eax]
 call DWORD PTR [ecx+0x104]
.Lclear:
 mov DWORD PTR [esi],0
 inc edi
 add esi,4
 cmp edi,0x10
 jb .Lslot
 pop edi
 pop esi
 pop ebx
 ret 4
.section .note.GNU-stack,"",@progbits
