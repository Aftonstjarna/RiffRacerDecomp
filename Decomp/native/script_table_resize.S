.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Original SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f0660.
.global original_script_table_resize
original_script_table_resize:
L4f0660:
    push   ebp
L4f0661:
    {load} mov    ebp,esp
L4f0663:
    and    esp,0xfffffff8
L4f0666:
    sub    esp,0x14
L4f0669:
    push   ebx
L4f066a:
    push   esi
L4f066b:
    push   edi
L4f066c:
    {load} mov    edi,edx
L4f066e:
    {load} mov    ebx,ecx
L4f0670:
    mov    edx,DWORD PTR [ebp+0x8]
L4f0673:
    movzx  eax,BYTE PTR [edi+0x7]
L4f0677:
    mov    esi,DWORD PTR [edi+0x1c]
L4f067a:
    mov    DWORD PTR [esp+0x1c],eax
L4f067e:
    mov    eax,DWORD PTR [edi+0x10]
L4f0681:
    mov    DWORD PTR [esp+0x10],esi
L4f0685:
    mov    DWORD PTR [esp+0x14],eax
L4f0689:
    {load} cmp    edx,esi
L4f068b:
    jle L4f0698
L4f068d:
    push   edx
L4f068e:
    {load} mov    edx,edi
L4f0690:
    call target_4f0520
L4f0695:
    add    esp,0x4
L4f0698:
    push   DWORD PTR [ebp+0xc]
L4f069b:
    {load} mov    edx,edi
L4f069d:
    {load} mov    ecx,ebx
L4f069f:
    call target_4f0580
L4f06a4:
    mov    eax,DWORD PTR [ebp+0x8]
L4f06a7:
    add    esp,0x4
L4f06aa:
    {load} cmp    eax,esi
L4f06ac:
    jge L4f0736
L4f06b2:
    mov    ecx,DWORD PTR [esp+0x10]
L4f06b6:
    {load} mov    esi,eax
L4f06b8:
    mov    DWORD PTR [edi+0x1c],eax
L4f06bb:
    jmp L4f06c0
L4f06bd:
    {disp8} lea ecx,[ecx+0x0]
L4f06c0:
    mov    eax,DWORD PTR [edi+0xc]
L4f06c3:
    mov    DWORD PTR [esp+0x18],eax
L4f06c7:
    cmp    DWORD PTR [eax+esi*8+0x4],0x0
L4f06cc:
    je L4f06f2
L4f06ce:
    lea    eax,[esi+0x1]
L4f06d1:
    {load} mov    edx,edi
L4f06d3:
    push   eax
L4f06d4:
    {load} mov    ecx,ebx
L4f06d6:
    call target_4f0cc0
L4f06db:
    mov    edx,DWORD PTR [esp+0x1c]
L4f06df:
    add    esp,0x4
L4f06e2:
    mov    ecx,DWORD PTR [edx+esi*8]
L4f06e5:
    mov    DWORD PTR [eax],ecx
L4f06e7:
    mov    ecx,DWORD PTR [edx+esi*8+0x4]
L4f06eb:
    mov    DWORD PTR [eax+0x4],ecx
L4f06ee:
    mov    ecx,DWORD PTR [esp+0x10]
L4f06f2:
    inc    esi
L4f06f3:
    {load} cmp    esi,ecx
L4f06f5:
    jl L4f06c0
L4f06f7:
    mov    edx,DWORD PTR [ebp+0x8]
L4f06fa:
    lea    eax,[edx+0x1]
L4f06fd:
    cmp    eax,0x1fffffff
L4f0702:
    ja L4f0723
L4f0704:
    lea    eax,[edx*8+0x0]
L4f070b:
    mov    edx,DWORD PTR [edi+0xc]
L4f070e:
    push   eax
L4f070f:
    lea    eax,[ecx*8+0x0]
L4f0716:
    {load} mov    ecx,ebx
L4f0718:
    push   eax
L4f0719:
    call target_4f7d10
L4f071e:
    add    esp,0x8
L4f0721:
    jmp L4f0733
L4f0723:
    push   0x9fdb34
L4f0728:
    push   ebx
L4f0729:
    call target_486ab0
