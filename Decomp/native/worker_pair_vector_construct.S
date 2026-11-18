# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42bfd0.
.intel_syntax noprefix
.code32
.text
.global original_worker_pair_vector_construct
.equ reserve_vectors,0x426800
original_worker_pair_vector_construct:
 push ebp
 mov.s ebp,esp
 push -1
 push 0x8fe473
 mov eax,fs:0
 push eax
 push ecx
 push esi
 push edi
 mov eax,DWORD PTR [0xbaabc0]
 xor.s eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov.s esi,ecx
 mov [ebp-0x10],esi
 mov DWORD PTR [esi],0
 mov DWORD PTR [esi+4],0
 mov DWORD PTR [esi+8],0
 mov DWORD PTR [ebp-4],0
 mov DWORD PTR [esi+0xc],0
 mov DWORD PTR [esi+0x10],0
 mov DWORD PTR [esi+0x14],0
 mov BYTE PTR [ebp-4],1
 mov eax,[esi+8]
 sub eax,[esi]
 sar eax,2
 cmp eax,0x10
 jae .Lsecond
 push 0x10
 call reserve_vectors
.Lsecond:
 mov eax,[esi+0x14]
 sub eax,[esi+0xc]
 sar eax,2
 cmp eax,0x10
 jae .Ldone
 push 0x10
 lea ecx,[esi+0xc]
 call reserve_vectors
.Ldone:
 mov.s eax,esi
 mov ecx,[ebp-0xc]
 mov DWORD PTR fs:0,ecx
 pop ecx
 pop edi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret
.section .note.GNU-stack,"",@progbits
