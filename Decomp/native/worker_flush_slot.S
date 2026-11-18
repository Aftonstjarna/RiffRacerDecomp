# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x492730.
.intel_syntax noprefix
.code32
.text
.global original_worker_flush_slot
.equ helper_reset,0x49a940
original_worker_flush_slot:
 push ebp
 mov.s ebp,esp
 push ecx
 mov eax,DWORD PTR [ecx+0x2ccc]
 push ebx
 mov bl,BYTE PTR [ebp+8]
 test.s bl,bl
 mov BYTE PTR [eax+0x91],bl
 mov.s ebx,ecx
 mov edx,DWORD PTR [ecx+0x2ccc]
 movzx eax,BYTE PTR [ecx+0x2d11]
 mov BYTE PTR [edx+0x92],al
 mov edx,DWORD PTR [ecx+0x2ccc]
 movzx eax,BYTE PTR [ecx+0x2d12]
 mov BYTE PTR [edx+0x93],al
 je .L492790
 mov eax,DWORD PTR [ebx+0x30]
 lea ecx,[ebx+0x60]
 mov DWORD PTR [ebx+0x34],eax
 call helper_reset
 mov eax,DWORD PTR [ebx+0x78]
 mov DWORD PTR [ebx+0x7c],eax
 mov eax,DWORD PTR [ebx+0x84]
 mov DWORD PTR [ebx+0x88],eax
.L492790:
 mov eax,DWORD PTR [ebx+0x2ccc]
 push esi
 mov esi,DWORD PTR [0xbfcc44]
 push edi
 mov edi,DWORD PTR [ebx+0x2cd0]
 push DWORD PTR [esi+edi*4+0x460]
 mov DWORD PTR [esi+edi*4+0x468],eax
 call DWORD PTR [0x92d104]
 push DWORD PTR [esi+edi*4+0x458]
 call DWORD PTR [0x92d120]
 inc DWORD PTR [ebx+0x2cd0]
 cmp DWORD PTR [ebx+0x2cd0],2
 jb .L4927de
 mov DWORD PTR [ebx+0x2cd0],0
.L4927de:
 mov esi,DWORD PTR [0xbfcc74]
 mov DWORD PTR [ebx+0x2ccc],0
 inc DWORD PTR [esi+0x248]
 cmp DWORD PTR [esi+0x248],3
 jb .L492807
 mov DWORD PTR [esi+0x248],0
.L492807:
 mov eax,DWORD PTR [esi]
 mov.s ecx,esi
 call DWORD PTR [eax+0x44]
 mov eax,DWORD PTR [esi+0x248]
 inc DWORD PTR [ebx+0x2cd8]
 cmp DWORD PTR [ebx+0x2cd8],3
 pop edi
 mov DWORD PTR [ebx+0x2cd4],eax
 pop esi
 jb .L492835
 mov DWORD PTR [ebx+0x2cd8],0
.L492835:
 mov eax,DWORD PTR [ebx+0x2cd8]
 add eax,0x3b8
 lea eax,[eax+eax*2]
 mov DWORD PTR [ebx+eax*4],0
 inc DWORD PTR [ebx+0x28]
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret 4
