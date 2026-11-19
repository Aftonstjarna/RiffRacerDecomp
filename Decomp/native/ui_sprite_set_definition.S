.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x448830.
.equ ui_singleton,0xbfbaa4
.equ refresh_visual,0x48b8f0
.equ update_flag,0x41f500
.global original_ui_sprite_set_definition
original_ui_sprite_set_definition:
 push ebp
 {load} mov ebp,esp
 mov eax,DWORD PTR [ui_singleton]
 mov edx,DWORD PTR [ebp+8]
 push esi
 push edi
 {load} mov edi,ecx
 cmp edx,DWORD PTR [eax+0x10]
 jb .Lin_range
 mov ecx,DWORD PTR [eax+0xc]
 jmp .Lselected
.Lin_range:
 imul ecx,edx,0x64
 add ecx,DWORD PTR [eax+0xc]
.Lselected:
 mov esi,DWORD PTR [edi+0x184]
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [esi+4],ecx
 test edx,edx
 je .Ldone
 push ecx
 {load} mov eax,esp
 mov DWORD PTR [eax],edx
 mov eax,DWORD PTR [edx]
 mov eax,DWORD PTR [eax+4]
 inc DWORD PTR [eax+edx+4]
 call refresh_visual
 mov al,BYTE PTR [edi+0x174]
 add esp,4
 mov ecx,DWORD PTR [esi]
 and al,1
 movzx eax,al
 push eax
 call update_flag
.Ldone:
 pop edi
 pop esi
 pop ebp
 ret 4
