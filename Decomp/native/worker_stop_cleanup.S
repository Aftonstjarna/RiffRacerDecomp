# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x498e00.
.intel_syntax noprefix
.code32
.text
.global original_worker_stop_cleanup
.equ helper_prepare,0x498f50
.equ helper_construct,0x42bfd0
.equ helper_free,0x453580
original_worker_stop_cleanup:
 push ebp
 mov.s ebp,esp
 push 0xffffffff
 push 0x9021bc
 mov eax,fs:[0x0]
 push eax
 sub esp,0xc
 push ebx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:[0x0],eax
 mov.s ebx,ecx
 mov DWORD PTR [ebp-0x18],ebx
 call helper_prepare
 mov BYTE PTR [ebx+0x2d10],0x1
 mov edx,DWORD PTR [0xbfcb48]
 mov DWORD PTR [ebp-0x10],edx
 test edx,edx
 jne .L498e7f
 push 0x18
 call DWORD PTR [0x92d4b4]
 add esp,0x4
 mov DWORD PTR [ebp-0x14],eax
 mov DWORD PTR [ebp-0x4],0x0
 test eax,eax
 je .L498e6d
 mov.s ecx,eax
 call helper_construct
 mov.s edx,eax
 mov DWORD PTR [ebp-0x10],eax
 jmp .L498e72
.L498e6d:
 xor.s edx,edx
 mov DWORD PTR [ebp-0x10],edx
.L498e72:
 mov DWORD PTR [ebp-0x4],0xffffffff
 mov DWORD PTR [0xbfcb48],edx
.L498e7f:
 mov esi,DWORD PTR [edx]
 cmp esi,DWORD PTR [edx+0x4]
 je .L498f29
 mov eax,DWORD PTR [ebp-0x10]
 {disp8} lea ecx,[ecx+0x0]
.L498e90:
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp-0x14],edx
 cmp DWORD PTR [edx+0x1c0],0x0
 jne .L498f05
 mov eax,DWORD PTR [edx+0x1b4]
 xor.s ebx,ebx
 mov ecx,DWORD PTR [edx+0x1b0]
 sub.s eax,ecx
 sar eax,0x2
 test eax,eax
 je .L498f02
.L498eb5:
 mov edi,DWORD PTR [ecx+ebx*4]
 test edi,edi
 je .L498eec
 mov ecx,DWORD PTR [edi+0x10]
 test ecx,ecx
 je .L498ee0
 mov eax,DWORD PTR [ecx+0x4]
 add ecx,0x4
 mov eax,DWORD PTR [eax+0x4]
 add.s ecx,eax
 dec DWORD PTR [ecx+0x4]
 jne .L498ed9
 mov eax,DWORD PTR [ecx]
 push 0x1
 call DWORD PTR [eax]
.L498ed9:
 mov DWORD PTR [edi+0x10],0x0
.L498ee0:
 push edi
 call helper_free
 mov edx,DWORD PTR [ebp-0x14]
 add esp,0x4
.L498eec:
 mov eax,DWORD PTR [edx+0x1b4]
 inc ebx
 mov ecx,DWORD PTR [edx+0x1b0]
 sub.s eax,ecx
 sar eax,0x2
 cmp.s ebx,eax
 jb .L498eb5
.L498f02:
 mov eax,DWORD PTR [ebp-0x10]
.L498f05:
 add esi,0x4
 cmp esi,DWORD PTR [eax+0x4]
 jne .L498e90
 mov eax,DWORD PTR [ebp-0x18]
 mov BYTE PTR [eax+0x2d10],0x0
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:[0x0],ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 
.L498f29:
 mov BYTE PTR [ebx+0x2d10],0x0
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:[0x0],ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 
