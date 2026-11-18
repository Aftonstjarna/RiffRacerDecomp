# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x4f1320.
.intel_syntax noprefix
.code32
.text
.global original_script_gc_visit_prototype
.equ MARK_OBJECT,0x4f0ef0
original_script_gc_visit_prototype:
 push ebx
 push esi
 mov.s esi,edx
 mov.s ebx,ecx
 push edi
 mov eax,DWORD PTR [esi+0x20]
 test eax,eax
 je L1332
 and BYTE PTR [eax+0x5],0xfc
L1332:
 xor.s edi,edi
 cmp DWORD PTR [esi+0x28],edi
 jle L1360
 {disp32} lea esp,[esp+0x0]
L1340:
 mov eax,DWORD PTR [esi+0x8]
 cmp DWORD PTR [eax+edi*8+0x4],0x4
 jl L135a
 mov edx,DWORD PTR [eax+edi*8]
 test BYTE PTR [edx+0x5],0x3
 je L135a
 mov.s ecx,ebx
 call MARK_OBJECT
L135a:
 inc edi
 cmp edi,DWORD PTR [esi+0x28]
 jl L1340
L1360:
 xor.s ecx,ecx
 cmp DWORD PTR [esi+0x24],ecx
 jle L137b
L1367:
 mov eax,DWORD PTR [esi+0x1c]
 mov eax,DWORD PTR [eax+ecx*4]
 test eax,eax
 je L1375
 and BYTE PTR [eax+0x5],0xfc
L1375:
 inc ecx
 cmp ecx,DWORD PTR [esi+0x24]
 jl L1367
L137b:
 xor.s edi,edi
 cmp DWORD PTR [esi+0x34],edi
 jle L139f
L1382:
 mov eax,DWORD PTR [esi+0x10]
 mov edx,DWORD PTR [eax+edi*4]
 test edx,edx
 je L1399
 test BYTE PTR [edx+0x5],0x3
 je L1399
 mov.s ecx,ebx
 call MARK_OBJECT
L1399:
 inc edi
 cmp edi,DWORD PTR [esi+0x34]
 jl L1382
L139f:
 xor.s ecx,ecx
 cmp DWORD PTR [esi+0x38],ecx
 jle L13bf
 xor.s edx,edx
L13a8:
 mov eax,DWORD PTR [esi+0x18]
 mov eax,DWORD PTR [edx+eax]
 test eax,eax
 je L13b6
 and BYTE PTR [eax+0x5],0xfc
L13b6:
 inc ecx
 add edx,0xc
 cmp ecx,DWORD PTR [esi+0x38]
 jl L13a8
L13bf:
 pop edi
 pop esi
 pop ebx
 ret
