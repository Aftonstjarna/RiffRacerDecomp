.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58a500, complete span through ret at 0x58a54e.
.equ reset_buffers,0x58a410
.equ reset_stream,0x58a550
.equ free_iat,0x92d3a4
.global original_audio_decoder_reset_state
original_audio_decoder_reset_state:
 push esi
 {load} mov esi,ecx
 call reset_buffers
 {load} mov ecx,esi
 call reset_stream
 mov eax,DWORD PTR [esi+0x4d40]
 test eax,eax
 je reset_flags
 push eax
 call DWORD PTR [free_iat]
 add esp,4
 mov DWORD PTR [esi+0x4d40],0
reset_flags:
 mov DWORD PTR [esi+0x6cd0],0
 {load} xor eax,eax
 mov DWORD PTR [esi+0x6cc4],1
 mov DWORD PTR [esi+0x6cc8],0
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
