# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x561170,0x5613a3); instruction-contiguous extent, INT3 padding excluded.
# vectorfast erase/insert: moves the trailing range with memmove and applies the original length checks. Element type is not established by this routine alone.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x561170..0x5613a3
.intel_syntax noprefix
.code32
.text
.global original_fast_vector_erase
original_fast_vector_erase:
.L561170:
 push   ebp
.L561171:
 {load} mov    ebp,esp
.L561173:
 sub    esp,0x8
.L561176:
 push   ebx
.L561177:
 {load} mov    ebx,ecx
.L561179:
 push   esi
.L56117a:
 mov    esi,DWORD PTR [ebx+0x8c]
.L561180:
 push   edi
.L561181:
 lea    edi,[ebx+0x8c]
.L561187:
 mov    BYTE PTR [ebx+0xf0],0x1
.L56118e:
 cmp    esi,DWORD PTR [ebx+0x90]
.L561194:
 je .L5611a8
.L561196:
 mov    ecx,DWORD PTR [esi]
.L561198:
 mov    eax,DWORD PTR [ecx]
.L56119a:
 call   DWORD PTR [eax+0x8]
.L56119d:
 add    esi,0x4
.L5611a0:
 cmp    esi,DWORD PTR [ebx+0x90]
.L5611a6:
 jne .L561196
.L5611a8:
 mov    esi,DWORD PTR [ebx+0xa4]
.L5611ae:
 mov    BYTE PTR [ebx+0xf0],0x0
.L5611b5:
 cmp    esi,DWORD PTR [ebx+0xa8]
.L5611bb:
 je .L5612b3
.L5611c1:
 mov    ecx,DWORD PTR [edi+0x4]
.L5611c4:
 {load} cmp    esi,ecx
.L5611c6:
 jae .L561240
.L5611c8:
 mov    edx,DWORD PTR [edi]
.L5611ca:
 {load} cmp    edx,esi
.L5611cc:
 ja .L561240
.L5611ce:
 {load} mov    eax,esi
.L5611d0:
 {load} sub    eax,edx
.L5611d2:
 mov    edx,DWORD PTR [edi+0x8]
.L5611d5:
 sar    eax,0x2
.L5611d8:
 mov    DWORD PTR [ebp-0x8],eax
.L5611db:
 {load} cmp    ecx,edx
.L5611dd:
 jne .L56122d
.L5611df:
 {load} mov    eax,edx
.L5611e1:
 {load} sub    eax,ecx
.L5611e3:
 sar    eax,0x2
.L5611e6:
 cmp    eax,0x1
.L5611e9:
 jae .L56122d
.L5611eb:
 sub    ecx,DWORD PTR [edi]
.L5611ed:
 mov    eax,0x3fffffff
.L5611f2:
 sar    ecx,0x2
.L5611f5:
 {load} sub    eax,ecx
.L5611f7:
 cmp    eax,0x1
.L5611fa:
 jb .L5612ed
.L561200:
 sub    edx,DWORD PTR [edi]
.L561202:
 inc    ecx
.L561203:
 sar    edx,0x2
.L561206:
 mov    eax,0x3fffffff
.L56120b:
 mov    DWORD PTR [ebp-0x4],ecx
.L56120e:
 {load} mov    ecx,edx
.L561210:
 shr    ecx,1
.L561212:
 {load} sub    eax,ecx
.L561214:
 {load} cmp    eax,edx
.L561216:
 jae .L56121c
.L561218:
 {load} xor    edx,edx
.L56121a:
 jmp .L56121e
.L56121c:
 {load} add    edx,ecx
.L56121e:
 cmp    edx,DWORD PTR [ebp-0x4]
.L561221:
 {load} mov    ecx,edi
.L561223:
 cmovb  edx,DWORD PTR [ebp-0x4]
.L561227:
 push   edx
.L561228:
 call target_426800
.L56122d:
 mov    edx,DWORD PTR [edi+0x4]
.L561230:
 test   edx,edx
.L561232:
 je .L5612a0
.L561234:
 mov    eax,DWORD PTR [edi]
.L561236:
 mov    ecx,DWORD PTR [ebp-0x8]
.L561239:
 mov    eax,DWORD PTR [eax+ecx*4]
.L56123c:
 mov    DWORD PTR [edx],eax
.L56123e:
 jmp .L5612a0
.L561240:
 mov    edx,DWORD PTR [edi+0x8]
.L561243:
 {load} cmp    ecx,edx
.L561245:
 jne .L561295
.L561247:
 {load} mov    eax,edx
.L561249:
 {load} sub    eax,ecx
.L56124b:
 sar    eax,0x2
.L56124e:
 cmp    eax,0x1
.L561251:
 jae .L561295
.L561253:
 sub    ecx,DWORD PTR [edi]
.L561255:
 mov    eax,0x3fffffff
.L56125a:
 sar    ecx,0x2
.L56125d:
 {load} sub    eax,ecx
.L56125f:
 cmp    eax,0x1
.L561262:
 jb .L5612ed
.L561268:
 sub    edx,DWORD PTR [edi]
.L56126a:
 inc    ecx
.L56126b:
 sar    edx,0x2
.L56126e:
 mov    eax,0x3fffffff
.L561273:
 mov    DWORD PTR [ebp-0x8],ecx
.L561276:
 {load} mov    ecx,edx
.L561278:
 shr    ecx,1
.L56127a:
 {load} sub    eax,ecx
.L56127c:
 {load} cmp    eax,edx
.L56127e:
 jae .L561284
