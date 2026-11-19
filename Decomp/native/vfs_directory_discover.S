# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x55e130.
.intel_syntax noprefix
.code32
.text
.global original_vfs_directory_discover
original_vfs_directory_discover:
    push   ebp
    {load} mov    ebp,esp
    push   0xffffffff
    push   0x906e28
    mov    eax,fs:0x0
    push   eax
    sub    esp,0x2bc
    mov    eax,ds:0xbaabc0
    {load} xor    eax,ebp
    mov    DWORD PTR [ebp-0x10],eax
    push   ebx
    push   esi
    push   edi
    push   eax
    lea    eax,[ebp-0xc]
    mov    fs:0x0,eax
    {load} mov    ebx,edx
    mov    DWORD PTR [ebp-0x2bc],ebx
    {load} mov    edi,ecx
    mov    DWORD PTR [ebp-0x2c4],edi
    {load} xor    eax,eax
    mov    DWORD PTR [ebp-0x30],0x7
    push   0xffffffff
    push   eax
    push   edi
    lea    ecx,[ebp-0x44]
    mov    DWORD PTR [ebp-0x34],0x0
    mov    WORD PTR [ebp-0x44],ax
    call target_44fb30
    {load} xor    ecx,ecx
    mov    DWORD PTR [ebp-0x4],0x0
    cmp    WORD PTR ds:0xa00998,cx
    mov    eax,0x3
    cmove  eax,ecx
    lea    ecx,[ebp-0x44]
    push   eax
    push   0xa00998
    call target_536160
    push   0x2a
    push   ecx
    lea    ecx,[ebp-0x44]
    call target_44f8f0
    {load} xor    ecx,ecx
    mov    eax,0x4
    cmp    WORD PTR ds:0xa00908,cx
    cmove  eax,ecx
    lea    ecx,[ebp-0x44]
    push   eax
    push   0xa00908
    call target_536160
    cmp    DWORD PTR [ebp-0x30],0x8
    lea    ecx,[ebp-0x2b0]
    lea    eax,[ebp-0x44]
    cmovae eax,DWORD PTR [ebp-0x44]
    push   ecx
    push   eax
    call   DWORD PTR ds:0x92d078
    mov    esi,DWORD PTR ds:0x92d4b0
    mov    DWORD PTR [ebp-0x2b8],eax
    cmp    eax,0xffffffff
    je L55e4cd
    {load} mov    edi,eax
    {load} mov    edi,edi
L55e210:
    test   BYTE PTR [ebp-0x2b0],0x10
    jne L55e49c
    lea    eax,[ebp-0x284]
    push   0x2e
    push   eax
    call   DWORD PTR ds:0x92d340
    {load} mov    edx,eax
    add    esp,0x8
    test   edx,edx
    je L55e49c
    {load} xor    eax,eax
    lea    ecx,[ebp-0x284]
    mov    WORD PTR [edx],ax
    lea    edi,[ecx+0x2]
L55e247:
    mov    ax,WORD PTR [ecx]
    add    ecx,0x2
    test   ax,ax
    jne L55e247
    {load} sub    ecx,edi
    sar    ecx,1
    cmp    ecx,0x3
    jb L55e496
    sub    ecx,0x3
    {load} mov    eax,ecx
    neg    eax
    lea    ebx,[edx+eax*2]
    movzx  eax,WORD PTR [ebx]
    test   ax,ax
    jne L55e2f7
    mov    edx,DWORD PTR [ebp-0x2c4]
    lea    eax,[ebp-0x284]
    push   eax
    lea    ecx,[ebp-0x5c]
    mov    DWORD PTR [ebp-0x2c0],0xffffffff
    call target_561d40
    add    esp,0x4
    push   eax
    lea    edx,[ebp-0x2c0]
    lea    ecx,[ebp-0x2c]
    call target_561e30
    add    esp,0x4
    mov    ebx,DWORD PTR [ebp-0x2bc]
    {load} mov    ecx,ebx
    push   eax
    mov    BYTE PTR [ebp-0x4],0x2
    call target_5614e0
L55e2bb:
    cmp    DWORD PTR [ebp-0x14],0x8
    jb L55e2c9
    push   DWORD PTR [ebp-0x28]
    call   esi
    add    esp,0x4
L55e2c9:
    {load} xor    eax,eax
    mov    DWORD PTR [ebp-0x14],0x7
    mov    BYTE PTR [ebp-0x4],al
    cmp    DWORD PTR [ebp-0x48],0x8
    mov    DWORD PTR [ebp-0x18],0x0
    mov    WORD PTR [ebp-0x28],ax
    jb L55e496
    push   DWORD PTR [ebp-0x5c]
    call   esi
    add    esp,0x4
    jmp L55e496
L55e2f7:
    cmp    ecx,0x7
    ja L55e490
    lea    esi,[ecx*4-0x4]
    {load} xor    edi,edi
    {disp32} lea    esp,[esp+0x0]
L55e310:
    movzx  eax,ax
    push   eax
    call   DWORD PTR ds:0x92d4d4
    {load} mov    edx,eax
    add    esp,0x4
    lea    ecx,[edx-0x30]
    cmp    ecx,0x9
    ja L55e32c
    lea    eax,[edx-0x30]
    jmp L55e33b
L55e32c:
    lea    eax,[edx-0x61]
    cmp    eax,0x5
    ja L55e48a
    lea    eax,[edx-0x57]
