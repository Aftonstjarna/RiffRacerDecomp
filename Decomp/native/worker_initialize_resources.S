.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x43f480.
.global original_worker_initialize_resources
original_worker_initialize_resources:
    push ebp
    {load} mov ebp,esp
    and esp,0xfffffff8
    push 0xffffffff
    push 0x8fefb8
    mov eax,fs:[0]
    push eax
    sub esp,0x28
    push ebx
    push esi
    push edi
    mov eax,[0xbaabc0]
    {load} xor eax,esp
    push eax
    lea eax,[esp+0x38]
    mov fs:[0],eax
    {load} mov edi,ecx
    call target_417540
    push 0x400
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_417150
    push 0x200
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_4170c0
    push 0x200
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_4171e0
    push 0x20
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_417270
    push 0x20
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_417300
    push 0x20
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_417390
    push 0x140
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_417420
    push 0x400
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_4174b0
    push 0x28
    lea ecx,[eax+0x4]
    call target_440cc0
    call target_4176f0
    push 0x200
    lea ecx,[eax+0x4]
    call target_440cc0
    mov esi,DWORD PTR [0xc0d404]
    mov ebx,DWORD PTR [0x92d4b4]
    test esi,esi
    jne .L43f598
    push 0x10
    call ebx
    {load} mov esi,eax
    add esp,0x4
    test esi,esi
    je .L43f590
    mov DWORD PTR [esi],0x0
    mov DWORD PTR [esi+0x4],0x0
    mov DWORD PTR [esi+0x8],0x0
    mov DWORD PTR [esi+0xc],0x0
    jmp .L43f592
.L43f590:
    {load} xor esi,esi
.L43f592:
    mov DWORD PTR [0xc0d404],esi
.L43f598:
    mov ecx,DWORD PTR [esi+0x8]
    mov eax,0x2aaaaaab
    sub ecx,DWORD PTR [esi]
    imul ecx
    sar edx,1
    {load} mov eax,edx
    shr eax,0x1f
    {load} add eax,edx
    cmp eax,0x20
    jae .L43f5bb
    push 0x20
    {load} mov ecx,esi
    call target_41da10
.L43f5bb:
    mov ecx,DWORD PTR [0xc0d408]
    lea edx,[esp+0x24]
    movaps xmm0,XMMWORD PTR [0xa07050]
    push 0x0
    push edx
    mov eax,DWORD PTR [ecx]
    movups XMMWORD PTR [esp+0x2c],xmm0
    call DWORD PTR [eax+0x20]
    mov ecx,DWORD PTR [0xbfbaac]
    push 0x2
    push 0x0
    push 0x1
    sub esp,0x8
    mov DWORD PTR [esp+0x4],0x3e99999a
    mov DWORD PTR [esp],0x0
    call target_4248e0
    lea ecx,[esp+0x18]
    mov DWORD PTR [esp+0x18],0xbf000000
    mov DWORD PTR [esp+0x1c],0xbf333333
    mov DWORD PTR [esp+0x20],0xbf4ccccd
    call target_426d90
    push 0x1d4
    call ebx
    {load} mov esi,eax
    add esp,0x4
    mov DWORD PTR [esp+0x10],esi
    mov DWORD PTR [esp+0x40],0x0
    test esi,esi
    je .L43f65e
    push 0x1
    push 0x0
    push 0x0
    push 0x100
    push 0x0
    push ecx
    {load} mov ecx,esp
    push 0x9f9a4c
    call target_418010
    {load} mov ecx,esi
    call target_4571f0
    {load} mov esi,eax
    jmp .L43f660
.L43f65e:
    {load} xor esi,esi
.L43f660:
    mov DWORD PTR [esp+0x40],0xffffffff
    mov edx,DWORD PTR [edi]
    {load} cmp edx,esi
    je .L43f693
    test edx,edx
    je .L43f684
    mov eax,DWORD PTR [edx]
    mov ecx,DWORD PTR [eax+0x4]
    {load} add ecx,edx
    dec DWORD PTR [ecx+0x4]
    jne .L43f684
    mov eax,DWORD PTR [ecx]
    push 0x1
    call DWORD PTR [eax]
.L43f684:
    mov DWORD PTR [edi],esi
    test esi,esi
    je .L43f693
    mov eax,DWORD PTR [esi]
    mov eax,DWORD PTR [eax+0x4]
    inc DWORD PTR [eax+esi*1+0x4]
