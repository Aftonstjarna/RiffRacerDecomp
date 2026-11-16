.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete original span [0x58a550,0x58a77c); padding excluded.
.equ dep_58e6f0,0x58e6f0
.equ dep_58b460,0x58b460
.equ dep_58b3c0,0x58b3c0
.equ dep_58b220,0x58b220
.global original_audio_decoder_reset_stream
original_audio_decoder_reset_stream:
 push   esi
 {load} mov    esi,ecx
 call dep_58e6f0
 xorps  xmm0,xmm0
 mov    DWORD PTR [esi+0x6d04],0x0
 movsd  QWORD PTR [esi+0x4d90],xmm0
 lea    edx,[esi+0x6fa8]
 movsd  xmm0,QWORD PTR [0xa068d8]
 lea    ecx,[esi+0x6fa4]
 mov    DWORD PTR [esi+0x6d08],0x0
 mov    DWORD PTR [esi+0x6ee8],0x0
 mov    DWORD PTR [esi+0x6d00],0x0
 mov    DWORD PTR [esi+0x4d28],0xffffffff
 mov    DWORD PTR [esi+0x4d2c],0xffffffff
 mov    DWORD PTR [esi+0x4d30],0xffffffff
 mov    DWORD PTR [esi+0x4d38],0x1
 mov    BYTE PTR [esi+0x4d3c],0x0
 mov    DWORD PTR [esi+0x4d34],0x0
 mov    DWORD PTR [esi+0x6ee4],0x0
 mov    DWORD PTR [esi+0x6cb4],0x0
 mov    DWORD PTR [esi+0x6cb8],0x0
 mov    DWORD PTR [esi+0x4d24],0x0
 mov    DWORD PTR [esi+0x6cbc],0x0
 mov    DWORD PTR [esi+0x4d88],0x0
 mov    DWORD PTR [esi+0x4d8c],0xffffffff
 mov    DWORD PTR [esi+0x4d1c],0x0
 mov    DWORD PTR [esi+0x4d98],0x0
 mov    DWORD PTR [esi+0x4d20],0x0
 movsd  QWORD PTR [esi+0x4d68],xmm0
 mov    DWORD PTR [esi+0x4d70],0xffffffff
 mov    DWORD PTR [esi+0x4d74],0xffffffff
 mov    DWORD PTR [esi+0x4d78],0x0
 mov    DWORD PTR [esi+0x4d7c],0x0
 mov    DWORD PTR [esi+0x4d80],0x0
 mov    DWORD PTR [esi+0x4d84],0x0
 mov    eax,DWORD PTR [esi+0x6ec8]
 neg    eax
 mov    DWORD PTR [esi+0x4d9c],0x0
 mov    DWORD PTR [esi+0x6d0c],0x0
 mov    DWORD PTR [esi+0x6d14],eax
 mov    DWORD PTR [esi+0x4ce4],0x0
 mov    DWORD PTR [esi+0x6d10],0xffffffff
 mov    DWORD PTR [esi],0x1
 mov    DWORD PTR [esi+0x4],0x0
 mov    DWORD PTR [esi+0x6d18],0xffffffff
 mov    DWORD PTR [esi+0x6d2c],0x0
 mov    DWORD PTR [esi+0x6d24],0x0
 mov    DWORD PTR [esi+0x6d28],0x0
 mov    DWORD PTR [esi+0x6d30],0x0
 mov    DWORD PTR [esi+0x6d34],0x0
 mov    DWORD PTR [esi+0x6d20],0x0
 mov    DWORD PTR [esi+0x6d1c],0x0
 mov    DWORD PTR [esi+0x2438],0x1
 call dep_58b460
 lea    edx,[esi+0x6f90]
 lea    ecx,[esi+0x6f8c]
 call dep_58b3c0
 lea    edx,[esi+0x6fa0]
 lea    ecx,[esi+0x6f9c]
 call dep_58b3c0
 lea    edx,[esi+0x6f98]
 lea    ecx,[esi+0x6f94]
 call dep_58b3c0
 {load} mov    ecx,esi
 call dep_58b220
 mov    DWORD PTR [esi+0x2570],0x0
 mov    DWORD PTR [esi+0x4cf4],0x0
 mov    DWORD PTR [esi+0x4d48],0xffffffff
 pop    esi
 ret
.section .note.GNU-stack,"",@progbits
