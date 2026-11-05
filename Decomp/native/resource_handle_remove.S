# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x41c090,0x41c286); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_resource_handle_remove
original_resource_handle_remove:
.L41c090:
 push   ebp
.L41c091:
 {load} mov    ebp,esp
.L41c093:
 push   0xffffffff
.L41c095:
 push   0x8fd938
.L41c09a:
 mov    eax,fs:0x0
.L41c0a0:
 push   eax
.L41c0a1:
 sub    esp,0x10
.L41c0a4:
 push   ebx
.L41c0a5:
 push   esi
.L41c0a6:
 push   edi
.L41c0a7:
 mov eax,[0xbaabc0]
.L41c0ac:
 {load} xor    eax,ebp
.L41c0ae:
 push   eax
.L41c0af:
 lea    eax,[ebp-0xc]
.L41c0b2:
 mov    fs:0x0,eax
# Resolve handle to dense index; remove the final live index.
.L41c0b8:
 {load} mov    esi,ecx
.L41c0ba:
 mov    eax,DWORD PTR [esi+0x4]
.L41c0bd:
 mov    ecx,DWORD PTR [esi]
.L41c0bf:
 {load} sub    eax,ecx
.L41c0c1:
 mov    edx,DWORD PTR [ebp+0x8]
.L41c0c4:
 sar    eax,1
.L41c0c6:
 {load} cmp    eax,edx
.L41c0c8:
 ja .L41c0d5
.L41c0ca:
 push   0x999ec8
.L41c0cf:
 call   DWORD PTR [0x92d16c]
.L41c0d5:
 movsx  ebx,WORD PTR [ecx+edx*2]
.L41c0d9:
 dec    WORD PTR [esi+0x30]
.L41c0dd:
 movsx  ecx,WORD PTR [esi+0x30]
.L41c0e1:
 {load} cmp    ebx,ecx
.L41c0e3:
 je .L41c1af
# Transfer last live record into the hole and repair index maps.
.L41c0e9:
 mov    eax,DWORD PTR [esi+0x10]
.L41c0ec:
 mov    edx,DWORD PTR [esi+0xc]
.L41c0ef:
 {load} sub    eax,edx
.L41c0f1:
 sar    eax,1
.L41c0f3:
 {load} cmp    eax,ecx
.L41c0f5:
 ja .L41c102
.L41c0f7:
 push   0x999ec8
.L41c0fc:
 call   DWORD PTR [0x92d16c]
.L41c102:
 mov    eax,DWORD PTR [esi+0x28]
.L41c105:
 mov    edi,DWORD PTR [esi+0x24]
.L41c108:
 {load} sub    eax,edi
.L41c10a:
 movsx  edx,WORD PTR [edx+ecx*2]
.L41c10e:
 sar    eax,0x3
.L41c111:
 mov    DWORD PTR [ebp-0x18],edx
.L41c114:
 {load} cmp    eax,ecx
.L41c116:
 ja .L41c123
.L41c118:
 push   0x999ec8
.L41c11d:
 call   DWORD PTR [0x92d16c]
.L41c123:
 mov    eax,DWORD PTR [esi+0x28]
.L41c126:
 lea    ecx,[edi+ecx*8]
.L41c129:
 {load} sub    eax,edi
.L41c12b:
 mov    DWORD PTR [ebp-0x14],ecx
.L41c12e:
 sar    eax,0x3
.L41c131:
 {load} cmp    eax,ebx
.L41c133:
 ja .L41c140
.L41c135:
 push   0x999ec8
.L41c13a:
 call   DWORD PTR [0x92d16c]
.L41c140:
 lea    edi,[edi+ebx*8]
.L41c143:
 {load} cmp    ecx,edi
.L41c145:
 je .L41c170
.L41c147:
 cmp    DWORD PTR [edi],0x0
.L41c14a:
 je .L41c156
.L41c14c:
 {load} mov    ecx,edi
.L41c14e:
 call target_426be0
.L41c153:
 mov    ecx,DWORD PTR [ebp-0x14]
.L41c156:
 mov eax,[0xbfcb38]
.L41c15b:
 mov    ecx,DWORD PTR [ecx]
.L41c15d:
 add    eax,0x4
.L41c160:
 {load} add    eax,ecx
.L41c162:
 {load} mov    ecx,edi
.L41c164:
 push   eax
.L41c165:
 call target_426a30
.L41c16a:
 mov    ecx,DWORD PTR [ebp-0x14]
.L41c16d:
 mov    edx,DWORD PTR [ebp-0x18]
.L41c170:
 mov    eax,DWORD PTR [ecx+0x4]
.L41c173:
 mov    DWORD PTR [edi+0x4],eax
.L41c176:
 mov    eax,DWORD PTR [esi+0x4]
