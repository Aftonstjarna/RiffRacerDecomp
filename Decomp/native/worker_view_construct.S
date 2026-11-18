.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence; Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x454790. Not high-level recovery.
.global original_worker_view_construct
.equ matrix_construct,0x422650
.equ sine_bridge,0x41f4d0
.equ cosine_bridge,0x41f4a0
original_worker_view_construct:
    push   ebp
    {load} mov    ebp,esp
    push   0xffffffff
    push   0x90005f
    mov    eax,fs:0x0
    push   eax
    sub    esp,0x8
    push   esi
    push   edi
    mov    eax,DWORD PTR [0xbaabc0]
    {load} xor    eax,ebp
    push   eax
    lea    eax,[ebp-0xc]
    mov    fs:0x0,eax
    {load} mov    edi,ecx
    mov    DWORD PTR [ebp-0x14],edi
    cmp    DWORD PTR [ebp+0x8],0x0
    mov    DWORD PTR [ebp-0x10],0x0
    je L4547f1
    mov    DWORD PTR [edi],0x9fa5a0
    mov    DWORD PTR [edi+0xf4],0xba20bc
    mov    DWORD PTR [edi+0xf8],0x0
    mov    DWORD PTR [ebp-0x4],0x0
    mov    DWORD PTR [ebp-0x10],0x1
L4547f1:
    mov    eax,DWORD PTR [edi]
    lea    ecx,[edi+0x44]
    mov    eax,DWORD PTR [eax+0x4]
    mov    DWORD PTR [edi+eax*1],0x9fa59c
    mov    DWORD PTR [edi+0x8],0x3dcccccd
    mov    DWORD PTR [edi+0xc],0x44480000
    mov    DWORD PTR [edi+0x10],0x0
    mov    DWORD PTR [edi+0x14],0x0
    mov    DWORD PTR [edi+0x18],0x0
    mov    DWORD PTR [edi+0x1c],0x0
    mov    DWORD PTR [edi+0x20],0x0
    mov    DWORD PTR [edi+0x24],0x0
    mov    DWORD PTR [edi+0x28],0x0
    mov    DWORD PTR [edi+0x2c],0x0
    mov    DWORD PTR [edi+0x30],0x0
    mov    DWORD PTR [edi+0x34],0x0
    mov    DWORD PTR [edi+0x38],0x0
    mov    DWORD PTR [edi+0x3c],0x0
    call matrix_construct
    lea    ecx,[edi+0x74]
    call matrix_construct
    lea    ecx,[edi+0xa4]
    call matrix_construct
    mov    DWORD PTR [edi+0xe0],0x42700000
    mov    DWORD PTR [edi+0xe4],0x42700000
    mov    DWORD PTR [edi+0xe8],0x3f800000
    mov    BYTE PTR [edi+0xec],0x0
    mov    DWORD PTR [edi+0xf0],0x3f800000
    mov    DWORD PTR [edi+0x44],0x3f800000
    mov    DWORD PTR [edi+0x48],0x0
    mov    DWORD PTR [edi+0x4c],0x0
    mov    DWORD PTR [edi+0x50],0x0
    mov    DWORD PTR [edi+0x54],0x3f800000
    mov    DWORD PTR [edi+0x58],0x0
    mov    DWORD PTR [edi+0x5c],0x0
    mov    DWORD PTR [edi+0x60],0x0
    mov    DWORD PTR [edi+0x64],0x3f800000
    push   ecx
    mov    DWORD PTR [edi+0x68],0x0
    mov    DWORD PTR [edi+0x6c],0x0
    mov    DWORD PTR [edi+0x70],0x0
    mov    DWORD PTR [edi+0xd4],0x42700000
    mov    DWORD PTR [esp],0x3f060a92
    call sine_bridge
    fstp   DWORD PTR [edi+0xd8]
    mov    DWORD PTR [esp],0x3f060a92
    call cosine_bridge
    fstp   DWORD PTR [edi+0xdc]
    mov    ecx,DWORD PTR [0xc0d408]
    add    esp,0x4
    mov    eax,DWORD PTR [ecx]
    push   0x0
    call   DWORD PTR [eax+0xc]
    test   eax,eax
    {load} mov    eax,edi
    jne L45495c
    mov    DWORD PTR [edi+0x4],0x3fe38e39
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:0x0,ecx
    pop    ecx
    pop    edi
    pop    esi
    {load} mov    esp,ebp
    pop    ebp
    ret    0x4
L45495c:
    mov    DWORD PTR [edi+0x4],0x3faaaaab
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:0x0,ecx
    pop    ecx
    pop    edi
    pop    esi
    {load} mov    esp,ebp
    pop    ebp
    ret    0x4
