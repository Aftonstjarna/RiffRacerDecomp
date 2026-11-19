.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41a110.
.global original_resource_name_normalize
original_resource_name_normalize:
.L41a110:
 push   ebp
.L41a111:
 {load} mov    ebp,esp
.L41a113:
 push   0xffffffff
.L41a115:
 push   0x8fd915
.L41a11a:
 mov    eax,fs:0x0
.L41a120:
 push   eax
.L41a121:
 sub    esp,0x14
.L41a124:
 push   ebx
.L41a125:
 push   esi
.L41a126:
 push   edi
.L41a127:
 mov    eax,ds:0xbaabc0
.L41a12c:
 {load} xor    eax,ebp
.L41a12e:
 push   eax
.L41a12f:
 lea    eax,[ebp-0xc]
.L41a132:
 mov    fs:0x0,eax
.L41a138:
 {load} mov    edi,ecx
.L41a13a:
 mov    DWORD PTR [ebp-0x1c],edi
.L41a13d:
 mov    DWORD PTR [ebp-0x4],0x0
.L41a144:
 mov    DWORD PTR [ebp-0x14],0x0
.L41a14b:
 mov    DWORD PTR [edi+0x14],0xf
.L41a152:
 mov    DWORD PTR [edi+0x10],0x0
.L41a159:
 mov    BYTE PTR [edi],0x0
.L41a15c:
 cmp    BYTE PTR [edx],0x0
.L41a15f:
 jne .L41a165
.L41a161:
 {load} xor    ecx,ecx
.L41a163:
 jmp .L41a179
.L41a165:
 {load} mov    ecx,edx
.L41a167:
 lea    esi,[ecx+0x1]
.L41a16a:
 {disp32} lea ebx,[ebx+0x0]
.L41a170:
 mov    al,BYTE PTR [ecx]
.L41a172:
 inc    ecx
.L41a173:
 test   al,al
.L41a175:
 jne .L41a170
.L41a177:
 {load} sub ecx,esi
.L41a179:
 push   ecx
.L41a17a:
 push   edx
.L41a17b:
 {load} mov    ecx,edi
.L41a17d:
 call target_416520
.L41a182:
 mov    DWORD PTR [ebp-0x4],0x0
.L41a189:
 {load} xor    ecx,ecx
.L41a18b:
 mov    edx,DWORD PTR [edi+0x10]
.L41a18e:
 mov    DWORD PTR [ebp-0x14],0x1
.L41a195:
 mov    DWORD PTR [ebp-0x18],edx
.L41a198:
 mov    DWORD PTR [ebp-0x10],ecx
.L41a19b:
 test   edx,edx
.L41a19d:
 je .L41a247
.L41a1a3:
 cmp    DWORD PTR [edi+0x14],0x10
.L41a1a7:
 jb .L41a1ad
.L41a1a9:
 mov    eax,DWORD PTR [edi]
.L41a1ab:
 jmp .L41a1af
.L41a1ad:
 {load} mov    eax,edi
.L41a1af:
 mov    esi,DWORD PTR ds:0xc0d3f8
.L41a1b5:
 movsx  ebx,BYTE PTR [eax+ecx*1]
.L41a1b9:
 test   esi,esi
.L41a1bb:
 jne .L41a20c
.L41a1bd:
 push   0x58
.L41a1bf:
 call   DWORD PTR ds:0x92d4b4
.L41a1c5:
 {load} mov    esi,eax
.L41a1c7:
 add    esp,0x4
.L41a1ca:
 mov    DWORD PTR [ebp-0x20],esi
.L41a1cd:
 mov    DWORD PTR [ebp-0x4],0x1
.L41a1d4:
 test   esi,esi
.L41a1d6:
 je .L41a1fa
.L41a1d8:
 push   0xbaac48
.L41a1dd:
 lea    ecx,[esi+0x4]
.L41a1e0:
 mov    WORD PTR [esi],0x100
.L41a1e5:
 mov    BYTE PTR [esi+0x2],0x5c
.L41a1e9:
 call target_417810
.L41a1ee:
 mov    WORD PTR [esi+0x54],0x100
.L41a1f4:
 mov    BYTE PTR [esi+0x56],0x5c
.L41a1f8:
 jmp .L41a1fc
.L41a1fa:
 {load} xor    esi,esi
.L41a1fc:
 mov    ecx,DWORD PTR [ebp-0x10]
.L41a1ff:
 mov    edx,DWORD PTR [ebp-0x18]
.L41a202:
 mov    BYTE PTR [ebp-0x4],0x0
.L41a206:
 mov    DWORD PTR ds:0xc0d3f8,esi
.L41a20c:
 cmp    BYTE PTR [esi+0x54],0x0
.L41a210:
 jne .L41a21d
.L41a212:
 lea    eax,[ebx-0x41]
.L41a215:
 cmp    eax,0x19
.L41a218:
 ja .L41a21d
.L41a21a:
 add    ebx,0x20
.L41a21d:
 cmp    BYTE PTR [esi+0x55],0x0
.L41a221:
 je .L41a22c
.L41a223:
 cmp    ebx,0x5c
.L41a226:
 jne .L41a22c
.L41a228:
 movsx  ebx,BYTE PTR [esi+0x56]
.L41a22c:
 cmp    DWORD PTR [edi+0x14],0x10
.L41a230:
 jb .L41a236
.L41a232:
 mov    eax,DWORD PTR [edi]
.L41a234:
 jmp .L41a238
.L41a236:
 {load} mov    eax,edi
.L41a238:
 mov    BYTE PTR [eax+ecx*1],bl
.L41a23b:
 inc    ecx
.L41a23c:
 mov    DWORD PTR [ebp-0x10],ecx
.L41a23f:
 {load} cmp ecx,edx
.L41a241:
 jb .L41a1a3
.L41a247:
 {load} mov    eax,edi
.L41a249:
 mov    ecx,DWORD PTR [ebp-0xc]
.L41a24c:
 mov    DWORD PTR fs:0x0,ecx
.L41a253:
 pop    ecx
.L41a254:
 pop    edi
.L41a255:
 pop    esi
.L41a256:
 pop    ebx
.L41a257:
 {load} mov    esp,ebp
.L41a259:
 pop    ebp
.L41a25a:
 ret
.equ target_416520,0x416520
.equ target_417810,0x417810
