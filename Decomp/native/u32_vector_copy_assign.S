# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA [0x43e240,0x43e347); four RET 4 exits; six conditional branches.
.intel_syntax noprefix
.code32
.text
.global original_u32_vector_copy_assign
.equ ALLOCATE,0x43e630
.equ COPY_ELEMENTS,0x43e770
original_u32_vector_copy_assign:
L43e240:
 push   ebp
L43e241:
 mov.s    ebp,esp
L43e243:
 sub    esp,0x8
L43e246:
 push   ebx
L43e247:
 mov.s    ebx,ecx
L43e249:
 push   esi
L43e24a:
 mov    esi,DWORD PTR [ebp+0x8]
L43e24d:
 mov    DWORD PTR [ebp-0x8],ebx
L43e250:
 cmp.s    ebx,esi
# Self assignment joins final epilogue without saving EDI.
L43e252:
 je     L43e33d
L43e258:
 mov    eax,DWORD PTR [esi+0x4]
L43e25b:
 push   edi
L43e25c:
 mov    edi,DWORD PTR [esi]
L43e25e:
 cmp.s    edi,eax
# Empty source clears logical size; allocation remains.
L43e260:
 jne    L43e272
L43e262:
 mov    eax,DWORD PTR [ebx]
L43e264:
 pop    edi
L43e265:
 mov    DWORD PTR [ebx+0x4],eax
L43e268:
 mov.s    eax,ebx
L43e26a:
 pop    esi
L43e26b:
 pop    ebx
L43e26c:
 mov.s    esp,ebp
L43e26e:
 pop    ebp
L43e26f:
 ret    0x4
L43e272:
 mov    esi,DWORD PTR [ebx+0x4]
L43e275:
 mov.s    edx,eax
L43e277:
 mov    ecx,DWORD PTR [ebx]
L43e279:
 sub.s    edx,edi
L43e27b:
 sub.s    esi,ecx
L43e27d:
 sar    edx,0x2
L43e280:
 sar    esi,0x2
L43e283:
 mov    DWORD PTR [ebp-0x4],esi
L43e286:
 cmp.s    edx,esi
L43e288:
 mov    esi,DWORD PTR [ebp+0x8]
# Compare source count with existing destination count.
L43e28b:
 ja     L43e2b9
L43e28d:
 sub.s    eax,edi
L43e28f:
 and    eax,0xfffffffc
L43e292:
 push   eax
L43e293:
 push   edi
L43e294:
 push   ecx
L43e295:
 call   DWORD PTR ds:0x92d4a4
L43e29b:
 mov    ecx,DWORD PTR [esi+0x4]
L43e29e:
 add    esp,0xc
L43e2a1:
 sub    ecx,DWORD PTR [esi]
L43e2a3:
 mov    eax,DWORD PTR [ebx]
L43e2a5:
 sar    ecx,0x2
L43e2a8:
 pop    edi
L43e2a9:
 pop    esi
L43e2aa:
 lea    eax,[eax+ecx*4]
L43e2ad:
 mov    DWORD PTR [ebx+0x4],eax
L43e2b0:
 mov.s    eax,ebx
L43e2b2:
 pop    ebx
L43e2b3:
 mov.s    esp,ebp
L43e2b5:
 pop    ebp
L43e2b6:
 ret    0x4
L43e2b9:
 mov    eax,DWORD PTR [ebx+0x8]
L43e2bc:
 sub.s    eax,ecx
L43e2be:
 sar    eax,0x2
L43e2c1:
 cmp.s    edx,eax
# Compare source count with destination capacity.
L43e2c3:
 ja     L43e309
L43e2c5:
 mov    eax,DWORD PTR [ebp-0x4]
L43e2c8:
 lea    ebx,[edi+eax*4]
L43e2cb:
 mov.s    eax,ebx
L43e2cd:
 sub.s    eax,edi
L43e2cf:
 and    eax,0xfffffffc
L43e2d2:
 push   eax
L43e2d3:
 push   edi
L43e2d4:
 mov    edi,DWORD PTR ds:0x92d4a4
L43e2da:
 push   ecx
L43e2db:
 call   edi
L43e2dd:
 mov    eax,DWORD PTR [esi+0x4]
L43e2e0:
 sub.s    eax,ebx
L43e2e2:
 sar    eax,0x2
L43e2e5:
 lea    esi,[eax*4+0x0]
L43e2ec:
 push   esi
L43e2ed:
 push   ebx
L43e2ee:
 mov    ebx,DWORD PTR [ebp-0x8]
L43e2f1:
 push   DWORD PTR [ebx+0x4]
L43e2f4:
 call   edi
L43e2f6:
 add    esp,0x18
L43e2f9:
 add.s    eax,esi
L43e2fb:
 mov    DWORD PTR [ebx+0x4],eax
L43e2fe:
 mov.s    eax,ebx
L43e300:
 pop    edi
L43e301:
 pop    esi
L43e302:
 pop    ebx
L43e303:
 mov.s    esp,ebp
L43e305:
 pop    ebp
L43e306:
 ret    0x4
# Insufficient capacity: release old allocation, reinitialize, copy.
L43e309:
 test   ecx,ecx
L43e30b:
 je     L43e317
L43e30d:
 push   ecx
L43e30e:
 call   DWORD PTR ds:0x92d4b0
L43e314:
 add    esp,0x4
L43e317:
 mov    eax,DWORD PTR [esi+0x4]
L43e31a:
 mov.s    ecx,ebx
L43e31c:
 sub    eax,DWORD PTR [esi]
L43e31e:
 sar    eax,0x2
L43e321:
 push   eax
L43e322:
 call ALLOCATE
L43e327:
 test   al,al
# Allocation initializer result in AL gates element copy.
L43e329:
 je     L43e33c
L43e32b:
 push   DWORD PTR [ebx]
L43e32d:
 mov.s    ecx,ebx
L43e32f:
 push   DWORD PTR [esi+0x4]
L43e332:
 push   DWORD PTR [esi]
L43e334:
 call COPY_ELEMENTS
L43e339:
 mov    DWORD PTR [ebx+0x4],eax
L43e33c:
 pop    edi
L43e33d:
 pop    esi
L43e33e:
 mov.s    eax,ebx
L43e340:
 pop    ebx
L43e341:
 mov.s    esp,ebp
L43e343:
 pop    ebp
L43e344:
 ret    0x4
.section .note.GNU-stack,"",@progbits
