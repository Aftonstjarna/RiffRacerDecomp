.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x5960b0,0x5960ea); sole return 0x5960e9; INT3 padding excluded.
# ECX=table object; no stack arguments; ESI preserved; no calls or static data.
.global original_audio_index_compact_even
original_audio_index_compact_even:
 push esi
 mov.s esi,ecx
 mov ecx,DWORD PTR [esi+0x10]
 cmp ecx,2
 jb .Ldone
 mov eax,DWORD PTR [esi+4]
 add.s eax,eax
 shr ecx,1
 mov DWORD PTR [esi+4],eax
 mov eax,0
 mov DWORD PTR [esi+0x10],ecx
 je .Lproduct
 nop
.Lcopy:
 mov edx,DWORD PTR [esi]
 mov ecx,DWORD PTR [edx+eax*8]
 mov DWORD PTR [edx+eax*4],ecx
 inc eax
 cmp eax,DWORD PTR [esi+0x10]
 jb .Lcopy
.Lproduct:
 mov eax,DWORD PTR [esi+0x10]
 imul eax,DWORD PTR [esi+4]
 mov DWORD PTR [esi+8],eax
.Ldone:
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
