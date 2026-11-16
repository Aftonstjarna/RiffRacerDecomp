.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e3d0,0x58e3f7); following INT3 padding excluded.
.equ audio_buffer_commit_consumed,0x58e180
.global original_audio_stream_commit_position
original_audio_stream_commit_position:
 push ebp
 mov.s ebp,esp
 push esi
 mov esi,DWORD PTR [ebp+8]
 lea ecx,[esi+0x6d7c]
 call audio_buffer_commit_consumed
 mov eax,DWORD PTR [esi+0x6d90]
 add eax,DWORD PTR [esi+0x6d88]
 mov DWORD PTR [esi+0x6d44],eax
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