L55e33b:
    {load} mov    ecx,esi
    add    ebx,0x2
    shl    eax,cl
    sub    esi,0x4
    {load} or     edi,eax
    mov    DWORD PTR [ebp-0x2c0],edi
    movzx  eax,WORD PTR [ebx]
    test   ax,ax
    jne L55e310
    test   edi,edi
    je L55e48a
    mov    esi,DWORD PTR [ebp-0x2bc]
    {load} xor    ebx,ebx
    mov    BYTE PTR [ebp-0x2b1],al
    mov    eax,0x92492493
    mov    ecx,DWORD PTR [esi]
    mov    esi,DWORD PTR [esi+0x4]
    {load} sub    esi,ecx
    imul   esi
    {load} add    edx,esi
    sar    edx,0x4
    {load} mov    esi,edx
    shr    esi,0x1f
    {load} add    esi,edx
    je L55e437
    {load} xor    eax,eax
    {disp8} lea    ecx,[ecx+0x0]
L55e390:
    cmp    DWORD PTR [eax+ecx*1],edi
    ja L55e3a8
    inc    ebx
    add    eax,0x1c
    {load} cmp    ebx,esi
    jb L55e390
    mov    al,BYTE PTR [ebp-0x2b1]
    jmp L55e439
L55e3a8:
    mov    edi,DWORD PTR [ebp-0x2c4]
    lea    eax,[ebx*8+0x0]
    {load} sub    eax,ebx
    {load} mov    edx,edi
    lea    esi,[ecx+eax*4]
    lea    eax,[ebp-0x284]
    push   eax
    lea    ecx,[ebp-0x5c]
    call target_561d40
    add    esp,0x4
    push   eax
    lea    edx,[ebp-0x2c0]
    lea    ecx,[ebp-0x2c]
    call target_561e30
    add    esp,0x4
    mov    ebx,DWORD PTR [ebp-0x2bc]
    {load} mov    ecx,ebx
    push   eax
    push   esi
    lea    eax,[ebp-0x2c8]
    mov    BYTE PTR [ebp-0x4],0x4
    push   eax
    call target_561ff0
    cmp    DWORD PTR [ebp-0x14],0x8
    mov    esi,DWORD PTR ds:0x92d4b0
    jb L55e40e
    push   DWORD PTR [ebp-0x28]
    call   esi
    add    esp,0x4
L55e40e:
    {load} xor    eax,eax
    mov    DWORD PTR [ebp-0x14],0x7
    mov    BYTE PTR [ebp-0x4],al
    cmp    DWORD PTR [ebp-0x48],0x8
    mov    DWORD PTR [ebp-0x18],0x0
    mov    WORD PTR [ebp-0x28],ax
    jb L55e433
    push   DWORD PTR [ebp-0x5c]
    call   esi
    add    esp,0x4
L55e433:
    mov    al,0x1
    jmp L55e445
L55e437:
    {load} mov    al,bl
L55e439:
    mov    edi,DWORD PTR [ebp-0x2c4]
    mov    ebx,DWORD PTR [ebp-0x2bc]
L55e445:
    test   al,al
    jne L55e4f7
    lea    eax,[ebp-0x284]
    {load} mov    edx,edi
    push   eax
    lea    ecx,[ebp-0x5c]
    call target_561d40
    add    esp,0x4
    push   eax
    lea    edx,[ebp-0x2c0]
    lea    ecx,[ebp-0x2c]
    call target_561e30
    add    esp,0x4
    push   eax
    {load} mov    ecx,ebx
    mov    BYTE PTR [ebp-0x4],0x6
    call target_5614e0
    mov    esi,DWORD PTR ds:0x92d4b0
    jmp L55e2bb
L55e48a:
    mov    esi,DWORD PTR ds:0x92d4b0
L55e490:
    mov    ebx,DWORD PTR [ebp-0x2bc]
L55e496:
    mov    edi,DWORD PTR [ebp-0x2b8]
L55e49c:
    lea    eax,[ebp-0x2b0]
    push   eax
    push   edi
    call   DWORD PTR ds:0x92d068
    test   eax,eax
    jne L55e210
    push   edi
    call   DWORD PTR ds:0x92d06c
    mov    eax,DWORD PTR [ebx+0x4]
    cmp    DWORD PTR [ebx],eax
    je L55e4cd
    cmp    DWORD PTR [eax-0x1c],0xffffffff
    jne L55e4cd
    mov    DWORD PTR [eax-0x1c],0x0
L55e4cd:
    cmp    DWORD PTR [ebp-0x30],0x8
    jb L55e4db
    push   DWORD PTR [ebp-0x44]
    call   esi
    add    esp,0x4
L55e4db:
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:0x0,ecx
    pop    ecx
    pop    edi
    pop    esi
    pop    ebx
    mov    ecx,DWORD PTR [ebp-0x10]
    {load} xor    ecx,ebp
    call target_8f8958
    {load} mov    esp,ebp
    pop    ebp
    ret
L55e4f7:
    mov    esi,DWORD PTR ds:0x92d4b0
    jmp L55e496
.equ target_44f8f0,0x44f8f0
.equ target_44fb30,0x44fb30
.equ target_536160,0x536160
.equ target_5614e0,0x5614e0
.equ target_561d40,0x561d40
.equ target_561e30,0x561e30
.equ target_561ff0,0x561ff0
.equ target_8f8958,0x8f8958
.section .note.GNU-stack,"",@progbits
