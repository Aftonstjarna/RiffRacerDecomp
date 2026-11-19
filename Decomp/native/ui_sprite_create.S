.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x422030.
.equ target_4431f0,0x4431f0
.equ target_41f7e0,0x41f7e0
.equ target_41f880,0x41f880
.equ target_41f920,0x41f920
.equ target_4482b0,0x4482b0
.equ target_44b9a0,0x44b9a0
.global original_ui_sprite_create
original_ui_sprite_create:
    push   ebp
    {load} mov    ebp,esp
    push   0xffffffff
    push   0x8fdf74
    mov    eax,fs:[0]
    push   eax
    sub    esp,0x1c
    push   ebx
    push   esi
    push   edi
    mov    eax,[0xbaabc0]
    {load} xor    eax,ebp
    push   eax
    lea    eax,[ebp-0xc]
    mov    fs:[0],eax
    {load} mov    ebx,ecx
    mov    eax,DWORD PTR [ebp+0x8]
    cmp    eax,DWORD PTR [ebx+0x10]
    jb L422067
    mov    edi,DWORD PTR [ebx+0xc]
    jmp L42206d
L422067:
    imul   edi,eax,0x64
    add    edi,DWORD PTR [ebx+0xc]
L42206d:
    push   0x194
    call   DWORD PTR [0x92d4b4]
    {load} mov    ecx,eax
    add    esp,0x4
    mov    DWORD PTR [ebp+0x8],ecx
    mov    DWORD PTR [ebp-0x4],0x0
    test   ecx,ecx
    je L4220c9
    movss  xmm0,DWORD PTR [edi+0xc]
    mov    eax,DWORD PTR [ebp+0xc]
    push   0x0
    push   DWORD PTR [ebp+0x14]
    sub    esp,0x10
    movss  DWORD PTR [esp+0xc],xmm0
    movss  xmm0,DWORD PTR [edi+0x8]
    movss  DWORD PTR [esp+0x8],xmm0
    movss  xmm0,DWORD PTR [eax+0x4]
    movss  DWORD PTR [esp+0x4],xmm0
    movss  xmm0,DWORD PTR [eax]
    movss  DWORD PTR [esp],xmm0
    call target_4431f0
    {load} mov    esi,eax
    jmp L4220cb
L4220c9:
    {load} xor    esi,esi
L4220cb:
    lea    eax,[ebx+0x60]
    mov    DWORD PTR [ebp-0x4],0xffffffff
    push   eax
    {load} mov    ecx,esi
    call target_41f7e0
    lea    eax,[ebx+0x68]
    {load} mov    ecx,esi
    push   eax
    call target_41f880
    lea    eax,[ebx+0x70]
    {load} mov    ecx,esi
    push   eax
    call target_41f920
    push   DWORD PTR [ebp+0x10]
    {load} mov    ecx,esi
    call target_4482b0
    and    BYTE PTR [esi+0x174],0xf9
    mov    DWORD PTR [ebp-0x28],0x0
    mov    BYTE PTR [ebp-0x18],0x0
    mov    DWORD PTR [ebp-0x4],0x1
    lea    ecx,[esi+0x184]
    mov    DWORD PTR [ebp-0x14],0x0
    mov    eax,DWORD PTR [ebp-0x14]
    mov    DWORD PTR [ebp-0x20],eax
    mov    DWORD PTR [ebp-0x10],0x0
    mov    eax,DWORD PTR [ebp-0x10]
    mov    DWORD PTR [ebp-0x1c],eax
    lea    eax,[ebp-0x28]
    push   eax
    mov    DWORD PTR [ebp-0x24],edi
    call target_44b9a0
    mov    DWORD PTR [ebp-0x4],0xffffffff
    mov    edx,DWORD PTR [ebp-0x28]
    test   edx,edx
    je L422162
    mov    eax,DWORD PTR [edx]
    mov    ecx,DWORD PTR [eax+0x4]
    {load} add    ecx,edx
    dec    DWORD PTR [ecx+0x4]
    jne L422162
    mov    eax,DWORD PTR [ecx]
    push   0x1
    call   DWORD PTR [eax]
L422162:
    {load} mov    eax,esi
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:[0],ecx
    pop    ecx
    pop    edi
    pop    esi
    pop    ebx
    {load} mov    esp,ebp
    pop    ebp
    ret    0x10
.section .note.GNU-stack,"",@progbits
