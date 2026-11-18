# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f1180.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_visit_table
.equ dep_4f0ef0,0x4f0ef0
.equ dep_4f5ca0,0x4f5ca0
original_script_gc_visit_table:
.L4f1180:
 push   ebp
.L4f1181:
 mov.s ebp,esp
.L4f1183:
 sub    esp,0x10
.L4f1186:
 push   ebx
.L4f1187:
 mov.s ebx,edx
.L4f1189:
 mov    DWORD PTR [ebp-0x4],0x0
.L4f1190:
 push   esi
.L4f1191:
 push   edi
.L4f1192:
 mov.s edi,ecx
.L4f1194:
 mov    DWORD PTR [ebp-0x8],0x0
.L4f119b:
 mov    edx,DWORD PTR [ebx+0x8]
.L4f119e:
 mov    DWORD PTR [ebp-0xc],edi
.L4f11a1:
 test.s edx,edx
.L4f11a3:
 je .L4f11b0
.L4f11a5:
 test   BYTE PTR [edx+0x5],0x3
.L4f11a9:
 je .L4f11b0
.L4f11ab:
 call dep_4f0ef0
.L4f11b0:
 mov    ecx,DWORD PTR [ebx+0x8]
.L4f11b3:
 test.s ecx,ecx
.L4f11b5:
 je .L4f1258
.L4f11bb:
 test   BYTE PTR [ecx+0x6],0x8
.L4f11bf:
 jne .L4f1258
.L4f11c5:
 push   DWORD PTR [edi+0xac]
.L4f11cb:
 mov    edx,0x3
.L4f11d0:
 call dep_4f5ca0
.L4f11d5:
 add    esp,0x4
.L4f11d8:
 mov    DWORD PTR [ebp-0x10],eax
.L4f11db:
 test.s eax,eax
.L4f11dd:
 je .L4f1258
.L4f11df:
 cmp    DWORD PTR [eax+0x4],0x4
.L4f11e3:
 jne .L4f1258
.L4f11e5:
 mov    eax,DWORD PTR [eax]
.L4f11e7:
 mov    esi,DWORD PTR [0x92d394]
.L4f11ed:
 add    eax,0x10
.L4f11f0:
 push   0x6b
.L4f11f2:
 push   eax
.L4f11f3:
 call   esi
.L4f11f5:
 mov    ecx,DWORD PTR [ebp-0x10]
.L4f11f8:
 neg    eax
.L4f11fa:
 push   0x76
.L4f11fc:
 sbb.s eax,eax
.L4f11fe:
 neg    eax
.L4f1200:
 mov    ecx,DWORD PTR [ecx]
.L4f1202:
 add    ecx,0x10
.L4f1205:
 mov    DWORD PTR [ebp-0x4],eax
.L4f1208:
 push   ecx
.L4f1209:
 call   esi
.L4f120b:
 add    esp,0x10
.L4f120e:
 neg    eax
.L4f1210:
 sbb.s edx,edx
.L4f1212:
 mov    eax,DWORD PTR [ebp-0x4]
.L4f1215:
 neg    edx
.L4f1217:
 mov    DWORD PTR [ebp-0x8],edx
.L4f121a:
 test.s eax,eax
.L4f121c:
 jne .L4f1222
.L4f121e:
 test.s edx,edx
.L4f1220:
 je .L4f1258
.L4f1222:
 mov.s cl,dl
.L4f1224:
 add.s cl,cl
.L4f1226:
 or.s cl,al
.L4f1228:
 mov    al,BYTE PTR [ebx+0x5]
.L4f122b:
 and    al,0xe7
.L4f122d:
 shl    cl,0x3
.L4f1230:
 or.s cl,al
.L4f1232:
 cmp    DWORD PTR [ebp-0x4],0x0
.L4f1236:
 mov    BYTE PTR [ebx+0x5],cl
.L4f1239:
 mov    eax,DWORD PTR [edi+0x2c]
.L4f123c:
 mov    DWORD PTR [ebx+0x18],eax
.L4f123f:
 mov    DWORD PTR [edi+0x2c],ebx
.L4f1242:
 je .L4f1254
.L4f1244:
 test.s edx,edx
.L4f1246:
 je .L4f1258
.L4f1248:
 pop    edi
