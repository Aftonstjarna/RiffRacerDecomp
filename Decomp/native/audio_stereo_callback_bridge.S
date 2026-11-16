.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x58e7a0,0x58e7d3); no padding included.
# cdecl (first input, second input, decoder); invokes decoder callback twice.
.global original_audio_stereo_callback_bridge
original_audio_stereo_callback_bridge:
 push ebp
 {load} mov ebp,esp
 push esi
 push edi
 mov edi,DWORD PTR [ebp+0x10]
 push 0
 push edi
 push 0
 push DWORD PTR [ebp+0x8]
 mov eax,DWORD PTR [edi+0x4cb4]
 call eax
 mov ecx,DWORD PTR [edi+0x4cb4]
 {load} mov esi,eax
 push 1
 push edi
 push 1
 push DWORD PTR [ebp+0xc]
 call ecx
 add esp,0x20
 {load} add eax,esi
 pop edi
 pop esi
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
