# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x441040.
.intel_syntax noprefix
.code32
.text
.global original_narrow_self_replace
.equ helper_416730,0x416730
.equ helper_8f8d66,0x8f8d66
original_narrow_self_replace:
 push ebp
 mov.s ebp,esp
 push ecx
 push esi
 mov.s esi,ecx
 push edi
 mov edi,DWORD PTR [ebp+0x8]
 mov ecx,DWORD PTR [esi+0x10]
 cmp.s ecx,edi
 jb .L441386
 mov eax,DWORD PTR [ebp+0x10]
 push ebx
 mov ebx,DWORD PTR [ebp+0x14]
 mov eax,DWORD PTR [eax+0x10]
 cmp.s eax,ebx
 jb .L441386
 mov edx,DWORD PTR [ebp+0xc]
 sub.s ecx,edi
 cmp.s ecx,edx
 cmovb edx,ecx
 sub.s eax,ebx
 mov ebx,DWORD PTR [ebp+0x18]
 cmp.s eax,ebx
 mov DWORD PTR [ebp+0xc],edx
 cmovb ebx,eax
 mov eax,DWORD PTR [esi+0x10]
 sub.s eax,edx
 mov DWORD PTR [ebp-0x4],eax
 or eax,0xffffffff
 sub.s eax,ebx
 cmp eax,DWORD PTR [ebp-0x4]
 ja .L44109c
 push 0x99994c
 call DWORD PTR 0x92d168
.L44109c:
 mov eax,DWORD PTR [ebp-0x4]
 sub.s ecx,edx
 add.s eax,ebx
 mov DWORD PTR [ebp+0x18],ecx
 mov DWORD PTR [ebp-0x4],eax
 cmp DWORD PTR [esi+0x10],eax
 jae .L4410be
 push 0x0
 push eax
 mov.s ecx,esi
 call helper_416730
 mov ecx,DWORD PTR [ebp+0x18]
 mov edx,DWORD PTR [ebp+0xc]
.L4410be:
 mov eax,DWORD PTR [ebp+0x10]
 cmp.s esi,eax
 je .L44113b
 cmp DWORD PTR [esi+0x14],0x10
 jb .L4410d5
 mov edi,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],edi
 mov edi,DWORD PTR [ebp+0x8]
 jmp .L4410d8
.L4410d5:
 mov DWORD PTR [ebp+0xc],esi
.L4410d8:
 cmp DWORD PTR [esi+0x14],0x10
 jb .L4410e8
 mov edi,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x18],edi
 mov edi,DWORD PTR [ebp+0x8]
 jmp .L4410eb
.L4410e8:
 mov DWORD PTR [ebp+0x18],esi
.L4410eb:
 test ecx,ecx
 je .L44110c
 mov eax,DWORD PTR [ebp+0xc]
 add.s eax,edi
 add.s eax,edx
 push ecx
 push eax
 mov eax,DWORD PTR [ebp+0x18]
 add.s eax,edi
 add.s eax,ebx
 push eax
 call DWORD PTR 0x92d4a4
 mov eax,DWORD PTR [ebp+0x10]
 add esp,0xc
.L44110c:
 cmp DWORD PTR [eax+0x14],0x10
 jb .L441114
 mov eax,DWORD PTR [eax]
.L441114:
 cmp DWORD PTR [esi+0x14],0x10
 jb .L44111e
 mov ecx,DWORD PTR [esi]
 jmp .L441120
.L44111e:
 mov.s ecx,esi
.L441120:
 test ebx,ebx
 je .L44135b
 add eax,DWORD PTR [ebp+0x14]
 push ebx
 push eax
 lea eax,[ecx+edi*1]
 push eax
 call helper_8f8d66
 jmp .L441358
.L44113b:
 cmp.s ebx,edx
 ja .L4411b3
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L44114e
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x8],ecx
 jmp .L441151
.L44114e:
 mov DWORD PTR [ebp+0x8],esi
.L441151:
 cmp eax,0x10
 jb .L44115a
 mov ecx,DWORD PTR [esi]
 jmp .L44115c
.L44115a:
 mov.s ecx,esi
.L44115c:
 test ebx,ebx
 je .L441178
 mov eax,DWORD PTR [ebp+0x8]
 add eax,DWORD PTR [ebp+0x14]
 push ebx
 push eax
 lea eax,[ecx+edi*1]
 push eax
 call DWORD PTR 0x92d4a4
 mov edx,DWORD PTR [ebp+0xc]
 add esp,0xc
.L441178:
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L441187
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],ecx
 jmp .L44118a
.L441187:
 mov DWORD PTR [ebp+0xc],esi
.L44118a:
 cmp eax,0x10
 jb .L441193
 mov ecx,DWORD PTR [esi]
 jmp .L441195
.L441193:
 mov.s ecx,esi
.L441195:
 mov eax,DWORD PTR [ebp+0x18]
 test eax,eax
 je .L44135b
 push eax
 mov eax,DWORD PTR [ebp+0xc]
 add.s eax,edi
 add.s eax,edx
 push eax
 lea eax,[ecx+edi*1]
 add.s eax,ebx
 jmp .L441351
.L4411b3:
 cmp DWORD PTR [ebp+0x14],edi
 ja .L44122a
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L4411ca
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x8],edx
 mov edx,DWORD PTR [ebp+0xc]
 jmp .L4411cd
.L4411ca:
 mov DWORD PTR [ebp+0x8],esi
.L4411cd:
 cmp eax,0x10
 jb .L4411d9
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [ebp+0xc],eax
 jmp .L4411dc
.L4411d9:
 mov DWORD PTR [ebp+0xc],esi
