.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x417270.
.global original_worker_resource_singleton_58_f8_get
original_worker_resource_singleton_58_f8_get:
    push ebp
    {load} mov ebp,esp
    push -1
    push 0x8fd7ac
    mov eax,fs:[0]
    push eax
    push ecx
    push esi
    mov eax,[0xbaabc0]
    {load} xor eax,ebp
    push eax
    lea eax,[ebp-0xc]
    mov fs:[0],eax
    mov eax,[0xc0d3f8]
    test eax,eax
    jne .Ldone
    push 0x58
    call DWORD PTR [0x92d4b4]
    {load} mov esi,eax
    add esp,4
    mov [ebp-0x10],esi
    mov DWORD PTR [ebp-4],0
    test esi,esi
    je .Lnull
    push 0xbaac48
    lea ecx,[esi+4]
    mov WORD PTR [esi],0x100
    mov BYTE PTR [esi+2],0x5c
    call target_417810
    mov WORD PTR [esi+0x54],0x100
    mov BYTE PTR [esi+0x56],0x5c
    jmp .Lstore
.Lnull:
    {load} xor esi,esi
.Lstore:
    mov [0xc0d3f8],esi
    {load} mov eax,esi
.Ldone:
    mov ecx,[ebp-0xc]
    mov fs:[0],ecx
    pop ecx
    pop esi
    {load} mov esp,ebp
    pop ebp
    ret
.equ target_417810,0x417810
.section .note.GNU-stack,"",@progbits