.L43f693:
    push 0xfc
    call ebx
    add esp,0x4
    mov DWORD PTR [esp+0x14],eax
    mov DWORD PTR [esp+0x40],0x1
    test eax,eax
    je .L43f6ba
    push 0x1
    {load} mov ecx,eax
    call target_454790
    {load} mov esi,eax
    jmp .L43f6bc
.L43f6ba:
    {load} xor esi,esi
.L43f6bc:
    mov DWORD PTR [esp+0x40],0xffffffff
    mov ebx,DWORD PTR [edi]
    mov edx,DWORD PTR [ebx+0x1ac]
    {load} cmp edx,esi
    je .L43f6f9
    test edx,edx
    je .L43f6e6
    mov eax,DWORD PTR [edx]
    mov ecx,DWORD PTR [eax+0x4]
    {load} add ecx,edx
    dec DWORD PTR [ecx+0x4]
    jne .L43f6e6
    mov eax,DWORD PTR [ecx]
    push 0x1
    call DWORD PTR [eax]
.L43f6e6:
    mov DWORD PTR [ebx+0x1ac],esi
    test esi,esi
    je .L43f6f9
    mov eax,DWORD PTR [esi]
    mov eax,DWORD PTR [eax+0x4]
    inc DWORD PTR [eax+esi*1+0x4]
.L43f6f9:
    mov eax,DWORD PTR [edi]
    push ecx
    mov DWORD PTR [esp],0x3f060a92
    mov esi,DWORD PTR [eax+0x1ac]
    mov DWORD PTR [esi+0xd4],0x42700000
    call target_41f4d0
    fstp DWORD PTR [esi+0xd8]
    mov DWORD PTR [esp],0x3f060a92
    call target_41f4a0
    movq xmm0,QWORD PTR [esp+0x1c]
    add esp,0x4
    mov eax,DWORD PTR [esp+0x20]
    fstp DWORD PTR [esi+0xdc]
    mov esi,DWORD PTR [edi]
    movq QWORD PTR [esi+0x4],xmm0
    mov DWORD PTR [esi+0xc],eax
    lea ecx,[esi+0x4]
    call target_426d90
    mov DWORD PTR [esi+0x10],0x3e99999a
    {load} mov ecx,edi
    mov DWORD PTR [esi+0x14],0x3e99999a
    mov DWORD PTR [esi+0x18],0x3e99999a
    mov DWORD PTR [esi+0x1c],0x3f800000
    mov DWORD PTR [esi+0x20],0x3f19999a
    mov DWORD PTR [esi+0x24],0x3f19999a
    mov DWORD PTR [esi+0x28],0x3f333333
    mov DWORD PTR [esi+0x2c],0x3f800000
    mov DWORD PTR [esi+0x30],0x3f800000
    mov DWORD PTR [esi+0x34],0x3f800000
    mov DWORD PTR [esi+0x38],0x3f800000
    mov DWORD PTR [esi+0x3c],0x3f800000
    mov eax,DWORD PTR [edi]
    mov eax,DWORD PTR [eax+0x1ac]
    mov DWORD PTR [eax+0xc],0x453b8000
    call target_440120
    mov eax,DWORD PTR [edi]
    mov eax,DWORD PTR [eax+0x1ac]
    movdqu xmm0,XMMWORD PTR [eax+0x44]
    movdqu XMMWORD PTR [edi+0xbc],xmm0
    movdqu xmm0,XMMWORD PTR [eax+0x54]
    movdqu XMMWORD PTR [edi+0xcc],xmm0
    movdqu xmm0,XMMWORD PTR [eax+0x64]
    movdqu XMMWORD PTR [edi+0xdc],xmm0
    mov ecx,DWORD PTR [esp+0x38]
    mov DWORD PTR fs:[0],ecx
    pop ecx
    pop edi
    pop esi
    pop ebx
    {load} mov esp,ebp
    pop ebp
    ret 
.equ target_4170c0,0x4170c0
.equ target_417150,0x417150
.equ target_4171e0,0x4171e0
.equ target_417270,0x417270
.equ target_417300,0x417300
.equ target_417390,0x417390
.equ target_417420,0x417420
.equ target_4174b0,0x4174b0
.equ target_417540,0x417540
.equ target_4176f0,0x4176f0
.equ target_418010,0x418010
.equ target_41da10,0x41da10
.equ target_41f4a0,0x41f4a0
.equ target_41f4d0,0x41f4d0
.equ target_4248e0,0x4248e0
.equ target_426d90,0x426d90
.equ target_440120,0x440120
.equ target_440cc0,0x440cc0
.equ target_454790,0x454790
.equ target_4571f0,0x4571f0
