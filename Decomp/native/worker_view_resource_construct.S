# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4571f0.
.intel_syntax noprefix
.code32
.text
.global original_worker_view_resource_construct
original_worker_view_resource_construct:
.L4571f0:
    push   ebp
.L4571f1:
    {load} mov    ebp,esp
.L4571f3:
    push   0xffffffff
.L4571f5:
    push   0x90024b
.L4571fa:
    mov    eax,fs:0x0
.L457200:
    push   eax
.L457201:
    sub    esp,0x34
.L457204:
    mov    eax,[0xbaabc0]
.L457209:
    {load} xor    eax,ebp
.L45720b:
    mov    DWORD PTR [ebp-0x10],eax
.L45720e:
    push   ebx
.L45720f:
    push   esi
.L457210:
    push   edi
.L457211:
    push   eax
.L457212:
    lea    eax,[ebp-0xc]
.L457215:
    mov    fs:0x0,eax
.L45721b:
    {load} mov    edi,ecx
.L45721d:
    mov    ecx,DWORD PTR [ebp+0x14]
.L457220:
    mov    edx,DWORD PTR [ebp+0x18]
.L457223:
    mov    DWORD PTR [ebp-0x38],edi
.L457226:
    mov    DWORD PTR [ebp-0x2c],ecx
.L457229:
    mov    DWORD PTR [ebp-0x30],edx
.L45722c:
    mov    DWORD PTR [ebp-0x3c],0x0
.L457233:
    cmp    DWORD PTR [ebp+0x1c],0x0
.L457237:
    mov    DWORD PTR [ebp-0x4],0x0
.L45723e:
    je .L457265
.L457240:
    mov    DWORD PTR [edi],0x9fa5d0
.L457246:
    mov    DWORD PTR [edi+0x1cc],0xba20bc
.L457250:
    mov    DWORD PTR [edi+0x1d0],0x0
.L45725a:
    mov    BYTE PTR [ebp-0x4],0x1
.L45725e:
    mov    DWORD PTR [ebp-0x3c],0x1
.L457265:
    mov    eax,DWORD PTR [edi]
.L457267:
    mov    eax,DWORD PTR [eax+0x4]
.L45726a:
    mov    DWORD PTR [edi+eax*1],0x9fa5dc
.L457271:
    mov    DWORD PTR [edi+0x4],0x0
.L457278:
    mov    DWORD PTR [edi+0x8],0xbf800000
.L45727f:
    mov    DWORD PTR [edi+0xc],0x0
.L457286:
    mov    DWORD PTR [edi+0x10],0x3f800000
.L45728d:
    mov    DWORD PTR [edi+0x14],0x3f800000
.L457294:
    mov    DWORD PTR [edi+0x18],0x3f800000
.L45729b:
    mov    DWORD PTR [edi+0x1c],0x3f800000
.L4572a2:
    mov    DWORD PTR [edi+0x20],0x3f800000
.L4572a9:
    mov    DWORD PTR [edi+0x24],0x3f800000
.L4572b0:
    mov    DWORD PTR [edi+0x28],0x3f800000
.L4572b7:
    mov    DWORD PTR [edi+0x2c],0x3f800000
.L4572be:
    mov    DWORD PTR [edi+0x30],0x3f800000
.L4572c5:
    mov    DWORD PTR [edi+0x34],0x3f800000
.L4572cc:
    mov    DWORD PTR [edi+0x38],0x3f800000
.L4572d3:
    mov    DWORD PTR [edi+0x3c],0x3f800000
.L4572da:
    mov    DWORD PTR [edi+0x40],0x0
.L4572e1:
    mov    DWORD PTR [edi+0x44],0xbf800000
.L4572e8:
    mov    DWORD PTR [edi+0x48],0x0
.L4572ef:
    mov    DWORD PTR [edi+0x4c],0x3f800000
.L4572f6:
    mov    DWORD PTR [edi+0x50],0x3f800000
.L4572fd:
    mov    DWORD PTR [edi+0x54],0x3f800000
.L457304:
    mov    DWORD PTR [edi+0x58],0x3f800000
.L45730b:
    mov    DWORD PTR [edi+0x5c],0x3f800000
