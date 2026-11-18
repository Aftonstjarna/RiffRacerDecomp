# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x44f4f0.
.intel_syntax noprefix
.code32
.text
.global original_graphics_startup_wide_message
.equ convert_wide,0x44f3e0
.equ get_service,0x6d86bb
.equ construct_wide,0x44f490
.equ check_cookie,0x8f8958
original_graphics_startup_wide_message:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8ff9d8
 mov eax,fs:0
 push eax
 sub esp,0x34
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 mov DWORD PTR [ebp-0x10],eax
 push esi
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 cmp DWORD PTR [ecx+0x14],0x10
 jb .Linline
 mov ecx,DWORD PTR [ecx]
.Linline:
 mov.s edx,ecx
 lea ecx,[ebp-0x40]
 call convert_wide
 mov.s esi,eax
 mov DWORD PTR [ebp-4],0
 call get_service
 push 1
 mov.s ecx,eax
 mov edx,DWORD PTR [eax]
 call DWORD PTR [edx+0xc]
 mov.s edx,eax
 lea ecx,[ebp-0x28]
 call construct_wide
 cmp DWORD PTR [ebp-0x14],8
 lea eax,[ebp-0x28]
 cmovae eax,DWORD PTR [ebp-0x28]
 cmp DWORD PTR [esi+0x14],8
 jb .Lmessage
 mov esi,DWORD PTR [esi]
.Lmessage:
 push 0x10
 push eax
 push esi
 push 0
 call DWORD PTR [0x92d594]
 cmp DWORD PTR [ebp-0x14],8
 mov esi,DWORD PTR [0x92d4b0]
 jb .Lfirst_done
 push DWORD PTR [ebp-0x28]
 call esi
 add esp,4
.Lfirst_done:
 cmp DWORD PTR [ebp-0x2c],8
 jb .Lsecond_done
 push DWORD PTR [ebp-0x40]
 call esi
 add esp,4
.Lsecond_done:
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop esi
 mov ecx,DWORD PTR [ebp-0x10]
 xor.s ecx,ebp
 call check_cookie
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
