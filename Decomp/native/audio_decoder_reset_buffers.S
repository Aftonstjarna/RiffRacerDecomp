.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58a410; exclusive end 0x58a4b0. No internal branches or inline data.
.equ memory_fill,0x8f8d7e
.global original_audio_decoder_reset_buffers
original_audio_decoder_reset_buffers:
 push esi
 {load} mov esi,ecx
 push DWORD PTR [esi+0x2434]
 lea eax,[esi+0x5d28]
 mov DWORD PTR [esi+0x6ce0],0
 push 0
 push DWORD PTR [esi+0x2430]
 mov DWORD PTR [esi+0x6cb0],0
 mov DWORD PTR [esi+0x6ca8],eax
 mov DWORD PTR [esi+0x6cac],eax
 mov DWORD PTR [esi+0x4da4],0
 call memory_fill
 push 0x1f00
 lea eax,[esi+0x4da8]
 push 0
 push eax
 call memory_fill
 xorps xmm0,xmm0
 lea eax,[esi+8]
 movdqu XMMWORD PTR [esi+0x254c],xmm0
 push 0x2400
 movdqu XMMWORD PTR [esi+0x255c],xmm0
 mov WORD PTR [esi+0x256c],0
 push 0
 push eax
 mov DWORD PTR [esi+0x240c],0
 mov DWORD PTR [esi+0x2408],0
 call memory_fill
 add esp,0x24
 {load} xor eax,eax
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
