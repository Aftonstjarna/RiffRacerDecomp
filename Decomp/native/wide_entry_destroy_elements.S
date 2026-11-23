# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x5620e0,0x562255); instruction-contiguous extent, INT3 padding excluded.
# Wide-entry element destruction: releases each 28-byte record through the original delete/destructor path after a failed or replaced allocation. Used by wide-entry reallocation.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x5620e0..0x562255
.intel_syntax noprefix
.code32
.text
.global original_wide_entry_destroy_elements
original_wide_entry_destroy_elements:
.L5620e0:
 push   edi
.L5620e1:
 {load} mov    edi,edx
.L5620e3:
 {load} cmp    ecx,edi
.L5620e5:
 je .L56211e
.L5620e7:
 push   ebx
.L5620e8:
 mov    ebx,DWORD PTR [0x92d4b0]
.L5620ee:
 push   esi
.L5620ef:
 lea    esi,[ecx+0x18]
.L5620f2:
 cmp    DWORD PTR [esi],0x8
.L5620f5:
 jb .L5620ff
.L5620f7:
 push   DWORD PTR [esi-0x14]
.L5620fa:
 call   ebx
.L5620fc:
 add    esp,0x4
.L5620ff:
 {load} xor    eax,eax
.L562101:
 mov    DWORD PTR [esi],0x7
.L562107:
 mov    DWORD PTR [esi-0x4],0x0
.L56210e:
 mov    WORD PTR [esi-0x14],ax
.L562112:
 add    esi,0x1c
.L562115:
 lea    eax,[esi-0x18]
.L562118:
 {load} cmp    eax,edi
.L56211a:
 jne .L5620f2
.L56211c:
 pop    esi
.L56211d:
 pop    ebx
.L56211e:
 pop    edi
.L56211f:
 ret
.L562120:
 push   ebp
.L562121:
 {load} mov    ebp,esp
.L562123:
 sub    esp,0x18
.L562126:
 push   ebx
.L562127:
 push   esi
.L562128:
 {load} mov    esi,edx
.L56212a:
 mov    eax,0x92492493
.L56212f:
 push   edi
.L562130:
 {load} mov    edi,ecx
.L562132:
 mov    ecx,DWORD PTR [ebp+0x8]
.L562135:
 {load} sub    esi,edi
.L562137:
 mov    DWORD PTR [ebp-0x10],ecx
.L56213a:
 imul   esi
.L56213c:
 {load} sub    ecx,edi
.L56213e:
 mov    DWORD PTR [ebp-0xc],edi
.L562141:
 {load} add    edx,esi
.L562143:
 sar    edx,0x4
.L562146:
 {load} mov    eax,edx
.L562148:
 shr    eax,0x1f
.L56214b:
 {load} add    eax,edx
.L56214d:
 mov    DWORD PTR [ebp-0x14],eax
.L562150:
 mov    eax,0x92492493
.L562155:
 imul   ecx
.L562157:
 {load} add    edx,ecx
.L562159:
 mov    ecx,DWORD PTR [ebp-0x14]
.L56215c:
 sar    edx,0x4
.L56215f:
 {load} mov    esi,ecx
.L562161:
 {load} mov    edi,edx
.L562163:
 shr    edi,0x1f
.L562166:
 {load} add    edi,edx
.L562168:
 mov    DWORD PTR [ebp-0x8],edi
.L56216b:
 {load} mov    ebx,edi
.L56216d:
 test   ecx,ecx
.L56216f:
 je .L562181
.L562171:
 {load} mov    eax,ebx
.L562173:
 {load} mov    ebx,esi
.L562175:
 cdq
.L562176:
 idiv   esi
.L562178:
 {load} mov    esi,edx
.L56217a:
 test   edx,edx
.L56217c:
 jne .L562171
.L56217e:
 mov    DWORD PTR [ebp-0x8],ebx
.L562181:
 {load} cmp    ebx,edi
.L562183:
 jge .L56224e
.L562189:
 test   ebx,ebx
.L56218b:
 jle .L56224e
.L562191:
 lea    edx,[ecx*8+0x0]
.L562198:
 {load} sub    edx,ecx
