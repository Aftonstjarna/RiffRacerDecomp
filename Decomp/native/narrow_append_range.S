# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x442170,0x442254); all four returns, padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_narrow_append_range
.equ target_416730,0x416730
.equ target_4420b0,0x4420b0
.equ target_8f8d66,0x8f8d66
original_narrow_append_range:
.L442170:
 push   ebp
.L442171:
 {load} mov    ebp,esp
.L442173:
 push   esi
.L442174:
 push   edi
.L442175:
 mov    edi,DWORD PTR [ebp+0x8]
.L442178:
 {load} mov    esi,ecx
.L44217a:
 test   edi,edi
.L44217c:
 je .L4421d5
.L44217e:
 mov    ecx,DWORD PTR [esi+0x14]
.L442181:
 cmp    ecx,0x10
.L442184:
 jb .L44218a
.L442186:
 mov    eax,DWORD PTR [esi]
.L442188:
 jmp .L44218c
.L44218a:
 {load} mov    eax,esi
.L44218c:
 {load} cmp    edi,eax
.L44218e:
 jb .L4421d5
.L442190:
 cmp    ecx,0x10
.L442193:
 jb .L442199
.L442195:
 mov    edx,DWORD PTR [esi]
.L442197:
 jmp .L44219b
.L442199:
 {load} mov    edx,esi
.L44219b:
 mov    eax,DWORD PTR [esi+0x10]
.L44219e:
 {load} add    eax,edx
.L4421a0:
 {load} cmp    eax,edi
.L4421a2:
 jbe .L4421d5
.L4421a4:
 cmp    ecx,0x10
.L4421a7:
 jb .L4421bf
.L4421a9:
 push   DWORD PTR [ebp+0xc]
.L4421ac:
 mov    eax,DWORD PTR [esi]
.L4421ae:
 {load} mov    ecx,esi
.L4421b0:
 {load} sub    edi,eax
.L4421b2:
 push   edi
.L4421b3:
 push   esi
.L4421b4:
 call target_4420b0
.L4421b9:
 pop    edi
.L4421ba:
 pop    esi
.L4421bb:
 pop    ebp
.L4421bc:
 ret    0x8
.L4421bf:
 push   DWORD PTR [ebp+0xc]
.L4421c2:
 {load} mov    eax,esi
.L4421c4:
 {load} mov    ecx,esi
.L4421c6:
 {load} sub    edi,eax
.L4421c8:
 push   edi
.L4421c9:
 push   esi
.L4421ca:
 call target_4420b0
.L4421cf:
 pop    edi
.L4421d0:
 pop    esi
.L4421d1:
 pop    ebp
.L4421d2:
 ret    0x8
.L4421d5:
 mov    ecx,DWORD PTR [esi+0x10]
.L4421d8:
 or     eax,0xffffffff
.L4421db:
 push   ebx
.L4421dc:
 mov    ebx,DWORD PTR [ebp+0xc]
.L4421df:
 {load} sub    eax,ecx
.L4421e1:
 mov    DWORD PTR [ebp+0x8],ecx
.L4421e4:
 {load} cmp    eax,ebx
.L4421e6:
 ja .L4421f3
.L4421e8:
 push   0x99994c
.L4421ed:
 call   DWORD PTR 0x92d168
.L4421f3:
 test   ebx,ebx
.L4421f5:
 je .L44224b
.L4421f7:
 lea    eax,[ecx+ebx*1]
.L4421fa:
 {load} mov    ecx,esi
.L4421fc:
 push   0x0
.L4421fe:
 push   eax
.L4421ff:
 call target_416730
.L442204:
 test   al,al
.L442206:
 je .L44224b
.L442208:
 cmp    DWORD PTR [esi+0x14],0x10
.L44220c:
 jb .L442212
.L44220e:
 mov    ecx,DWORD PTR [esi]
.L442210:
 jmp .L442214
.L442212:
 {load} mov    ecx,esi
.L442214:
 test   ebx,ebx
.L442216:
 je .L442228
.L442218:
 mov    eax,DWORD PTR [esi+0x10]
.L44221b:
 push   ebx
.L44221c:
 {load} add    eax,ecx
.L44221e:
 push   edi
.L44221f:
 push   eax
.L442220:
 call target_8f8d66
.L442225:
 add    esp,0xc
.L442228:
 mov    ecx,DWORD PTR [ebp+0x8]
.L44222b:
 {load} add    ecx,ebx
.L44222d:
 cmp    DWORD PTR [esi+0x14],0x10
.L442231:
 mov    DWORD PTR [esi+0x10],ecx
.L442234:
 jb .L442245
.L442236:
 mov    eax,DWORD PTR [esi]
.L442238:
 pop    ebx
.L442239:
 pop    edi
.L44223a:
 mov    BYTE PTR [eax+ecx*1],0x0
.L44223e:
 {load} mov    eax,esi
.L442240:
 pop    esi
.L442241:
 pop    ebp
.L442242:
 ret    0x8
.L442245:
 {load} mov    eax,esi
.L442247:
 mov    BYTE PTR [eax+ecx*1],0x0
.L44224b:
 pop    ebx
.L44224c:
 pop    edi
.L44224d:
 {load} mov    eax,esi
.L44224f:
 pop    esi
.L442250:
 pop    ebp
.L442251:
 ret    0x8
.section .note.GNU-stack,"",@progbits
