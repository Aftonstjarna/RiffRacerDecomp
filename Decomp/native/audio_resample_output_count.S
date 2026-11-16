.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x5909e0,0x590a51); both returns and the complete loop included.
# ECX=state, EDX=signed input count; EAX=result. No calls or static data.
.global original_audio_resample_output_count
original_audio_resample_output_count:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push ebx
 push esi
 mov.s esi,edx
 mov ebx,0x4000
 mov.s edx,ecx
 xor.s ecx,ecx
 mov eax,DWORD PTR [edx+0x4cec]
 mov DWORD PTR [ebp-8],eax
 test esi,esi
 jg .Lpositive
 pop esi
 xor.s eax,eax
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.Lpositive:
 mov edx,DWORD PTR [edx+0x4ba0]
 mov DWORD PTR [ebp-0xc],edx
 push edi
.Lloop:
 cmp.s esi,eax
 mov.s edi,esi
 cmovg edi,eax
 imul edx,edi
 sub.s esi,edi
 add.s ebx,edx
 mov.s eax,ebx
 cdq
 and edx,0x7fff
 add.s eax,edx
 mov edx,DWORD PTR [ebp-0xc]
 sar eax,0xf
 add.s ecx,eax
 mov DWORD PTR [ebp-4],ecx
 imul ecx,eax,0xffff8000
 mov eax,DWORD PTR [ebp-8]
 add.s ebx,ecx
 mov ecx,DWORD PTR [ebp-4]
 test esi,esi
 jg .Lloop
 pop edi
 pop esi
 mov.s eax,ecx
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
