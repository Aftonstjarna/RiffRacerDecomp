.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41dcb0.
.global original_worker_record12_copy_construct_range
original_worker_record12_copy_construct_range:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fdbad
 mov eax,DWORD PTR fs:[0]
 push eax
 sub esp,0x18
 push ebx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov DWORD PTR fs:[0],eax
 mov DWORD PTR [ebp-0x10],esp
 {load} mov eax,edx
 mov DWORD PTR [ebp-0x14],eax
 {load} mov ebx,ecx
 mov edi,DWORD PTR [ebp+8]
 mov DWORD PTR [ebp-0x18],edi
 mov DWORD PTR [ebp-4],0
 nop
.Lloop:
 {load} cmp ebx,eax
 je .Ldone
 mov DWORD PTR [ebp-0x20],edi
 mov BYTE PTR [ebp-4],1
 test edi,edi
 je .Lnext
 mov eax,DWORD PTR [ebx]
 mov DWORD PTR [edi],eax
 mov eax,DWORD PTR [ebx+4]
 mov DWORD PTR [ebp-0x1c],eax
 mov DWORD PTR [edi+4],eax
 test eax,eax
 js .Lpointer
 mov esi,DWORD PTR [0xc0d3d8]
 test esi,esi
 jne .Lpool
 push 0x58
 call DWORD PTR [0x92d4b4]
 {load} mov esi,eax
 add esp,4
 mov DWORD PTR [ebp-0x24],esi
 mov BYTE PTR [ebp-4],2
 test esi,esi
 je .Lnull
 push 0xbaac0c
 lea ecx,[esi+4]
 mov WORD PTR [esi],0x100
 mov BYTE PTR [esi+2],0x5c
 call constructor
 mov WORD PTR [esi+0x54],0x100
 mov BYTE PTR [esi+0x56],0x5c
 jmp .Lstore
.Lnull:
 {load} xor esi,esi
.Lstore:
 mov DWORD PTR [0xc0d3d8],esi
.Lpool:
 mov eax,DWORD PTR [esi+4]
 mov ecx,DWORD PTR [ebp-0x1c]
 movsx ecx,WORD PTR [eax+ecx*2]
 mov eax,DWORD PTR [esi+0x28]
 inc DWORD PTR [eax+ecx*8+4]
.Lpointer:
 mov ecx,DWORD PTR [ebx+8]
 mov DWORD PTR [edi+8],ecx
 test ecx,ecx
 je .Lreload
 mov eax,DWORD PTR [ecx+4]
 mov eax,DWORD PTR [eax+4]
 inc DWORD PTR [eax+ecx+8]
.Lreload:
 mov eax,DWORD PTR [ebp-0x14]
.Lnext:
 add edi,0xc
 mov BYTE PTR [ebp-4],0
 mov DWORD PTR [ebp+8],edi
 add ebx,0xc
 jmp .Lloop
# Exception continuation, entered by the original unwind machinery.
 mov esi,DWORD PTR [ebp-0x18]
 mov edi,DWORD PTR [ebp+8]
 {load} cmp esi,edi
 je .Lresume
.Lcleanup:
 {load} mov ecx,esi
 call destroy_one
 add esi,0xc
 {load} cmp esi,edi
 jne .Lcleanup
.Lresume:
 push 0
 push 0
 call unwind_resume
.Ldone:
 {load} mov eax,edi
 mov ecx,DWORD PTR [ebp-0xc]
 mov DWORD PTR fs:[0],ecx
 pop ecx
 pop edi
 pop esi
 pop ebx
 {load} mov esp,ebp
 pop ebp
 ret
.equ constructor,0x417810
.equ destroy_one,0x41dde0
.equ unwind_resume,0x8f8d5a
.section .note.GNU-stack,"",@progbits