.L4411dc:
 test ecx,ecx
 je .L4411fa
 mov eax,DWORD PTR [ebp+0x8]
 add.s eax,edi
 add.s eax,edx
 push ecx
 push eax
 mov eax,DWORD PTR [ebp+0xc]
 add.s eax,edi
 add.s eax,ebx
 push eax
 call DWORD PTR 0x92d4a4
 add esp,0xc
.L4411fa:
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L441206
 mov edx,DWORD PTR [esi]
 jmp .L441208
.L441206:
 mov.s edx,esi
.L441208:
 cmp eax,0x10
 jb .L441211
 mov ecx,DWORD PTR [esi]
 jmp .L441213
.L441211:
 mov.s ecx,esi
.L441213:
 test ebx,ebx
 je .L44135b
 mov eax,DWORD PTR [ebp+0x14]
 add.s eax,edx
 push ebx
 push eax
 lea eax,[ecx+edi*1]
 jmp .L441351
.L44122a:
 lea eax,[edi+edx*1]
 cmp eax,DWORD PTR [ebp+0x14]
 mov eax,DWORD PTR [esi+0x14]
 ja .L4412a9
 cmp eax,0x10
 jb .L441244
 mov edx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x8],edx
 mov edx,DWORD PTR [ebp+0xc]
 jmp .L441247
.L441244:
 mov DWORD PTR [ebp+0x8],esi
.L441247:
 cmp eax,0x10
 jb .L441253
 mov eax,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],eax
 jmp .L441256
.L441253:
 mov DWORD PTR [ebp+0x10],esi
.L441256:
 test ecx,ecx
 je .L441277
 mov eax,DWORD PTR [ebp+0x8]
 add.s eax,edi
 add.s eax,edx
 push ecx
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add.s eax,edi
 add.s eax,ebx
 push eax
 call DWORD PTR 0x92d4a4
 mov edx,DWORD PTR [ebp+0xc]
 add esp,0xc
.L441277:
 mov ecx,DWORD PTR [esi+0x14]
 cmp ecx,0x10
 jb .L441283
 mov eax,DWORD PTR [esi]
 jmp .L441285
.L441283:
 mov.s eax,esi
.L441285:
 cmp ecx,0x10
 jb .L44128e
 mov ecx,DWORD PTR [esi]
 jmp .L441290
.L44128e:
 mov.s ecx,esi
.L441290:
 test ebx,ebx
 je .L44135b
 sub.s eax,edx
 add eax,DWORD PTR [ebp+0x14]
 add.s eax,ebx
 push ebx
 push eax
 lea eax,[ecx+edi*1]
 jmp .L441351
.L4412a9:
 cmp eax,0x10
 jb .L4412b5
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],ecx
 jmp .L4412b8
.L4412b5:
 mov DWORD PTR [ebp+0x10],esi
.L4412b8:
 cmp eax,0x10
 jb .L4412c1
 mov ecx,DWORD PTR [esi]
 jmp .L4412c3
.L4412c1:
 mov.s ecx,esi
.L4412c3:
 test edx,edx
 je .L4412df
 mov eax,DWORD PTR [ebp+0x10]
 add eax,DWORD PTR [ebp+0x14]
 push edx
 push eax
 lea eax,[ecx+edi*1]
 push eax
 call DWORD PTR 0x92d4a4
 mov edx,DWORD PTR [ebp+0xc]
 add esp,0xc
.L4412df:
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L4412ee
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],ecx
 jmp .L4412f1
.L4412ee:
 mov DWORD PTR [ebp+0x10],esi
.L4412f1:
 cmp eax,0x10
 jb .L4412fa
 mov ecx,DWORD PTR [esi]
 jmp .L4412fc
.L4412fa:
 mov.s ecx,esi
.L4412fc:
 mov eax,DWORD PTR [ebp+0x18]
 test eax,eax
 je .L44131b
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add.s eax,edi
 add.s eax,edx
 push eax
 lea eax,[ecx+edi*1]
 add.s eax,ebx
 push eax
 call DWORD PTR 0x92d4a4
 add esp,0xc
.L44131b:
 mov eax,DWORD PTR [esi+0x14]
 cmp eax,0x10
 jb .L44132a
 mov ecx,DWORD PTR [esi]
 mov DWORD PTR [ebp+0x10],ecx
 jmp .L44132d
.L44132a:
 mov DWORD PTR [ebp+0x10],esi
.L44132d:
 cmp eax,0x10
 jb .L441336
 mov edx,DWORD PTR [esi]
 jmp .L441338
.L441336:
 mov.s edx,esi
.L441338:
 mov ecx,DWORD PTR [ebp+0xc]
 mov.s eax,ebx
 sub.s eax,ecx
 je .L44135b
 push eax
 mov eax,DWORD PTR [ebp+0x10]
 add eax,DWORD PTR [ebp+0x14]
 add.s eax,ebx
 push eax
 mov.s eax,edi
 add.s eax,edx
 add.s eax,ecx
.L441351:
 push eax
 call DWORD PTR 0x92d4a4
.L441358:
 add esp,0xc
.L44135b:
 cmp DWORD PTR [esi+0x14],0x10
 mov ecx,DWORD PTR [ebp-0x4]
 mov DWORD PTR [esi+0x10],ecx
 pop ebx
 jb .L441378
 mov eax,DWORD PTR [esi]
 pop edi
 mov BYTE PTR [eax+ecx*1],0x0
 mov.s eax,esi
 pop esi
 mov.s esp,ebp
 pop ebp
 ret 0x14
.L441378:
 mov.s eax,esi
 pop edi
 pop esi
 mov BYTE PTR [eax+ecx*1],0x0
 mov.s esp,ebp
 pop ebp
 ret 0x14
.L441386:
 push 0x99995c
 call DWORD PTR 0x92d16c