.L4f1249:
 pop    esi
.L4f124a:
 mov    eax,0x1
.L4f124f:
 pop    ebx
.L4f1250:
 mov.s esp,ebp
.L4f1252:
 pop    ebp
.L4f1253:
 ret
.L4f1254:
 test.s edx,edx
.L4f1256:
 jne .L4f127f
.L4f1258:
 mov    esi,DWORD PTR [ebx+0x1c]
.L4f125b:
 test.s esi,esi
.L4f125d:
 je .L4f127f
.L4f125f:
 nop
.L4f1260:
 mov    eax,DWORD PTR [ebx+0xc]
.L4f1263:
 dec    esi
.L4f1264:
 cmp    DWORD PTR [eax+esi*8+0x4],0x4
.L4f1269:
 jl .L4f127b
.L4f126b:
 mov    edx,DWORD PTR [eax+esi*8]
.L4f126e:
 test   BYTE PTR [edx+0x5],0x3
.L4f1272:
 je .L4f127b
.L4f1274:
 mov.s ecx,edi
.L4f1276:
 call dep_4f0ef0
.L4f127b:
 test.s esi,esi
.L4f127d:
 jne .L4f1260
.L4f127f:
 mov    cl,BYTE PTR [ebx+0x7]
.L4f1282:
 mov    edi,0x1
.L4f1287:
 shl    edi,cl
.L4f1289:
 test.s edi,edi
.L4f128b:
 je .L4f12f4
.L4f128d:
 lea    eax,[edi+edi*4]
.L4f1290:
 shl    eax,0x2
.L4f1293:
 mov    esi,DWORD PTR [ebx+0x10]
.L4f1296:
 sub    eax,0x14
.L4f1299:
 add.s esi,eax
.L4f129b:
 mov    DWORD PTR [ebp-0x10],eax
.L4f129e:
 dec    edi
.L4f129f:
 cmp    DWORD PTR [esi+0x4],0x0
.L4f12a3:
 jne .L4f12b4
.L4f12a5:
 cmp    DWORD PTR [esi+0xc],0x4
.L4f12a9:
 jl .L4f12ed
.L4f12ab:
 mov    DWORD PTR [esi+0xc],0xb
.L4f12b2:
 jmp .L4f12ed
.L4f12b4:
 cmp    DWORD PTR [ebp-0x4],0x0
.L4f12b8:
 jne .L4f12d1
.L4f12ba:
 cmp    DWORD PTR [esi+0xc],0x4
.L4f12be:
 jl .L4f12d1
.L4f12c0:
 mov    edx,DWORD PTR [esi+0x8]
.L4f12c3:
 test   BYTE PTR [edx+0x5],0x3
.L4f12c7:
 je .L4f12d1
.L4f12c9:
 mov    ecx,DWORD PTR [ebp-0xc]
.L4f12cc:
 call dep_4f0ef0
.L4f12d1:
 cmp    DWORD PTR [ebp-0x8],0x0
.L4f12d5:
 jne .L4f12ed
.L4f12d7:
 cmp    DWORD PTR [esi+0x4],0x4
.L4f12db:
 jl .L4f12ed
.L4f12dd:
 mov    edx,DWORD PTR [esi]
.L4f12df:
 test   BYTE PTR [edx+0x5],0x3
.L4f12e3:
 je .L4f12ed
.L4f12e5:
 mov    ecx,DWORD PTR [ebp-0xc]
.L4f12e8:
 call dep_4f0ef0
.L4f12ed:
 mov    eax,DWORD PTR [ebp-0x10]
.L4f12f0:
 test.s edi,edi
.L4f12f2:
 jne .L4f1293
.L4f12f4:
 cmp    DWORD PTR [ebp-0x4],0x0
.L4f12f8:
 jne .L4f1248
.L4f12fe:
 cmp    DWORD PTR [ebp-0x8],0x0
.L4f1302:
 jne .L4f1248
.L4f1308:
 pop    edi
.L4f1309:
 pop    esi
.L4f130a:
 xor.s eax,eax
.L4f130c:
 pop    ebx
.L4f130d:
 mov.s esp,ebp
.L4f130f:
 pop    ebp
.L4f1310:
 ret
.section .note.GNU-stack,"",@progbits