.L457312:
    mov    DWORD PTR [edi+0x60],0x3f800000
.L457319:
    mov    DWORD PTR [edi+0x64],0x3f800000
.L457320:
    mov    DWORD PTR [edi+0x68],0x3f800000
.L457327:
    mov    DWORD PTR [edi+0x6c],0x3f800000
.L45732e:
    mov    DWORD PTR [edi+0x70],0x3f800000
.L457335:
    mov    DWORD PTR [edi+0x74],0x3f800000
.L45733c:
    mov    DWORD PTR [edi+0x78],0x3f800000
.L457343:
    mov    DWORD PTR [edi+0x7c],0x0
.L45734a:
    mov    DWORD PTR [edi+0x80],0xbf800000
.L457354:
    mov    DWORD PTR [edi+0x84],0x0
.L45735e:
    mov    DWORD PTR [edi+0x88],0x3f800000
.L457368:
    mov    DWORD PTR [edi+0x8c],0x3f800000
.L457372:
    mov    DWORD PTR [edi+0x90],0x3f800000
.L45737c:
    mov    DWORD PTR [edi+0x94],0x3f800000
.L457386:
    mov    DWORD PTR [edi+0x98],0x3f800000
.L457390:
    mov    DWORD PTR [edi+0x9c],0x3f800000
.L45739a:
    mov    DWORD PTR [edi+0xa0],0x3f800000
.L4573a4:
    mov    DWORD PTR [edi+0xa4],0x3f800000
.L4573ae:
    mov    DWORD PTR [edi+0xa8],0x3f800000
.L4573b8:
    mov    DWORD PTR [edi+0xac],0x3f800000
.L4573c2:
    mov    DWORD PTR [edi+0xb0],0x3f800000
.L4573cc:
    mov    DWORD PTR [edi+0xb4],0x3f800000
.L4573d6:
    mov    DWORD PTR [edi+0xb8],0x0
.L4573e0:
    mov    DWORD PTR [edi+0xbc],0xbf800000
.L4573ea:
    mov    DWORD PTR [edi+0xc0],0x0
.L4573f4:
    mov    DWORD PTR [edi+0xc4],0x3f800000
.L4573fe:
    mov    DWORD PTR [edi+0xc8],0x3f800000
.L457408:
    mov    DWORD PTR [edi+0xcc],0x3f800000
.L457412:
    mov    DWORD PTR [edi+0xd0],0x3f800000
.L45741c:
    mov    DWORD PTR [edi+0xd4],0x3f800000
.L457426:
    mov    DWORD PTR [edi+0xd8],0x3f800000
.L457430:
    mov    DWORD PTR [edi+0xdc],0x3f800000
.L45743a:
    mov    DWORD PTR [edi+0xe0],0x3f800000
.L457444:
    mov    DWORD PTR [edi+0xe4],0x3f800000
.L45744e:
    mov    DWORD PTR [edi+0xe8],0x3f800000
.L457458:
    mov    DWORD PTR [edi+0xec],0x3f800000
.L457462:
    mov    DWORD PTR [edi+0xf0],0x3f800000
.L45746c:
    mov    DWORD PTR [edi+0xf4],0x3f800000
.L457476:
    mov    DWORD PTR [edi+0xf8],0x3f800000
.L457480:
    mov    DWORD PTR [edi+0xfc],0x3f800000
.L45748a:
    mov    DWORD PTR [edi+0x100],0x3f800000
.L457494:
    mov    DWORD PTR [edi+0x104],0x42c80000
.L45749e:
    mov    DWORD PTR [edi+0x108],0x447a0000
.L4574a8:
    mov    DWORD PTR [edi+0x10c],0x42c80000
.L4574b2:
    mov    DWORD PTR [edi+0x110],0x0
.L4574bc:
    mov    DWORD PTR [edi+0x114],0x0
.L4574c6:
    mov    DWORD PTR [edi+0x118],0x0
.L4574d0:
    mov    BYTE PTR [edi+0x11c],0x0
.L4574d7:
    mov    DWORD PTR [edi+0x120],0x3f800000
.L4574e1:
    mov    DWORD PTR [edi+0x124],0x3f800000
.L4574eb:
    mov    DWORD PTR [edi+0x128],0x3f800000
