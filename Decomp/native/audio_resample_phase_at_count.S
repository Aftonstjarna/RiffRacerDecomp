.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x5908d0,0x59090f), sole RET at 0x59090e; INT3 padding excluded.
# ECX=audio state, EDX=signed iteration count, EAX=result.
# Reads state+0x4ba0 and state+0x4cec only when count>0. No calls/static data.
# Preserves ESI/EDI and stack; ECX/EDX/EAX/flags volatile. No stack arguments.
.global original_audio_resample_phase_at_count
original_audio_resample_phase_at_count:
 push esi
 push edi
 mov.s edi,edx
 mov.s eax,ecx
 mov esi,0x4000
 test edi,edi
 jle .Ldone
 mov ecx,DWORD PTR [eax+0x4ba0]
 imul ecx,DWORD PTR [eax+0x4cec]
 {disp8} lea esp,[esp+0]
.Lstep:
 add.s esi,ecx
 mov.s eax,esi
 cdq
 and edx,0x7fff
 add.s eax,edx
 sar eax,0xf
 neg eax
 shl eax,0xf
 add.s esi,eax
 dec edi
 jne .Lstep
.Ldone:
 pop edi
 mov.s eax,esi
 pop esi
 ret
.section .note.GNU-stack,"",@progbits
