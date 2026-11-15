# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f1090,0x4f1176); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_separate_finalizable
original_script_gc_separate_finalizable:
.L4f1090:
 push ebp
.L4f1091:
 mov.s ebp,esp
.L4f1093:
 sub esp,0x14
.L4f1096:
 mov.s eax,DWORD PTR [ecx+0x10]
.L4f1099:
 mov DWORD PTR [ebp-0xc],eax
.L4f109c:
 push esi
.L4f109d:
 push edi
.L4f109e:
 mov.s eax,DWORD PTR [eax+0x64]
.L4f10a1:
 mov.s edi,edx
.L4f10a3:
 xor.s edx,edx
.L4f10a5:
 mov DWORD PTR [ebp-0x10],edi
.L4f10a8:
 mov DWORD PTR [ebp-0x14],ecx
.L4f10ab:
 mov DWORD PTR [ebp-0x8],edx
.L4f10ae:
 mov.s esi,DWORD PTR [eax]
.L4f10b0:
 mov DWORD PTR [ebp-0x4],eax
.L4f10b3:
 test esi,esi
.L4f10b5:
 je .L4f1130
.L4f10b7:
 push ebx
.L4f10b8:
 mov bl,BYTE PTR [esi+0x5]
.L4f10bb:
 test bl,0x3
.L4f10be:
 jne .L4f10c4
.L4f10c0:
 test edi,edi
.L4f10c2:
 je .L4f111e
.L4f10c4:
 test bl,0x8
.L4f10c7:
 jne .L4f111e
.L4f10c9:
 mov.s edx,DWORD PTR [esi+0x8]
.L4f10cc:
 test edx,edx
.L4f10ce:
 je .L4f1117
.L4f10d0:
 test BYTE PTR [edx+0x6],0x4
.L4f10d4:
 jne .L4f1117
.L4f10d6:
 mov.s eax,DWORD PTR [ecx+0x10]
.L4f10d9:
 mov cl,BYTE PTR [edx+0x7]
.L4f10dc:
 mov.s edi,DWORD PTR [eax+0xa8]
.L4f10e2:
 mov eax,0x1
.L4f10e7:
 shl eax,cl
.L4f10e9:
 dec eax
.L4f10ea:
 and eax,DWORD PTR [edi+0x8]
.L4f10ed:
 lea ecx,[eax+eax*4]
.L4f10f0:
 mov.s eax,DWORD PTR [edx+0x10]
.L4f10f3:
 lea eax,[eax+ecx*4]
.L4f10f6:
 cmp DWORD PTR [eax+0xc],0x4
.L4f10fa:
 jne .L4f1101
.L4f10fc:
 cmp DWORD PTR [eax+0x8],edi
.L4f10ff:
 je .L4f110d
.L4f1101:
 mov.s eax,DWORD PTR [eax+0x10]
.L4f1104:
 test eax,eax
.L4f1106:
 jne .L4f10f6
.L4f1108:
 mov eax,0x99a41c
.L4f110d:
 cmp DWORD PTR [eax+0x4],0x0
.L4f1111:
 jne .L4f1138
.L4f1113:
 or BYTE PTR [edx+0x6],0x4
.L4f1117:
 or BYTE PTR [esi+0x5],0x8
.L4f111b:
 mov.s edx,DWORD PTR [ebp-0x8]
.L4f111e:
 mov.s eax,esi
.L4f1120:
 mov DWORD PTR [ebp-0x4],eax
.L4f1123:
 mov.s esi,DWORD PTR [eax]
.L4f1125:
 mov.s edi,DWORD PTR [ebp-0x10]
.L4f1128:
 mov.s ecx,DWORD PTR [ebp-0x14]
.L4f112b:
 test esi,esi
.L4f112d:
 jne .L4f10b8
.L4f112f:
 pop ebx
.L4f1130:
 pop edi
.L4f1131:
 mov.s eax,edx
.L4f1133:
 pop esi
.L4f1134:
 mov.s esp,ebp
.L4f1136:
 pop ebp
.L4f1137:
 ret
.L4f1138:
 mov.s edx,DWORD PTR [ebp-0x8]
.L4f113b:
 or bl,0x8
.L4f113e:
 mov.s ecx,DWORD PTR [ebp-0x4]
.L4f1141:
 add edx,0x18
.L4f1144:
 add.s edx,DWORD PTR [esi+0x10]
.L4f1147:
 mov.s eax,DWORD PTR [esi]
.L4f1149:
 mov BYTE PTR [esi+0x5],bl
.L4f114c:
 mov DWORD PTR [ecx],eax
.L4f114e:
 mov.s ecx,DWORD PTR [ebp-0xc]
.L4f1151:
 mov DWORD PTR [ebp-0x8],edx
.L4f1154:
 mov.s eax,DWORD PTR [ecx+0x30]
.L4f1157:
 test eax,eax
.L4f1159:
 jne .L4f1165
.L4f115b:
 mov.s eax,DWORD PTR [ebp-0x4]
.L4f115e:
 mov DWORD PTR [esi],esi
.L4f1160:
 mov DWORD PTR [ecx+0x30],esi
.L4f1163:
 jmp .L4f1123
.L4f1165:
 mov.s eax,DWORD PTR [eax]
.L4f1167:
 mov DWORD PTR [esi],eax
.L4f1169:
 mov.s eax,DWORD PTR [ecx+0x30]
.L4f116c:
 mov DWORD PTR [eax],esi
.L4f116e:
 mov.s eax,DWORD PTR [ebp-0x4]
.L4f1171:
 mov DWORD PTR [ecx+0x30],esi
.L4f1174:
 jmp .L4f1123
.section .note.GNU-stack,"",@progbits
