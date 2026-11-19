# Mechanically transcribed reference evidence; Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2, VA 0x448500; not high-level recovery.
.intel_syntax noprefix
.code32
.text
.equ colour_scale,0xa067f0
.global original_ui_item_set_colour
original_ui_item_set_colour:
.L448500:
    push   ebp
.L448501:
    {load} mov ebp,esp
.L448503:
    push   ecx
.L448504:
    {load} mov edx,ecx
.L448506:
    push   esi
.L448507:
    mov    esi,DWORD PTR [ebp+0x8]
.L44850a:
    mov    DWORD PTR [ebp-0x4],edx
.L44850d:
    mov    ecx,DWORD PTR [edx+0x184]
.L448513:
    mov    eax,DWORD PTR [esi]
.L448515:
    mov    DWORD PTR [edx+0x54],eax
.L448518:
    mov    eax,DWORD PTR [esi+0x4]
.L44851b:
    mov    DWORD PTR [edx+0x58],eax
.L44851e:
    mov    eax,DWORD PTR [esi+0x8]
.L448521:
    mov    DWORD PTR [edx+0x5c],eax
.L448524:
    mov    eax,DWORD PTR [esi+0xc]
.L448527:
    mov    DWORD PTR [edx+0x60],eax
.L44852a:
    cmp    ecx,DWORD PTR [edx+0x188]
.L448530:
    je .L44869b
.L448536:
    movss  xmm2,DWORD PTR [colour_scale]
.L44853e:
    {load} mov eax,edx
.L448540:
    push   ebx
.L448541:
    push   edi
.L448542:
    mov    edx,DWORD PTR [ecx]
.L448544:
    test   edx,edx
.L448546:
    je .L44868a
.L44854c:
    cmp    DWORD PTR [edx+0x12c],0x0
.L448553:
    je .L44860f
.L448559:
    lea    edi,[edx+0x120]
.L44855f:
    mov    DWORD PTR [ebp+0x8],0x0
.L448566:
    mov    edx,DWORD PTR [edi+0x4]
.L448569:
    mov    eax,0x38e38e39
.L44856e:
    sub    edx,DWORD PTR [edi]
.L448570:
    imul   edx
.L448572:
    sar    edx,0x3
.L448575:
    {load} mov eax,edx
.L448577:
    shr    eax,0x1f
.L44857a:
    {load} add eax,edx
.L44857c:
    test   eax,eax
.L44857e:
    jle .L448687
.L448584:
    {load} xor ebx,ebx
.L448586:
    jmp .L448590
.L448588:
    {disp32} lea esp,[esp+0x0]
.L44858f:
    nop
.L448590:
    movss  xmm0,DWORD PTR [esi]
.L448594:
    lea    ebx,[ebx+0x24]
.L448597:
    mulss  xmm0,xmm2
.L44859b:
    inc    DWORD PTR [ebp+0x8]
.L44859e:
    cvttss2si eax,xmm0
.L4485a2:
    movss  xmm0,DWORD PTR [esi+0x4]
.L4485a7:
    movzx  edx,al
.L4485aa:
    mulss  xmm0,xmm2
.L4485ae:
    shl    edx,0x8
.L4485b1:
    cvttss2si eax,xmm0
.L4485b5:
    movss  xmm0,DWORD PTR [esi+0x8]
.L4485ba:
    movzx  eax,al
.L4485bd:
    {load} or edx,eax
.L4485bf:
    mulss  xmm0,xmm2
.L4485c3:
    shl    edx,0x8
.L4485c6:
    cvttss2si eax,xmm0
.L4485ca:
    movss  xmm0,DWORD PTR [esi+0xc]
.L4485cf:
    movzx  eax,al
.L4485d2:
    {load} or edx,eax
.L4485d4:
    mulss  xmm0,xmm2
.L4485d8:
    shl    edx,0x8
.L4485db:
    cvttss2si eax,xmm0
.L4485df:
    movzx  eax,al
.L4485e2:
    {load} or edx,eax
.L4485e4:
    mov    eax,DWORD PTR [edi]
.L4485e6:
    mov    DWORD PTR [ebx+eax*1-0x1c],edx
.L4485ea:
    mov    eax,0x38e38e39
.L4485ef:
    mov    edi,DWORD PTR [ecx]
.L4485f1:
    add    edi,0x120
.L4485f7:
    mov    edx,DWORD PTR [edi+0x4]
.L4485fa:
    sub    edx,DWORD PTR [edi]
.L4485fc:
    imul   edx
.L4485fe:
    sar    edx,0x3
.L448601:
    {load} mov eax,edx
.L448603:
    shr    eax,0x1f
.L448606:
    {load} add eax,edx
.L448608:
    cmp    DWORD PTR [ebp+0x8],eax
.L44860b:
    jl .L448590
.L44860d:
    jmp .L448687
.L44860f:
    movss  xmm1,DWORD PTR [esi]
.L448613:
    movss  xmm0,DWORD PTR [edx+0x90]
.L44861b:
    ucomiss xmm0,xmm1
.L44861e:
    lahf
.L44861f:
    test   ah,0x44
.L448622:
    jp .L44865a
.L448624:
    movss  xmm0,DWORD PTR [edx+0x94]
.L44862c:
    ucomiss xmm0,DWORD PTR [esi+0x4]
.L448630:
    lahf
.L448631:
    test   ah,0x44
.L448634:
    jp .L44865a
.L448636:
    movss  xmm0,DWORD PTR [edx+0x98]
.L44863e:
    ucomiss xmm0,DWORD PTR [esi+0x8]
.L448642:
    lahf
.L448643:
    test   ah,0x44
.L448646:
    jp .L44865a
.L448648:
    movss  xmm0,DWORD PTR [edx+0x9c]
.L448650:
    ucomiss xmm0,DWORD PTR [esi+0xc]
.L448654:
    lahf
.L448655:
    test   ah,0x44
.L448658:
    jnp .L448687
.L44865a:
    movss  DWORD PTR [edx+0x90],xmm1
.L448662:
    mov    eax,DWORD PTR [esi+0x4]
.L448665:
    mov    DWORD PTR [edx+0x94],eax
.L44866b:
    mov    eax,DWORD PTR [esi+0x8]
.L44866e:
    mov    DWORD PTR [edx+0x98],eax
.L448674:
    mov    eax,DWORD PTR [esi+0xc]
.L448677:
    mov    DWORD PTR [edx+0x9c],eax
.L44867d:
    or     DWORD PTR [edx+0x170],0x100
.L448687:
    mov    eax,DWORD PTR [ebp-0x4]
.L44868a:
    add    ecx,0x14
.L44868d:
    cmp    ecx,DWORD PTR [eax+0x188]
.L448693:
    jne .L448542
.L448699:
    pop    edi
.L44869a:
    pop    ebx
.L44869b:
    pop    esi
.L44869c:
    {load} mov esp,ebp
.L44869e:
    pop    ebp
.L44869f:
    ret    0x4
