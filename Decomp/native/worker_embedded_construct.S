.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x482bc0.
.global original_worker_embedded_construct
original_worker_embedded_construct:
    push   ebp
    {load} mov    ebp,esp
    push   0xffffffff
    push   0x9014a3
    mov    eax,fs:[0]
    push   eax
    sub    esp,0x8
    push   esi
    push   edi
    mov    eax,ds:[0xbaabc0]
    {load} xor    eax,ebp
    push   eax
    lea    eax,[ebp-0xc]
    mov    fs:[0],eax
    {load} mov    edi,ecx
    mov    DWORD PTR [ebp-0x14],edi
    mov    DWORD PTR [ebp-0x4],0x0
    lea    ecx,[edi+0x4]
    mov    DWORD PTR [edi],0x9fb588
    call matrix_init
    mov    DWORD PTR [edi+0x34],0x0
    mov    DWORD PTR [edi+0x38],0x0
    mov    DWORD PTR [edi+0x3c],0x0
    mov    DWORD PTR [edi+0x40],0x0
    mov    DWORD PTR [edi+0x44],0x0
    mov    DWORD PTR [edi+0x48],0x0
    mov    DWORD PTR [edi+0x4c],0x0
    mov    DWORD PTR [edi+0x50],0x41200000
    mov    DWORD PTR [edi+0x54],0x0
    mov    DWORD PTR [edi+0x58],0x0
    mov    DWORD PTR [edi+0x5c],0x0
    mov    WORD PTR [edi+0x60],0x1
    mov    DWORD PTR [edi+0x64],0x0
    mov    DWORD PTR [edi+0x68],0x0
    mov    DWORD PTR [edi+0x6c],0x0
    mov    BYTE PTR [ebp-0x4],0x1
    lea    eax,[ebp-0x10]
    mov    DWORD PTR [edi+0x4],0x3f800000
    mov    DWORD PTR [edi+0x8],0x0
    mov    DWORD PTR [edi+0xc],0x0
    mov    DWORD PTR [edi+0x10],0x0
    mov    DWORD PTR [edi+0x14],0x3f800000
    mov    DWORD PTR [edi+0x18],0x0
    mov    DWORD PTR [edi+0x1c],0x0
    mov    DWORD PTR [edi+0x20],0x0
    mov    DWORD PTR [edi+0x24],0x3f800000
    mov    DWORD PTR [edi+0x28],0x0
    mov    DWORD PTR [edi+0x2c],0x0
    mov    DWORD PTR [edi+0x30],0x0
    mov    ecx,DWORD PTR ds:[0xc0d424]
    push   eax
    mov    DWORD PTR [ebp-0x10],edi
    lea    ecx,[ecx+0x4]
    call vector_append
    {load} mov    eax,edi
    mov    ecx,DWORD PTR [ebp-0xc]
    mov    DWORD PTR fs:[0],ecx
    pop    ecx
    pop    edi
    pop    esi
    {load} mov    esp,ebp
    pop    ebp
    ret
.equ matrix_init,0x422650
.equ vector_append,0x42c2a0
.section .note.GNU-stack,"",@progbits
