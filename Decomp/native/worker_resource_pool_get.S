.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x417150.
.global original_worker_resource_pool_get
original_worker_resource_pool_get:
 push ebp
 {load} mov ebp,esp
 push -1
 push 0x8fd7ac
 mov eax,fs:0
 push eax
 push ecx
 push esi
 mov eax, dword ptr [0xbaabc0]
 {load} xor eax,ebp
 push eax
 lea eax,[ebp-0xc]
 mov fs:0,eax
 mov eax, dword ptr [0xc0d3f4]
 test eax,eax
 jne .Ldone
 push 0x58
 call dword ptr [0x92d4b4]
 {load} mov esi,eax
 add esp,4
 mov dword ptr [ebp-0x10],esi
 mov dword ptr [ebp-4],0
 test esi,esi
 je .Lnull
 push 0xbaac34
 lea ecx,[esi+4]
 mov word ptr [esi],0x100
 mov byte ptr [esi+2],0x5c
 call resource_construct
 mov word ptr [esi+0x54],0x100
 mov byte ptr [esi+0x56],0x5c
 jmp .Lstore
.Lnull:
 {load} xor esi,esi
.Lstore:
 mov dword ptr [0xc0d3f4],esi
 {load} mov eax,esi
.Ldone:
 mov ecx,dword ptr [ebp-0xc]
 mov dword ptr fs:0,ecx
 pop ecx
 pop esi
 {load} mov esp,ebp
 pop ebp
 ret
.equ resource_construct,0x417810
.section .note.GNU-stack,"",@progbits
