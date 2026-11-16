.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e750,0x58e793); INT3 padding excluded.
.equ backend_table,0xbaf4a0
.global original_audio_callback_backend_select
original_audio_callback_backend_select:
 push ecx
 mov DWORD PTR [ecx+0x6d40],-1
 mov DWORD PTR [ecx+0x6d48],-1
 mov DWORD PTR [ecx+0x6d4c],edx
 mov DWORD PTR [ecx+0x6d50],0x40
 mov DWORD PTR [ecx+0x6d3c],backend_table
 call DWORD PTR [backend_table]
 {load} xor ecx,ecx
 add esp,4
 test eax,eax
 setns cl
 lea eax,[ecx-1]
 ret
.section .note.GNU-stack,"",@progbits
