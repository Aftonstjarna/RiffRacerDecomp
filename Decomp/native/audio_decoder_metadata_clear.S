.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x58b220; end exclusive 0x58b2b4; no branches or external data.
.global original_audio_decoder_metadata_clear
original_audio_decoder_metadata_clear:
 mov BYTE PTR [ecx+0x6f70],0
 mov DWORD PTR [ecx+0x6f74],0
 mov DWORD PTR [ecx+0x6f78],0
 mov DWORD PTR [ecx+0x6f7c],0
 mov DWORD PTR [ecx+0x6f80],0
 mov DWORD PTR [ecx+0x6f84],0
 mov DWORD PTR [ecx+0x6f88],0
 mov DWORD PTR [ecx+0x6f90],0
 mov DWORD PTR [ecx+0x6f8c],0
 mov DWORD PTR [ecx+0x6f98],0
 mov DWORD PTR [ecx+0x6f94],0
 mov DWORD PTR [ecx+0x6fa0],0
 mov DWORD PTR [ecx+0x6f9c],0
 mov DWORD PTR [ecx+0x6fa8],0
 mov DWORD PTR [ecx+0x6fa4],0
 ret
.section .note.GNU-stack,"",@progbits