.L561280:
 {load} xor    edx,edx
.L561282:
 jmp .L561286
.L561284:
 {load} add    edx,ecx
.L561286:
 cmp    edx,DWORD PTR [ebp-0x8]
.L561289:
 {load} mov    ecx,edi
.L56128b:
 cmovb  edx,DWORD PTR [ebp-0x8]
.L56128f:
 push   edx
.L561290:
 call target_426800
.L561295:
 mov    ecx,DWORD PTR [edi+0x4]
.L561298:
 test   ecx,ecx
.L56129a:
 je .L5612a0
.L56129c:
 mov    eax,DWORD PTR [esi]
.L56129e:
 mov    DWORD PTR [ecx],eax
.L5612a0:
 add    DWORD PTR [edi+0x4],0x4
.L5612a4:
 add    esi,0x4
.L5612a7:
 cmp    esi,DWORD PTR [ebx+0xa8]
.L5612ad:
 jne .L5611c1
.L5612b3:
 mov    eax,DWORD PTR [ebx+0xa4]
.L5612b9:
 mov    DWORD PTR [ebx+0xa8],eax
.L5612bf:
 mov    esi,DWORD PTR [ebx+0x98]
.L5612c5:
 cmp    esi,DWORD PTR [ebx+0x9c]
.L5612cb:
 je .L56131e
.L5612cd:
 {disp8} lea    ecx,[ecx+0x0]
.L5612d0:
 mov    eax,DWORD PTR [edi]
.L5612d2:
 mov    ecx,DWORD PTR [ebx+0x90]
.L5612d8:
 mov    edx,DWORD PTR [esi]
.L5612da:
 {load} cmp    eax,ecx
.L5612dc:
 je .L561313
.L5612de:
 {load} mov    edi,edi
.L5612e0:
 cmp    DWORD PTR [eax],edx
.L5612e2:
 je .L5612f8
.L5612e4:
 add    eax,0x4
.L5612e7:
 {load} cmp    eax,ecx
.L5612e9:
 jne .L5612e0
.L5612eb:
 jmp .L561313
.L5612ed:
 push   0x9fdf88
.L5612f2:
 call   DWORD PTR [0x92d168]
.L5612f8:
 mov    ecx,DWORD PTR [edi+0x4]
.L5612fb:
 lea    edx,[eax+0x4]
.L5612fe:
 {load} sub    ecx,edx
.L561300:
 and    ecx,0xfffffffc
.L561303:
 push   ecx
.L561304:
 push   edx
.L561305:
 push   eax
.L561306:
 call   DWORD PTR [0x92d4a4]
.L56130c:
 add    esp,0xc
.L56130f:
 add    DWORD PTR [edi+0x4],0xfffffffc
.L561313:
 add    esi,0x4
.L561316:
 cmp    esi,DWORD PTR [ebx+0x9c]
.L56131c:
 jne .L5612d0
.L56131e:
 mov    eax,DWORD PTR [ebx+0x98]
.L561324:
 lea    esi,[ebx+0xe8]
.L56132a:
 mov    DWORD PTR [ebx+0x9c],eax
.L561330:
 mov    edx,DWORD PTR [esi]
.L561332:
 test   edx,edx
.L561334:
 je .L56137f
.L561336:
 mov    eax,DWORD PTR [edi]
.L561338:
 mov    ecx,DWORD PTR [ebx+0x90]
.L56133e:
 {load} cmp    eax,ecx
.L561340:
 je .L56136a
.L561342:
 cmp    DWORD PTR [eax],edx
.L561344:
 je .L56134f
.L561346:
 add    eax,0x4
.L561349:
 {load} cmp    eax,ecx
.L56134b:
 jne .L561342
.L56134d:
 jmp .L56136a
.L56134f:
 mov    ecx,DWORD PTR [edi+0x4]
.L561352:
 lea    edx,[eax+0x4]
.L561355:
 {load} sub    ecx,edx
.L561357:
 and    ecx,0xfffffffc
.L56135a:
 push   ecx
.L56135b:
 push   edx
.L56135c:
 push   eax
.L56135d:
 call   DWORD PTR [0x92d4a4]
.L561363:
 add    esp,0xc
.L561366:
 add    DWORD PTR [edi+0x4],0xfffffffc
.L56136a:
 push   esi
.L56136b:
 push   ecx
.L56136c:
 push   DWORD PTR [edi]
.L56136e:
 lea    eax,[ebp-0x8]
.L561371:
 {load} mov    ecx,edi
.L561373:
 push   eax
.L561374:
 call target_5617b0
.L561379:
 mov    DWORD PTR [esi],0x0
.L56137f:
 cmp    DWORD PTR [ebx+0xe4],0x0
.L561386:
 jne .L56139c
.L561388:
 mov    eax,DWORD PTR [edi]
.L56138a:
 cmp    eax,DWORD PTR [edi+0x4]
.L56138d:
 je .L56139c
.L56138f:
 mov    ecx,DWORD PTR [eax]
.L561391:
 mov    DWORD PTR [ebx+0xe4],ecx
.L561397:
 mov    eax,DWORD PTR [ecx]
.L561399:
 call   DWORD PTR [eax+0x4]
.L56139c:
 pop    edi
.L56139d:
 pop    esi
.L56139e:
 pop    ebx
.L56139f:
 {load} mov    esp,ebp
.L5613a1:
 pop    ebp
.L5613a2:
 ret
.equ target_426800,0x426800
.equ target_5617b0,0x5617b0
