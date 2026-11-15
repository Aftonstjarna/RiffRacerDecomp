# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x53d2d0,0x53d39a); external switch tables remain original data.
.intel_syntax noprefix
.code32
.text
.global original_render_target_dimensions_initialize
original_render_target_dimensions_initialize:
# ECX=this, two stack dimensions; writes 23 pairs. No calls.
# Switch data at 0x53d39c/0x53d3ac must remain mapped from original evidence.
L_53d2d0:
    push   ebp
L_53d2d1:
    {load} mov    ebp,esp
L_53d2d3:
    mov    eax,DWORD PTR [ebp+0x8]
L_53d2d6:
    push   ebx
L_53d2d7:
    {load} mov    ebx,ecx
L_53d2d9:
    push   esi
L_53d2da:
    push   edi
L_53d2db:
    {load} xor    esi,esi
L_53d2dd:
    mov    DWORD PTR [ebx+0x8],eax
L_53d2e0:
    lea    edi,[ebx+0x78]
L_53d2e3:
    mov    eax,DWORD PTR [ebp+0xc]
L_53d2e6:
    mov    DWORD PTR [ebx+0xc],eax
L_53d2e9:
    {disp32} lea    esp,[esp+0x0]
L_53d2f0:
    cmp    esi,0x13
L_53d2f3:
    je L_53d379
L_53d2f9:
    cmp    esi,0x14
L_53d2fc:
    je L_53d379
L_53d2fe:
    cmp    esi,0x15
L_53d301:
    je L_53d362
L_53d303:
    cmp    esi,0x16
L_53d306:
    je L_53d362
L_53d308:
    lea    eax,[esi-0x2]
L_53d30b:
    {load} xor    ecx,ecx
L_53d30d:
    cmp    eax,0x10
L_53d310:
    ja L_53d351
L_53d312:
    movzx  eax,BYTE PTR [eax+0x53d3ac]
L_53d319:
    jmp    DWORD PTR [eax*4+0x53d39c]
L_53d320:
    mov    eax,DWORD PTR [ebx+0x8]
L_53d323:
    mov    ecx,0x1
L_53d328:
    sar    eax,cl
L_53d32a:
    mov    DWORD PTR [edi-0x5c],eax
L_53d32d:
    mov    eax,DWORD PTR [ebx+0xc]
L_53d330:
    sar    eax,cl
L_53d332:
    mov    DWORD PTR [edi],eax
L_53d334:
    jmp L_53d386
L_53d336:
    mov    eax,DWORD PTR [ebx+0x8]
L_53d339:
    mov    ecx,0x2
L_53d33e:
    sar    eax,cl
L_53d340:
    mov    DWORD PTR [edi-0x5c],eax
L_53d343:
    mov    eax,DWORD PTR [ebx+0xc]
L_53d346:
    sar    eax,cl
L_53d348:
    mov    DWORD PTR [edi],eax
L_53d34a:
    jmp L_53d386
L_53d34c:
    mov    ecx,0x3
L_53d351:
    mov    eax,DWORD PTR [ebx+0x8]
L_53d354:
    sar    eax,cl
L_53d356:
    mov    DWORD PTR [edi-0x5c],eax
L_53d359:
    mov    eax,DWORD PTR [ebx+0xc]
L_53d35c:
    sar    eax,cl
L_53d35e:
    mov    DWORD PTR [edi],eax
L_53d360:
    jmp L_53d386
L_53d362:
    mov    eax,DWORD PTR [ebx+0x8]
L_53d365:
    cdq
L_53d366:
    {load} sub    eax,edx
L_53d368:
    sar    eax,1
L_53d36a:
    mov    DWORD PTR [edi-0x5c],eax
L_53d36d:
    mov    eax,DWORD PTR [ebx+0xc]
L_53d370:
    cdq
L_53d371:
    {load} sub    eax,edx
L_53d373:
    sar    eax,1
L_53d375:
    mov    DWORD PTR [edi],eax
L_53d377:
    jmp L_53d386
L_53d379:
    mov    DWORD PTR [edi-0x5c],0x140
L_53d380:
    mov    DWORD PTR [edi],0xb4
L_53d386:
    inc    esi
L_53d387:
    add    edi,0x4
L_53d38a:
    cmp    esi,0x17
L_53d38d:
    jb L_53d2f0
L_53d393:
    pop    edi
L_53d394:
    pop    esi
L_53d395:
    pop    ebx
L_53d396:
    pop    ebp
L_53d397:
    ret    0x8
.section .note.GNU-stack,"",@progbits
