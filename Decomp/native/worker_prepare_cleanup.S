# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x498f50.
.intel_syntax noprefix
.code32
.text
.global original_worker_prepare_cleanup
.equ helper_collect,0x492610
.equ helper_flush,0x492730
original_worker_prepare_cleanup:
 push ebp
 mov.s ebp,esp
 push ecx
 push ebx
 push esi
 push edi
 mov.s edi,ecx
 mov DWORD PTR [ebp-4],0
 cmp BYTE PTR [edi+0xd1],0
 je .L498fb5
 mov eax,DWORD PTR [edi+0xcc]
 mov esi,DWORD PTR [0x92d124]
 push -1
 push DWORD PTR [edi+0xc8]
 mov DWORD PTR [ebp-4],eax
 call esi
 push DWORD PTR [edi+0xc0]
 call DWORD PTR [0x92d120]
 push -1
 push DWORD PTR [edi+0xc4]
 call esi
 push DWORD PTR [edi+0xc8]
 call DWORD PTR [0x92d104]
 mov DWORD PTR [edi+0xcc],0
 mov BYTE PTR [edi+0xd1],0
.L498fb5:
 mov BYTE PTR [edi+0x29d5],1
 mov esi,2
 mov BYTE PTR [edi+0x2b81],1
.L498fc8:
 mov.s ecx,edi
 call helper_collect
 push 1
 mov.s ecx,edi
 call helper_flush
 dec esi
 jne .L498fc8
 mov edx,DWORD PTR [0xbfcc70]
 xor.s ecx,ecx
 mov eax,DWORD PTR [edx+4]
 sub eax,DWORD PTR [edx]
 sar eax,2
 test.s eax,eax
 je .L499006
 nop
.L498ff0:
 mov eax,DWORD PTR [edx]
 mov eax,DWORD PTR [eax+ecx*4]
 inc ecx
 mov BYTE PTR [eax+0x2b],1
 mov eax,DWORD PTR [edx+4]
 sub eax,DWORD PTR [edx]
 sar eax,2
 cmp.s ecx,eax
 jb .L498ff0
.L499006:
 mov eax,DWORD PTR [edi+0x30]
 mov DWORD PTR [edi+0x34],eax
 mov ebx,DWORD PTR [edi+0x64]
 mov esi,DWORD PTR [edi+0x60]
 cmp.s esi,ebx
 je .L499035
.L499016:
 mov edx,DWORD PTR [esi]
 test.s edx,edx
 je .L49902e
 mov eax,DWORD PTR [edx]
 mov ecx,DWORD PTR [eax+4]
 add.s ecx,edx
 dec DWORD PTR [ecx+4]
 jne .L49902e
 mov eax,DWORD PTR [ecx]
 push 1
 call DWORD PTR [eax]
.L49902e:
 add esi,0x18
 cmp.s esi,ebx
 jne .L499016
.L499035:
 mov eax,DWORD PTR [edi+0x60]
 mov DWORD PTR [edi+0x64],eax
 mov eax,DWORD PTR [edi+0x78]
 mov DWORD PTR [edi+0x7c],eax
 mov eax,DWORD PTR [edi+0x84]
 mov DWORD PTR [edi+0x88],eax
 mov eax,DWORD PTR [ebp-4]
 test.s eax,eax
 je .L499076
 cmp BYTE PTR [edi+0xd1],0
 jne .L499076
 push DWORD PTR [edi+0xc0]
 mov BYTE PTR [edi+0xd1],1
 mov DWORD PTR [edi+0xcc],eax
 call DWORD PTR [0x92d120]
.L499076:
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
