# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f2330.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_step
.equ target_4F16F0,0x4F16F0
.equ target_4F19F0,0x4F19F0
.equ target_4F1B50,0x4F1B50
.equ target_4F1BC0,0x4F1BC0
.equ target_4F20E0,0x4F20E0
.equ target_4F2190,0x4F2190
original_script_gc_step:
.L4F2330:
 push ebp
.L4F2331:
 mov.s ebp,esp
.L4F2333:
 sub esp,0x8
.L4F2336:
 push ebx
.L4F2337:
 push esi
.L4F2338:
 push edi
.L4F2339:
 mov edi,DWORD PTR [ecx+0x10]
.L4F233C:
 mov DWORD PTR [ebp-0x4],ecx
.L4F233F:
 mov eax,DWORD PTR [edi+0x54]
.L4F2342:
 lea ebx,[eax+eax*4]
.L4F2345:
 mov eax,0x7ffffffe
.L4F234A:
 add.s ebx,ebx
.L4F234C:
 cmove ebx,eax
.L4F234F:
 mov eax,DWORD PTR [edi+0x44]
.L4F2352:
 sub eax,DWORD PTR [edi+0x40]
.L4F2355:
 add DWORD PTR [edi+0x4c],eax
.L4F2358:
 jmp .L4F2360
.L4F235A:
 {disp32} lea ebx,[ebx+0x0]
.L4F2360:
 mov esi,DWORD PTR [ecx+0x10]
.L4F2363:
 movzx eax,BYTE PTR [esi+0x15]
.L4F2367:
 cmp eax,0x4
.L4F236A:
 ja .L4F244E
.L4F2370:
 jmp DWORD PTR [eax*4+0x4f24b0]
.L4F2377:
 call target_4F20E0
.L4F237C:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F237F:
 jmp .L4F244E
.L4F2384:
 cmp DWORD PTR [esi+0x24],0x0
.L4F2388:
 je .L4F2399
.L4F238A:
 mov.s ecx,esi
.L4F238C:
 call target_4F16F0
.L4F2391:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F2394:
 jmp .L4F2450
.L4F2399:
 call target_4F2190
.L4F239E:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F23A1:
 jmp .L4F244E
.L4F23A6:
 mov eax,DWORD PTR [esi+0x44]
.L4F23A9:
 mov ecx,DWORD PTR [esi+0x18]
.L4F23AC:
 mov DWORD PTR [ebp-0x8],eax
.L4F23AF:
 mov eax,DWORD PTR [esi]
.L4F23B1:
 push 0xfffffffd
.L4F23B3:
 lea edx,[eax+ecx*4]
.L4F23B6:
 lea eax,[ecx+0x1]
.L4F23B9:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F23BC:
 mov DWORD PTR [esi+0x18],eax
.L4F23BF:
 call target_4F19F0
.L4F23C4:
 mov eax,DWORD PTR [esi+0x18]
.L4F23C7:
 add esp,0x4
.L4F23CA:
 cmp eax,DWORD PTR [esi+0x8]
.L4F23CD:
 jl .L4F23D3
.L4F23CF:
 mov BYTE PTR [esi+0x15],0x3
.L4F23D3:
 mov eax,DWORD PTR [esi+0x44]
.L4F23D6:
 sub eax,DWORD PTR [ebp-0x8]
.L4F23D9:
 add DWORD PTR [esi+0x48],eax
.L4F23DC:
 mov eax,0xa
.L4F23E1:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F23E4:
 jmp .L4F2450
.L4F23E6:
 mov eax,DWORD PTR [esi+0x44]
.L4F23E9:
 mov edx,DWORD PTR [esi+0x20]
.L4F23EC:
 push 0x28
.L4F23EE:
 mov DWORD PTR [ebp-0x8],eax
.L4F23F1:
 call target_4F19F0
.L4F23F6:
 add esp,0x4
.L4F23F9:
 mov DWORD PTR [esi+0x20],eax
.L4F23FC:
 cmp DWORD PTR [eax],0x0
.L4F23FF:
 jne .L4F240D
.L4F2401:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F2404:
 call target_4F1B50
.L4F2409:
 mov BYTE PTR [esi+0x15],0x4
.L4F240D:
 mov eax,DWORD PTR [esi+0x44]
.L4F2410:
 sub eax,DWORD PTR [ebp-0x8]
.L4F2413:
 add DWORD PTR [esi+0x48],eax
.L4F2416:
 mov eax,0x190
.L4F241B:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F241E:
 jmp .L4F2450
.L4F2420:
 cmp DWORD PTR [esi+0x30],0x0
.L4F2424:
 je .L4F2443
.L4F2426:
 call target_4F1BC0
.L4F242B:
 mov eax,DWORD PTR [esi+0x48]
.L4F242E:
 cmp eax,0x64
.L4F2431:
 jbe .L4F2439
.L4F2433:
 add eax,0xffffff9c
.L4F2436:
 mov DWORD PTR [esi+0x48],eax
.L4F2439:
 mov ecx,DWORD PTR [ebp-0x4]
.L4F243C:
 mov eax,0x64
.L4F2441:
 jmp .L4F2450
.L4F2443:
 mov BYTE PTR [esi+0x15],0x0
.L4F2447:
 mov DWORD PTR [esi+0x4c],0x0
.L4F244E:
 xor.s eax,eax
.L4F2450:
 sub.s ebx,eax
.L4F2452:
 cmp BYTE PTR [edi+0x15],0x0
.L4F2456:
 je .L4F2497
.L4F2458:
 test ebx,ebx
.L4F245A:
 jg .L4F2360
.L4F2460:
 cmp BYTE PTR [edi+0x15],0x0
.L4F2464:
 je .L4F2497
.L4F2466:
 mov eax,DWORD PTR [edi+0x4c]
.L4F2469:
 cmp eax,0x400
.L4F246E:
 jae .L4F2482
.L4F2470:
 mov eax,DWORD PTR [edi+0x44]
.L4F2473:
 add eax,0x400
.L4F2478:
 mov DWORD PTR [edi+0x40],eax
.L4F247B:
 pop edi
.L4F247C:
 pop esi
.L4F247D:
 pop ebx
.L4F247E:
 mov.s esp,ebp
.L4F2480:
 pop ebp
.L4F2481:
 ret 
.L4F2482:
 add eax,0xfffffc00
.L4F2487:
 mov DWORD PTR [edi+0x4c],eax
.L4F248A:
 mov eax,DWORD PTR [edi+0x44]
.L4F248D:
 mov DWORD PTR [edi+0x40],eax
.L4F2490:
 pop edi
.L4F2491:
 pop esi
.L4F2492:
 pop ebx
.L4F2493:
 mov.s esp,ebp
.L4F2495:
 pop ebp
.L4F2496:
 ret 
.L4F2497:
 mov eax,0x51eb851f
.L4F249C:
 mul DWORD PTR [edi+0x48]
.L4F249F:
 shr edx,0x5
.L4F24A2:
 imul edx,DWORD PTR [edi+0x50]
.L4F24A6:
 mov DWORD PTR [edi+0x40],edx
.L4F24A9:
 pop edi
.L4F24AA:
 pop esi
.L4F24AB:
 pop ebx
.L4F24AC:
 mov.s esp,ebp
.L4F24AE:
 pop ebp
.L4F24AF:
 ret 
.section .note.GNU-stack,"",@progbits