L4f072e:
    add    esp,0x8
L4f0731:
    {load} xor    eax,eax
L4f0733:
    mov    DWORD PTR [edi+0xc],eax
L4f0736:
    mov    ecx,DWORD PTR [esp+0x1c]
L4f073a:
    mov    eax,0x1
L4f073f:
    shl    eax,cl
L4f0741:
    mov    DWORD PTR [esp+0x1c],eax
L4f0745:
    lea    ecx,[eax-0x1]
L4f0748:
    mov    DWORD PTR [esp+0x10],ecx
L4f074c:
    test   ecx,ecx
L4f074e:
    js L4f07d8
L4f0754:
    mov    edx,DWORD PTR [esp+0x14]
L4f0758:
    lea    esi,[ecx*4+0x2]
L4f075f:
    {load} add    esi,ecx
L4f0761:
    lea    esi,[edx+esi*4]
L4f0764:
    cmp    DWORD PTR [esi-0x4],0x0
L4f0768:
    je L4f07c8
L4f076a:
    {load} mov    edx,esi
L4f076c:
    {load} mov    ecx,edi
L4f076e:
    call target_4f0bb0
L4f0773:
    mov    BYTE PTR [edi+0x6],0x0
L4f0777:
    cmp    eax,0x99a41c
L4f077c:
    jne L4f07b9
L4f077e:
    mov    eax,DWORD PTR [esi+0x4]
L4f0781:
    test   eax,eax
L4f0783:
    jne L4f078c
L4f0785:
    push   0x9fd750
L4f078a:
    jmp L4f07a3
L4f078c:
    cmp    eax,0x3
L4f078f:
    jne L4f07ac
L4f0791:
    movss  xmm0,DWORD PTR [esi]
L4f0795:
    ucomiss xmm0,xmm0
L4f0798:
    lahf
L4f0799:
    test   ah,0x44
L4f079c:
    jnp L4f07ac
L4f079e:
    push   0x9fd714
L4f07a3:
    push   ebx
L4f07a4:
    call target_486ab0
L4f07a9:
    add    esp,0x8
L4f07ac:
    push   esi
L4f07ad:
    {load} mov    edx,edi
L4f07af:
    {load} mov    ecx,ebx
L4f07b1:
    call target_4f09e0
L4f07b6:
    add    esp,0x4
L4f07b9:
    mov    ecx,DWORD PTR [esi-0x8]
L4f07bc:
    mov    DWORD PTR [eax],ecx
L4f07be:
    mov    ecx,DWORD PTR [esi-0x4]
L4f07c1:
    mov    DWORD PTR [eax+0x4],ecx
L4f07c4:
    mov    ecx,DWORD PTR [esp+0x10]
L4f07c8:
    dec    ecx
L4f07c9:
    sub    esi,0x14
L4f07cc:
    mov    DWORD PTR [esp+0x10],ecx
L4f07d0:
    test   ecx,ecx
L4f07d2:
    jns L4f0764
L4f07d4:
    mov    eax,DWORD PTR [esp+0x1c]
L4f07d8:
    mov    ecx,DWORD PTR [esp+0x14]
L4f07dc:
    cmp    ecx,0x99a424
L4f07e2:
    je L4f07f9
L4f07e4:
    lea    eax,[eax+eax*4]
L4f07e7:
    {load} mov    edx,ecx
L4f07e9:
    shl    eax,0x2
L4f07ec:
    {load} mov    ecx,ebx
L4f07ee:
    push   0x0
L4f07f0:
    push   eax
L4f07f1:
    call target_4f7d10
L4f07f6:
    add    esp,0x8
L4f07f9:
    pop    edi
L4f07fa:
    pop    esi
L4f07fb:
    pop    ebx
L4f07fc:
    {load} mov    esp,ebp
L4f07fe:
    pop    ebp
L4f07ff:
    ret
.equ target_486ab0,0x486ab0
.equ target_4f0520,0x4f0520
.equ target_4f0580,0x4f0580
.equ target_4f09e0,0x4f09e0
.equ target_4f0bb0,0x4f0bb0
.equ target_4f0cc0,0x4f0cc0
.equ target_4f7d10,0x4f7d10
