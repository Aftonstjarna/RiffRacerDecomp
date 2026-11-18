# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x499120.
.intel_syntax noprefix
.code32
.text
.global original_worker_queue_record_dispatch
.equ copy_bytes,0x8f8d66
.equ append_record,0x4295d0
original_worker_queue_record_dispatch:
 push ebp
 mov.s ebp,esp
 sub esp,0xc
 push edi
 mov.s edi,ecx
 cmp BYTE PTR [edi+0xd1],0
 jne done
 mov eax,DWORD PTR [edi+0x2cd8]
 mov edx,DWORD PTR [ebp+0xc]
 push ebx
 push esi
 lea eax,[eax+eax*2]
 lea ebx,[edi+eax*4]
 mov.s eax,edx
 lea esi,[eax+1]
length_loop:
 mov cl,BYTE PTR [eax]
 inc eax
 test cl,cl
 jne length_loop
 sub.s eax,esi
 mov esi,DWORD PTR [ebx+0x2c9c]
 lea ecx,[eax+1]
 mov eax,DWORD PTR [ebx+0x2ca0]
 push ecx
 add.s esi,eax
 add.s eax,ecx
 push edx
 push esi
 mov DWORD PTR [ebx+0x2ca0],eax
 call copy_bytes
 mov eax,DWORD PTR [ebp+8]
 add esp,0xc
 mov DWORD PTR [ebp-0xc],eax
 mov eax,DWORD PTR [ebp+0x10]
 mov DWORD PTR [ebp-8],eax
 lea eax,[ebp-0xc]
 push eax
 mov eax,DWORD PTR [ebp+0x14]
 mov DWORD PTR [ebp-4],esi
 lea eax,[eax+eax*2]
 lea eax,[eax+0x1e]
 lea ecx,[edi+eax*4]
 call append_record
 pop esi
 pop ebx
done:
 pop edi
 mov.s esp,ebp
 pop ebp
 ret 0x10
.section .note.GNU-stack,"",@progbits