.L4574f5:
    mov    DWORD PTR [edi+0x12c],0x3f800000
.L4574ff:
    mov    DWORD PTR [edi+0x130],0x42c80000
.L457509:
    mov    DWORD PTR [edi+0x134],0x447a0000
.L457513:
    mov    DWORD PTR [edi+0x138],0x42c80000
.L45751d:
    mov    esi,DWORD PTR [ebp+0x8]
.L457520:
    mov    DWORD PTR [edi+0x13c],0x0
.L45752a:
    mov    DWORD PTR [edi+0x140],0x0
.L457534:
    mov    DWORD PTR [edi+0x144],0x0
.L45753e:
    mov    BYTE PTR [edi+0x148],0x0
.L457545:
    mov    DWORD PTR [edi+0x14c],ecx
.L45754b:
    mov    DWORD PTR [edi+0x150],0x0
.L457555:
    mov    DWORD PTR [edi+0x154],0xc
.L45755f:
    mov    DWORD PTR [edi+0x158],edx
.L457565:
    mov    DWORD PTR [edi+0x15c],esi
.L45756b:
    test   esi,esi
.L45756d:
    js .L457587
.L45756f:
    call target_417270
.L457574:
    {load} mov    ecx,eax
.L457576:
    mov    eax,DWORD PTR [ecx+0x4]
.L457579:
    movsx  edx,WORD PTR [eax+esi*2]
.L45757d:
    mov    eax,DWORD PTR [ecx+0x28]
.L457580:
    inc    DWORD PTR [eax+edx*8+0x4]
.L457584:
    mov    esi,DWORD PTR [ebp+0x8]
.L457587:
    mov    eax,DWORD PTR [ebp+0xc]
.L45758a:
    mov    DWORD PTR [ebp-0x4],0x2
.L457591:
    mov    DWORD PTR [edi+0x160],0x0
.L45759b:
    mov    DWORD PTR [edi+0x164],0x0
.L4575a5:
    mov    DWORD PTR [edi+0x168],0x0
.L4575af:
    mov    DWORD PTR [edi+0x16c],0x0
.L4575b9:
    mov    DWORD PTR [edi+0x170],0x3f800000
.L4575c3:
    mov    DWORD PTR [edi+0x174],0x3f800000
.L4575cd:
    mov    DWORD PTR [edi+0x178],0x0
.L4575d7:
    mov    DWORD PTR [edi+0x17c],0x0
.L4575e1:
    mov    DWORD PTR [edi+0x180],0x26ff
.L4575eb:
    mov    DWORD PTR [edi+0x184],0x0
.L4575f5:
    mov    DWORD PTR [edi+0x188],eax
.L4575fb:
    mov    DWORD PTR [edi+0x18c],0x0
.L457605:
    mov    DWORD PTR [edi+0x190],0x0
.L45760f:
    mov    DWORD PTR [edi+0x19c],0x0
.L457619:
    mov    DWORD PTR [edi+0x1a0],0x0
.L457623:
    mov    DWORD PTR [edi+0x1ac],0x0
.L45762d:
    lea    ebx,[edi+0x1b0]
.L457633:
    mov    DWORD PTR [ebx],0x0
.L457639:
    mov    DWORD PTR [ebx+0x4],0x0
.L457640:
    mov    DWORD PTR [ebx+0x8],0x0
.L457647:
    mov    DWORD PTR [edi+0x1bc],0x0
.L457651:
    mov    DWORD PTR [edi+0x1c0],0x0
.L45765b:
    mov    BYTE PTR [ebp-0x4],0x5
.L45765f:
    mov    eax,0x9998bc
.L457664:
    mov    WORD PTR [edi+0x1c4],0x1
.L45766d:
    mov    BYTE PTR [edi+0x1c6],0x0
.L457674:
    test   esi,esi
.L457676:
    js .L457696
.L457678:
    call target_417270
.L45767d:
    {load} mov    edx,eax
.L45767f:
    mov    eax,DWORD PTR [edx+0x4]
.L457682:
    movsx  ecx,WORD PTR [eax+esi*2]
.L457686:
    mov    eax,DWORD PTR [edx+0x28]