.L56219a:
 lea    eax,[ebx*8+0x0]
.L5621a1:
 mov    ecx,DWORD PTR [ebp-0xc]
.L5621a4:
 shl    edx,0x2
.L5621a7:
 {load} sub    eax,ebx
.L5621a9:
 mov    DWORD PTR [ebp-0x18],edx
.L5621ac:
 lea    ebx,[ecx+eax*4]
.L5621af:
 mov    DWORD PTR [ebp-0x4],ebx
.L5621b2:
 lea    esi,[ebx+edx*1]
.L5621b5:
 {load} mov    edi,ebx
.L5621b7:
 cmp    esi,DWORD PTR [ebp-0x10]
.L5621ba:
 cmove  esi,ecx
.L5621bd:
 {disp8} lea    ecx,[ecx+0x0]
.L5621c0:
 {load} cmp    edi,esi
.L5621c2:
 je .L5621f9
.L5621c4:
 mov    ecx,DWORD PTR [edi]
.L5621c6:
 lea    ebx,[esi+0x4]
.L5621c9:
 mov    eax,DWORD PTR [esi]
.L5621cb:
 mov    DWORD PTR [edi],eax
.L5621cd:
 add    edi,0x4
.L5621d0:
 mov    DWORD PTR [esi],ecx
.L5621d2:
 {load} cmp    edi,ebx
.L5621d4:
 je .L5621f6
.L5621d6:
 push   ebx
.L5621d7:
 {load} mov    ecx,edi
.L5621d9:
 call target_562310
.L5621de:
 mov    ecx,DWORD PTR [edi+0x10]
.L5621e1:
 mov    eax,DWORD PTR [ebx+0x10]
.L5621e4:
 mov    DWORD PTR [edi+0x10],eax
.L5621e7:
 mov    DWORD PTR [ebx+0x10],ecx
.L5621ea:
 mov    ecx,DWORD PTR [edi+0x14]
.L5621ed:
 mov    eax,DWORD PTR [ebx+0x14]
.L5621f0:
 mov    DWORD PTR [edi+0x14],eax
.L5621f3:
 mov    DWORD PTR [ebx+0x14],ecx
.L5621f6:
 mov    ebx,DWORD PTR [ebp-0x4]
.L5621f9:
 mov    ecx,DWORD PTR [ebp-0x10]
.L5621fc:
 mov    eax,0x92492493
.L562201:
 {load} sub    ecx,esi
.L562203:
 {load} mov    edi,esi
.L562205:
 imul   ecx
.L562207:
 {load} add    edx,ecx
.L562209:
 mov    ecx,DWORD PTR [ebp-0x14]
.L56220c:
 sar    edx,0x4
.L56220f:
 {load} mov    eax,edx
.L562211:
 shr    eax,0x1f
.L562214:
 {load} add    eax,edx
.L562216:
 mov    edx,DWORD PTR [ebp-0x18]
.L562219:
 {load} cmp    ecx,eax
.L56221b:
 jge .L562224
.L56221d:
 mov    ecx,DWORD PTR [ebp-0xc]
.L562220:
 {load} add    esi,edx
.L562222:
 jmp .L562235
.L562224:
 {load} sub    ecx,eax
.L562226:
 lea    eax,[ecx*8+0x0]
.L56222d:
 {load} sub    eax,ecx
.L56222f:
 mov    ecx,DWORD PTR [ebp-0xc]
.L562232:
 lea    esi,[ecx+eax*4]
.L562235:
 {load} cmp    esi,ebx
.L562237:
 jne .L5621c0
.L562239:
 mov    eax,DWORD PTR [ebp-0x8]
.L56223c:
 sub    ebx,0x1c
.L56223f:
 dec    eax
.L562240:
 mov    DWORD PTR [ebp-0x4],ebx
.L562243:
 mov    DWORD PTR [ebp-0x8],eax
.L562246:
 test   eax,eax
.L562248:
 jg .L5621b2
.L56224e:
 pop    edi
.L56224f:
 pop    esi
.L562250:
 pop    ebx
.L562251:
 {load} mov    esp,ebp
.L562253:
 pop    ebp
.L562254:
 ret
.equ target_562310,0x562310
