.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x492860.
.equ counter_iat,0x92d0f4
.equ convert_double,0x8f92ef
.equ convert_integer,0x8f9131
.equ collect_slot,0x492610
.equ update_worker,0x4987c0
.equ flush_slot,0x492730
.equ frequency,0xc00b50
.equ unsigned_table,0xa071b0
.equ divisor,0xa0680c
.equ global_flag,0xbfcbbb
.global original_worker_frame_step
original_worker_frame_step:
 push ebp
 mov.s ebp,esp
 sub esp,0x24
 push ebx
 push esi
 mov.s esi,ecx
 push edi
 mov [ebp-4],esi
 cmp BYTE PTR [esi+0xd1],0
 je .Lactive
 mov eax,1
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.Lactive:
 mov edi,DWORD PTR [counter_iat]
 lea eax,[ebp-0x10]
 push eax
 call edi
 mov edx,[ebp-0xc]
 mov ecx,[ebp-0x10]
 call convert_double
 divsd xmm0,QWORD PTR [frequency]
 call convert_integer
 mov.s ecx,esi
 mov.s ebx,eax
 call collect_slot
 test eax,eax
 mov ecx,1
 cmove eax,ecx
 mov [esi+0x24],eax
 lea eax,[ebp-0x18]
 push eax
 call edi
 mov edx,[ebp-0x14]
 mov ecx,[ebp-0x18]
 call convert_double
 divsd xmm0,QWORD PTR [frequency]
 call convert_integer
 mov ecx,[ebp-4]
 mov.s esi,eax
 push 0
 call update_worker
 lea eax,[ebp-0x20]
 push eax
 call edi
 mov edx,[ebp-0x1c]
 mov ecx,[ebp-0x20]
 call convert_double
 divsd xmm0,QWORD PTR [frequency]
 call convert_integer
 mov edi,[ebp-4]
 mov.s ecx,eax
 push 0
 sub ecx,[edi+0x98]
 sub.s ecx,esi
 mov [edi+0x98],eax
 add.s ecx,ebx
 movd xmm0,ecx
 cvtdq2pd xmm0,xmm0
 shr ecx,0x1f
 addsd xmm0,QWORD PTR [ecx*8+unsigned_table]
 mov.s ecx,edi
 cvtpd2ps xmm0,xmm0
 divss xmm0,DWORD PTR [divisor]
 movss DWORD PTR [edi+0x9c],xmm0
 call flush_slot
 mov DWORD PTR [edi+0x90],4
 mov eax,[edi+0xc]
 shr eax,3
 and al,1
 mov BYTE PTR [global_flag],al
 mov eax,[edi+0x24]
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