.L457689:
    mov    ecx,DWORD PTR [eax+ecx*8]
.L45768c:
    mov    eax,[0xbfcb38]
.L457691:
    add    eax,0x4
.L457694:
    {load} add    eax,ecx
.L457696:
    push   DWORD PTR [ebp-0x2c]
.L457699:
    push   DWORD PTR [ebp-0x30]
.L45769c:
    push   eax
.L45769d:
    lea    eax,[ebp-0x28]
.L4576a0:
    push   0x9fa5b0
.L4576a5:
    push   eax
.L4576a6:
    call target_4571b0
.L4576ab:
    add    esp,0x14
.L4576ae:
    cmp    DWORD PTR [ebp-0x14],0x10
.L4576b2:
    jb .L4576c0
.L4576b4:
    push   DWORD PTR [ebp-0x28]
.L4576b7:
    call   DWORD PTR [0x92d4b0]
.L4576bd:
    add    esp,0x4
.L4576c0:
    cmp    DWORD PTR [ebp+0x8],0x0
.L4576c4:
    jl .L4576cb
.L4576c6:
    call target_417270
.L4576cb:
    mov    esi,DWORD PTR [0xbfcb48]
.L4576d1:
    test   esi,esi
.L4576d3:
    jne .L457702
.L4576d5:
    push   0x18
.L4576d7:
    call   DWORD PTR [0x92d4b4]
.L4576dd:
    add    esp,0x4
.L4576e0:
    mov    DWORD PTR [ebp-0x30],eax
.L4576e3:
    mov    BYTE PTR [ebp-0x4],0x6
.L4576e7:
    test   eax,eax
.L4576e9:
    je .L4576f6
.L4576eb:
    {load} mov    ecx,eax
.L4576ed:
    call target_42bfd0
.L4576f2:
    {load} mov    esi,eax
.L4576f4:
    jmp .L4576f8
.L4576f6:
    {load} xor    esi,esi
.L4576f8:
    mov    BYTE PTR [ebp-0x4],0x5
.L4576fc:
    mov    DWORD PTR [0xbfcb48],esi
.L457702:
    mov    ecx,DWORD PTR [0xc0d408]
.L457708:
    mov    DWORD PTR [ebp-0x2c],edi
.L45770b:
    mov    eax,DWORD PTR [ecx]
.L45770d:
    mov    eax,DWORD PTR [eax+0x168]
.L457713:
    call   eax
.L457715:
    test   al,al
.L457717:
    lea    eax,[ebp-0x2c]
.L45771a:
    push   eax
.L45771b:
    je .L457727
.L45771d:
    lea    ecx,[esi+0xc]
.L457720:
    call target_42c2a0
.L457725:
    jmp .L457746
.L457727:
    {load} mov    ecx,esi
.L457729:
    call target_42c2a0
.L45772e:
    mov    edx,DWORD PTR [esi+0x4]
.L457731:
    {load} mov    eax,edx
.L457733:
    mov    ecx,DWORD PTR [esi]
.L457735:
    {load} sub    eax,ecx
.L457737:
    push   DWORD PTR [ebp-0x38]
.L45773a:
    sar    eax,0x2
.L45773d:
    push   eax
.L45773e:
    call target_42c310
.L457743:
    add    esp,0x8
.L457746:
    mov    edx,DWORD PTR [edi+0x158]
.L45774c:
    cmp    edx,0x3
.L45774f:
    jne .L45777b
.L457751:
    mov    DWORD PTR [edi+0x194],0x1
.L45775b:
    mov    DWORD PTR [edi+0x1a4],0x1
.L457765:
    mov    DWORD PTR [edi+0x198],0x1
.L45776f:
    mov    DWORD PTR [edi+0x1a8],0x1
.L457779:
    jmp .L4577af
.L45777b:
    mov    ecx,DWORD PTR [0xc0d408]
.L457781:
    push   edx
.L457782:
    lea    edx,[ebp-0x34]
.L457785:
    push   edx
.L457786:
    mov    eax,DWORD PTR [ecx]
.L457788:
    call   DWORD PTR [eax+0x10]
.L45778b:
    cvttss2si eax,DWORD PTR [ebp-0x34]
