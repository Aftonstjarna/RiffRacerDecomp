.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4176f0.
.global original_worker_resource_singleton_d0_get
original_worker_resource_singleton_d0_get:
    push ebp
    {load} mov ebp,esp
    push -1
    push 0x8fd7ac
    mov eax,fs:0x0
    push eax
    push ecx
    push esi
    mov eax,ds:0xbaabc0
    {load} xor eax,ebp
    push eax
    lea eax,[ebp-0xc]
    mov fs:0x0,eax
    mov eax,ds:0xc0d3d0
    test eax,eax
    jne .Ldone
    push 0x58
    call DWORD PTR ds:0x92d4b4
    {load} mov esi,eax
    add esp,4
    mov DWORD PTR [ebp-0x10],esi
    mov DWORD PTR [ebp-4],0
    test esi,esi
    je .Lnull
    push 0xbaac3c
    lea ecx,[esi+4]
    mov WORD PTR [esi],1
    mov BYTE PTR [esi+2],0x2f
    call target_417810
    mov WORD PTR [esi+0x54],1
    mov BYTE PTR [esi+0x56],0x2f
    jmp .Lstore
.Lnull:
    {load} xor esi,esi
.Lstore:
    mov DWORD PTR ds:0xc0d3d0,esi
    {load} mov eax,esi
.Ldone:
    mov ecx,DWORD PTR [ebp-0xc]
    mov DWORD PTR fs:0x0,ecx
    pop ecx
    pop esi
    {load} mov esp,ebp
    pop ebp
    ret
.equ target_417810,0x417810
.section .note.GNU-stack,"",@progbits
