 .intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x44f160.
.global original_graphics_error_message
original_graphics_error_message:
.L44f160:
 push ebp
.L44f161:
 mov.s ebp,esp
.L44f163:
 sub esp,0xa8
.L44f169:
 mov eax,DWORD PTR [0xbaabc0]
.L44f16e:
 xor.s eax,ebp
.L44f170:
 mov DWORD PTR [ebp-0x4],eax
.L44f173:
 push esi
.L44f174:
 push edi
.L44f175:
 push 0x0
.L44f177:
 push 0x0
.L44f179:
 lea eax,[ebp-0xa4]
.L44f17f:
 mov DWORD PTR [ebp-0xa8],0x0
.L44f189:
 push eax
.L44f18a:
 push 0x0
.L44f18c:
 mov.s edi,edx
.L44f18e:
 mov.s esi,ecx
.L44f190:
 push edi
.L44f191:
 push 0x0
.L44f193:
 push 0x1300
.L44f198:
 call DWORD PTR 0x92d11c
.L44f19e:
 mov edx,DWORD PTR [ebp-0xa4]
.L44f1a4:
 test edx,edx
.L44f1a6:
 je .L44f22f
.L44f1ac:
 mov DWORD PTR [ebp-0x8c],0xf
.L44f1b6:
 mov DWORD PTR [ebp-0x90],0x0
.L44f1c0:
 mov BYTE PTR [ebp-0xa0],0x0
.L44f1c7:
 cmp BYTE PTR [edx],0x0
.L44f1ca:
 jne .L44f1d0
.L44f1cc:
 xor.s ecx,ecx
.L44f1ce:
 jmp .L44f1de
.L44f1d0:
 mov.s ecx,edx
.L44f1d2:
 lea edi,[ecx+0x1]
.L44f1d5:
 mov al,BYTE PTR [ecx]
.L44f1d7:
 inc ecx
.L44f1d8:
 test al,al
.L44f1da:
 jne .L44f1d5
.L44f1dc:
 sub.s ecx,edi
.L44f1de:
 push ecx
.L44f1df:
 push edx
.L44f1e0:
 lea ecx,[ebp-0xa0]
.L44f1e6:
 call fn_416520
.L44f1eb:
 push DWORD PTR [ebp-0xa4]
.L44f1f1:
 call DWORD PTR 0x92d0fc
.L44f1f7:
 lea eax,[ebp-0xa0]
.L44f1fd:
 mov.s ecx,esi
.L44f1ff:
 push eax
.L44f200:
 call fn_416af0
.L44f205:
 cmp DWORD PTR [ebp-0x8c],0x10
.L44f20c:
 jb .L44f289
.L44f20e:
 push DWORD PTR [ebp-0xa0]
.L44f214:
 call DWORD PTR 0x92d4b0
.L44f21a:
 add esp,0x4
.L44f21d:
 mov.s eax,esi
.L44f21f:
 pop edi
.L44f220:
 pop esi
.L44f221:
 mov ecx,DWORD PTR [ebp-0x4]
.L44f224:
 xor.s ecx,ebp
.L44f226:
 call fn_8f8958
.L44f22b:
 mov.s esp,ebp
.L44f22d:
 pop ebp
.L44f22e:
 ret
.L44f22f:
 push edi
.L44f230:
 push edi
.L44f231:
 push 0x9fa0f8
.L44f236:
 lea eax,[ebp-0x88]
.L44f23c:
 push 0x80
.L44f241:
 push eax
.L44f242:
 call fn_452ca0
.L44f247:
 mov DWORD PTR [esi+0x14],0xf
.L44f24e:
 add esp,0x14
.L44f251:
 mov DWORD PTR [esi+0x10],0x0
.L44f258:
 mov BYTE PTR [esi],0x0
.L44f25b:
 cmp BYTE PTR [ebp-0x88],0x0
.L44f262:
 jne .L44f268
.L44f264:
 xor.s ecx,ecx
.L44f266:
 jmp .L44f27a
.L44f268:
 lea ecx,[ebp-0x88]
.L44f26e:
 lea edx,[ecx+0x1]
.L44f271:
 mov al,BYTE PTR [ecx]
.L44f273:
 inc ecx
.L44f274:
 test al,al
.L44f276:
 jne .L44f271
.L44f278:
 sub.s ecx,edx
.L44f27a:
 push ecx
.L44f27b:
 lea eax,[ebp-0x88]
.L44f281:
 mov.s ecx,esi
.L44f283:
 push eax
.L44f284:
 call fn_416520
.L44f289:
 mov ecx,DWORD PTR [ebp-0x4]
.L44f28c:
 mov.s eax,esi
.L44f28e:
 pop edi
.L44f28f:
 xor.s ecx,ebp
.L44f291:
 pop esi
.L44f292:
 call fn_8f8958
.L44f297:
 mov.s esp,ebp
.L44f299:
 pop ebp
.L44f29a:
 ret
.equ fn_416520,0x416520
.equ fn_416af0,0x416af0
.equ fn_8f8958,0x8f8958
.equ fn_452ca0,0x452ca0
.section .note.GNU-stack,"",@progbits