.L457790:
    dec    eax
.L457791:
    mov    DWORD PTR [edi+0x194],eax
.L457797:
    mov    DWORD PTR [edi+0x1a4],eax
.L45779d:
    cvttss2si eax,DWORD PTR [ebp-0x30]
.L4577a2:
    dec    eax
.L4577a3:
    mov    DWORD PTR [edi+0x198],eax
.L4577a9:
    mov    DWORD PTR [edi+0x1a8],eax
.L4577af:
    movd   xmm1,DWORD PTR [edi+0x18c]
.L4577b7:
    movd   xmm0,DWORD PTR [edi+0x194]
.L4577bf:
    movd   xmm2,DWORD PTR [edi+0x190]
.L4577c7:
    cvtdq2ps xmm0,xmm0
.L4577ca:
    mov    ecx,DWORD PTR [ebp+0x10]
.L4577cd:
    cvtdq2ps xmm1,xmm1
.L4577d0:
    cvtdq2ps xmm2,xmm2
.L4577d3:
    subss  xmm0,xmm1
.L4577d7:
    movss  DWORD PTR [edi+0x168],xmm1
.L4577df:
    movss  DWORD PTR [edi+0x16c],xmm2
.L4577e7:
    addss  xmm0,DWORD PTR [0xa06558]
.L4577ef:
    movss  DWORD PTR [edi+0x160],xmm0
.L4577f7:
    movd   xmm0,DWORD PTR [edi+0x198]
.L4577ff:
    cvtdq2ps xmm0,xmm0
.L457802:
    subss  xmm0,xmm2
.L457806:
    addss  xmm0,DWORD PTR [0xa06558]
.L45780e:
    movss  DWORD PTR [edi+0x164],xmm0
.L457816:
    mov    eax,DWORD PTR [ebx+0x8]
.L457819:
    sub    eax,DWORD PTR [ebx]
.L45781b:
    sar    eax,0x2
.L45781e:
    {load} cmp    eax,ecx
.L457820:
    jae .L45783d
.L457822:
    cmp    ecx,0x3fffffff
.L457828:
    jbe .L457835
.L45782a:
    push   0x999938
.L45782f:
    call   DWORD PTR [0x92d168]
.L457835:
    push   ecx
.L457836:
    {load} mov    ecx,ebx
.L457838:
    call target_43ee60
.L45783d:
    mov    DWORD PTR [ebp-0x4],0xffffffff
.L457844:
    mov    esi,DWORD PTR [ebp+0x8]
.L457847:
    test   esi,esi
.L457849:
    js .L457873
.L45784b:
    call target_417270
.L457850:
    {load} mov    ecx,eax
.L457852:
    mov    eax,DWORD PTR [ecx+0x4]
.L457855:
    movsx  edx,WORD PTR [eax+esi*2]
.L457859:
    mov    eax,DWORD PTR [ecx+0x28]
.L45785c:
    dec    DWORD PTR [eax+edx*8+0x4]
.L457860:
    jne .L457873
.L457862:
    mov    esi,DWORD PTR [ebp+0x8]
.L457865:
    call target_417270
.L45786a:
    push   esi
.L45786b:
    lea    ecx,[eax+0x4]
.L45786e:
    call target_41c090
.L457873:
    {load} mov    eax,edi
.L457875:
    mov    ecx,DWORD PTR [ebp-0xc]
.L457878:
    mov    DWORD PTR fs:0x0,ecx
.L45787f:
    pop    ecx
.L457880:
    pop    edi
.L457881:
    pop    esi
.L457882:
    pop    ebx
.L457883:
    mov    ecx,DWORD PTR [ebp-0x10]
.L457886:
    {load} xor    ecx,ebp
.L457888:
    call target_8f8958
.L45788d:
    {load} mov    esp,ebp
.L45788f:
    pop    ebp
.L457890:
    ret    0x18
.equ target_417270,0x417270
.equ target_41c090,0x41c090
.equ target_42bfd0,0x42bfd0
.equ target_42c2a0,0x42c2a0
.equ target_42c310,0x42c310
.equ target_43ee60,0x43ee60
.equ target_4571b0,0x4571b0
.equ target_8f8958,0x8f8958