.L41c179:
 mov    ecx,DWORD PTR [esi]
.L41c17b:
 {load} sub    eax,ecx
.L41c17d:
 sar    eax,1
.L41c17f:
 {load} cmp    eax,edx
.L41c181:
 ja .L41c18e
.L41c183:
 push   0x999ec8
.L41c188:
 call   DWORD PTR [0x92d16c]
.L41c18e:
 mov    WORD PTR [ecx+edx*2],bx
.L41c192:
 mov    eax,DWORD PTR [esi+0x10]
.L41c195:
 mov    ecx,DWORD PTR [esi+0xc]
.L41c198:
 {load} sub    eax,ecx
.L41c19a:
 sar    eax,1
.L41c19c:
 {load} cmp    eax,ebx
.L41c19e:
 ja .L41c1ab
.L41c1a0:
 push   0x999ec8
.L41c1a5:
 call   DWORD PTR [0x92d16c]
.L41c1ab:
 mov    WORD PTR [ecx+ebx*2],dx
# Ensure shared pool exists before resetting the vacated record.
.L41c1af:
 cmp    DWORD PTR [0xbfcb38],0x0
.L41c1b6:
 mov    DWORD PTR [ebp-0x1c],0x0
.L41c1bd:
 jne .L41c1f5
.L41c1bf:
 push   0x20000
.L41c1c4:
 call target_8f87c8
.L41c1c9:
 push   0x20000
.L41c1ce:
 push   0x0
.L41c1d0:
 push   eax
.L41c1d1:
 mov [0xbfcb38],eax
.L41c1d6:
 call target_8f8d7e
.L41c1db:
 mov eax,[0xbfcb38]
.L41c1e0:
 add    esp,0x10
.L41c1e3:
 mov    DWORD PTR [eax],0x80000001
.L41c1e9:
 mov eax,[0xbfcb38]
.L41c1ee:
 mov    DWORD PTR [eax+0x8],0x4000bfff
.L41c1f5:
 mov    DWORD PTR [ebp-0x18],0x0
.L41c1fc:
 mov    DWORD PTR [ebp-0x4],0x0
# Reset last record through pool helpers, then recycle the handle.
.L41c203:
 mov    eax,DWORD PTR [esi+0x28]
.L41c206:
 mov    edx,DWORD PTR [esi+0x24]
.L41c209:
 {load} sub    eax,edx
.L41c20b:
 movsx  ecx,WORD PTR [esi+0x30]
.L41c20f:
 sar    eax,0x3
.L41c212:
 {load} cmp    eax,ecx
.L41c214:
 ja .L41c221
.L41c216:
 push   0x999ec8
.L41c21b:
 call   DWORD PTR [0x92d16c]
.L41c221:
 lea    edi,[edx+ecx*8]
.L41c224:
 lea    eax,[ebp-0x1c]
.L41c227:
 {load} cmp    eax,edi
.L41c229:
 je .L41c247
.L41c22b:
 cmp    DWORD PTR [edi],0x0
.L41c22e:
 je .L41c237
.L41c230:
 {load} mov    ecx,edi
.L41c232:
 call target_426be0
.L41c237:
 mov eax,[0xbfcb38]
.L41c23c:
 {load} mov    ecx,edi
.L41c23e:
 add    eax,0x4
.L41c241:
 push   eax
.L41c242:
 call target_426a30
.L41c247:
 lea    ecx,[ebp-0x1c]
.L41c24a:
 mov    DWORD PTR [edi+0x4],0x0
.L41c251:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L41c258:
 call target_426be0
.L41c25d:
 mov    ecx,DWORD PTR [ebp+0x8]
.L41c260:
 movzx  eax,cx
.L41c263:
 lea    ecx,[esi+0x18]
.L41c266:
 mov    DWORD PTR [ebp+0x8],eax
.L41c269:
 lea    eax,[ebp+0x8]
.L41c26c:
 push   eax
.L41c26d:
 call target_41c290
# Restore Windows exception chain and callee-saved registers.
.L41c272:
 mov    ecx,DWORD PTR [ebp-0xc]
.L41c275:
 mov    DWORD PTR fs:0x0,ecx
.L41c27c:
 pop    ecx
.L41c27d:
 pop    edi
.L41c27e:
 pop    esi
.L41c27f:
 pop    ebx
.L41c280:
 {load} mov    esp,ebp
.L41c282:
 pop    ebp
.L41c283:
 ret    0x4
.equ target_41c290,0x41c290
.equ target_426a30,0x426a30
.equ target_426be0,0x426be0
.equ target_8f87c8,0x8f87c8
.equ target_8f8d7e,0x8f8d7e
.section .note.GNU-stack,"",@progbits
