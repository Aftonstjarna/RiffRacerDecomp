# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x4f0800,0x4f08f6); full function, following INT3 excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_table_rehash
original_script_table_rehash:
L4f0800:
    push   ebp
L4f0801:
    mov.s    ebp,esp
L4f0803:
    sub    esp,0x78
L4f0806:
    mov    eax,DWORD PTR [0xbaabc0]
L4f080b:
    xor.s    eax,ebp
L4f080d:
    mov    DWORD PTR [ebp-0x4],eax
L4f0810:
    xorps  xmm0,xmm0
L4f0813:
    mov    DWORD PTR [ebp-0x78],ecx
L4f0816:
    push   ebx
L4f0817:
    mov.s    ebx,edx
L4f0819:
    movq   QWORD PTR [ebp-0x10],xmm0
L4f081e:
    push   esi
L4f081f:
    push   edi
L4f0820:
    mov    edi,DWORD PTR [ebp+0x8]
L4f0823:
    lea    edx,[ebp-0x70]
L4f0826:
    mov.s    ecx,ebx
L4f0828:
    mov    DWORD PTR [ebp-0x8],0x0
L4f082f:
    movdqu XMMWORD PTR [ebp-0x70],xmm0
L4f0834:
    movdqu XMMWORD PTR [ebp-0x60],xmm0
L4f0839:
    movdqu XMMWORD PTR [ebp-0x50],xmm0
L4f083e:
    movdqu XMMWORD PTR [ebp-0x40],xmm0
L4f0843:
    movdqu XMMWORD PTR [ebp-0x30],xmm0
L4f0848:
    movdqu XMMWORD PTR [ebp-0x20],xmm0
L4f084d:
    call   0x4f03e0
L4f0852:
    mov.s    esi,eax
L4f0854:
    lea    edx,[ebp-0x70]
L4f0857:
    lea    eax,[ebp-0x74]
L4f085a:
    mov    DWORD PTR [ebp-0x74],esi
L4f085d:
    push   eax
L4f085e:
    mov.s    ecx,ebx
L4f0860:
    call   0x4f0460
L4f0865:
    add    esp,0x4
L4f0868:
    add.s    esi,eax
L4f086a:
    cmp    DWORD PTR [edi+0x4],0x3
L4f086e:
    jne L4f08c1
L4f0870:
    cvttss2si ecx,DWORD PTR [edi]
L4f0874:
    movd   xmm0,ecx
L4f0878:
    cvtdq2ps xmm0,xmm0
L4f087b:
    ucomiss xmm0,DWORD PTR [edi]
L4f087e:
    lahf
L4f087f:
    test   ah,0x44
L4f0882:
    jp L4f08c1
L4f0884:
    lea    eax,[ecx-0x1]
L4f0887:
    cmp    eax,0x3ffffff
L4f088c:
    ja L4f08c1
L4f088e:
    lea    eax,[ecx-0x1]
L4f0891:
    or     ecx,0xffffffff
L4f0894:
    cmp    eax,0x100
L4f0899:
    jb L4f08ad
L4f089b:
    jmp L4f08a0
L4f089d:
    {disp8} lea    ecx,[ecx+0x0]
L4f08a0:
    shr    eax,0x8
L4f08a3:
    add    ecx,0x8
L4f08a6:
    cmp    eax,0x100
L4f08ab:
    jae L4f08a0
L4f08ad:
    movzx  eax,BYTE PTR [eax+0x99a438]
L4f08b4:
    add.s    eax,ecx
L4f08b6:
    inc    DWORD PTR [ebp+eax*4-0x6c]
L4f08ba:
    mov    eax,0x1
L4f08bf:
    jmp L4f08c3
L4f08c1:
    xor.s    eax,eax
L4f08c3:
    add    DWORD PTR [ebp-0x74],eax
L4f08c6:
    lea    edx,[ebp-0x74]
L4f08c9:
    lea    ecx,[ebp-0x70]
L4f08cc:
    call   0x4f0370
L4f08d1:
    mov    ecx,DWORD PTR [ebp-0x78]
L4f08d4:
    sub.s    esi,eax
L4f08d6:
    inc    esi
L4f08d7:
    mov.s    edx,ebx
L4f08d9:
    push   esi
L4f08da:
    push   DWORD PTR [ebp-0x74]
L4f08dd:
    call   0x4f0660
L4f08e2:
    mov    ecx,DWORD PTR [ebp-0x4]
L4f08e5:
    add    esp,0x8
L4f08e8:
    xor.s    ecx,ebp
L4f08ea:
    pop    edi
L4f08eb:
    pop    esi
L4f08ec:
    pop    ebx
L4f08ed:
    call   0x8f8958
L4f08f2:
    mov.s    esp,ebp
L4f08f4:
    pop    ebp
L4f08f5:
    ret
.section .note.GNU-stack,"",@progbits
