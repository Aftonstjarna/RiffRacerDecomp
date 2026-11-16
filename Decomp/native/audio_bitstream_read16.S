.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x58eab0, complete 77-byte function.
.global original_audio_bitstream_read16
original_audio_bitstream_read16:
push   ebx
mov.s    ebx,ecx
push   esi
push   edi
mov    esi,DWORD PTR [ebx+0x4d50]
mov    ecx,DWORD PTR [ebx+0x4d4c]
movzx  edi,BYTE PTR [esi]
movzx  eax,BYTE PTR [esi+0x1]
lea    edx,[ecx+0x10]
shl    edi,0x8
or.s     edi,eax
movzx  eax,BYTE PTR [esi+0x2]
shl    edi,0x8
or.s     eax,edi
shl    eax,cl
mov.s    ecx,edx
sar    ecx,0x3
and    edx,0x7
pop    edi
add.s    ecx,esi
mov    DWORD PTR [ebx+0x4d4c],edx
and    eax,0xffffff
mov    DWORD PTR [ebx+0x4d50],ecx
pop    esi
shr    eax,0x8
pop    ebx
ret
.section .note.GNU-stack,"",@progbits
