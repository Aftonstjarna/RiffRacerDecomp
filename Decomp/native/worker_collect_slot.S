# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x492610.
.intel_syntax noprefix
.code32
.text
.global original_worker_collect_slot
.equ reset_record,0x4909e0
.equ grow_pointers,0x429ce0
.equ clear_slot,0x490d30
original_worker_collect_slot:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push ebx
 push esi
 push edi
 mov.s edi,ecx
 mov DWORD PTR [ebp-8],edi
 mov al,BYTE PTR [edi+0xd1]
 mov al,BYTE PTR [edi+0xd1]
 mov esi,DWORD PTR [0xbfcc44]
 mov ebx,DWORD PTR [edi+0x2cd0]
 cmp BYTE PTR [esi+0xba0],0
 jne .L64e
 push -1
 push DWORD PTR [esi+ebx*4+0x460]
 call DWORD PTR [0x92d124]
.L64e:
 mov eax,DWORD PTR [esi+ebx*4+0x4d0]
 lea ecx,[edi+0x2944]
 mov DWORD PTR [ebp-0xc],eax
 xor.s ebx,ebx
 mov al,BYTE PTR [edi+0xd1]
 imul eax,DWORD PTR [edi+0x2cd0],0x1ac
 add.s ecx,eax
 mov DWORD PTR [edi+0x2ccc],ecx
 mov eax,DWORD PTR [ecx+4]
 sub eax,DWORD PTR [ecx]
 sar eax,2
 test.s eax,eax
 je .L70c
 lea esi,[edi+0x2938]
 mov.s edi,edi
.L690:
 mov eax,DWORD PTR [edi+0x2ccc]
 mov eax,DWORD PTR [eax]
 mov edi,DWORD PTR [eax+ebx*4]
 mov.s ecx,edi
 mov DWORD PTR [ebp-4],edi
 call reset_record
 mov eax,DWORD PTR [esi+4]
 lea ecx,[ebp-4]
 cmp.s ecx,eax
 jae .L6dc
 mov ecx,DWORD PTR [esi]
 lea edx,[ebp-4]
 cmp.s ecx,edx
 ja .L6dc
 mov.s edi,edx
 sub.s edi,ecx
 sar edi,2
 cmp eax,DWORD PTR [esi+8]
 jne .L6cc
 push ecx
 mov.s ecx,esi
 call grow_pointers
.L6cc:
 mov ecx,DWORD PTR [esi+4]
 test.s ecx,ecx
 je .L6f2
 mov eax,DWORD PTR [esi]
 mov eax,DWORD PTR [eax+edi*4]
 mov DWORD PTR [ecx],eax
 jmp .L6f2
.L6dc:
 cmp eax,DWORD PTR [esi+8]
 jne .L6e9
 push ecx
 mov.s ecx,esi
 call grow_pointers
.L6e9:
 mov eax,DWORD PTR [esi+4]
 test.s eax,eax
 je .L6f2
 mov DWORD PTR [eax],edi
.L6f2:
 mov edi,DWORD PTR [ebp-8]
 inc ebx
 add DWORD PTR [esi+4],4
 mov ecx,DWORD PTR [edi+0x2ccc]
 mov edx,DWORD PTR [ecx+4]
 sub edx,DWORD PTR [ecx]
 sar edx,2
 cmp.s ebx,edx
 jb .L690
.L70c:
 mov ecx,DWORD PTR [edi+0x2ccc]
 call clear_slot
 mov eax,DWORD PTR [ebp-0xc]
 pop edi
 pop esi
 pop ebx
 mov.s esp,ebp
 pop ebp
 ret
