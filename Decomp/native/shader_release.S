# Reviewed original instructions and Ghidra control flow; see SHADERS.md.
# Original VA range 0x52f4c0..0x52f55a
.intel_syntax noprefix
.code32
.text
.global original_shader_release
original_shader_release:
.L52f4c0:
 push   esi
.L52f4c1:
 push   edi
.L52f4c2:
 {load} mov    edi,ecx
.L52f4c4:
 call target_52f5b0
.L52f4c9:
 {load} xor    esi,esi
.L52f4cb:
 jmp .L52f4d0
.L52f4cd:
 {disp8} lea    ecx,[ecx+0x0]
.L52f4d0:
 mov    eax,DWORD PTR [edi+0xe18]
.L52f4d6:
 mov    ecx,DWORD PTR [esi+eax*1]
.L52f4d9:
 test   ecx,ecx
.L52f4db:
 je .L52f4e3
.L52f4dd:
 mov    eax,DWORD PTR [ecx]
.L52f4df:
 push   0x1
.L52f4e1:
 call   DWORD PTR [eax]
.L52f4e3:
 mov    eax,DWORD PTR [edi+0xe18]
.L52f4e9:
 mov    DWORD PTR [esi+eax*1],0x0
.L52f4f0:
 add    esi,0x4
.L52f4f3:
 cmp    esi,0x460
.L52f4f9:
 jb .L52f4d0
.L52f4fb:
 lea    esi,[edi+0xc]
.L52f4fe:
 mov    edi,0xe1
.L52f503:
 mov    ecx,DWORD PTR [esi]
.L52f505:
 test   ecx,ecx
.L52f507:
 je .L52f50f
.L52f509:
 mov    eax,DWORD PTR [ecx]
.L52f50b:
 push   ecx
.L52f50c:
 call   DWORD PTR [eax+0x8]
.L52f50f:
 mov    ecx,DWORD PTR [esi-0x4]
.L52f512:
 mov    DWORD PTR [esi],0x0
.L52f518:
 test   ecx,ecx
.L52f51a:
 je .L52f522
.L52f51c:
 mov    eax,DWORD PTR [ecx]
.L52f51e:
 push   ecx
.L52f51f:
 call   DWORD PTR [eax+0x8]
.L52f522:
 mov    DWORD PTR [esi-0x4],0x0
.L52f529:
 mov    ecx,DWORD PTR [esi+0x8]
.L52f52c:
 test   ecx,ecx
.L52f52e:
 je .L52f536
.L52f530:
 mov    eax,DWORD PTR [ecx]
.L52f532:
 push   ecx
.L52f533:
 call   DWORD PTR [eax+0x8]
.L52f536:
 mov    ecx,DWORD PTR [esi+0x4]
.L52f539:
 mov    DWORD PTR [esi+0x8],0x0
.L52f540:
 test   ecx,ecx
.L52f542:
 je .L52f54a
.L52f544:
 mov    eax,DWORD PTR [ecx]
.L52f546:
 push   ecx
.L52f547:
 call   DWORD PTR [eax+0x8]
.L52f54a:
 mov    DWORD PTR [esi+0x4],0x0
.L52f551:
 add    esi,0x10
.L52f554:
 dec    edi
.L52f555:
 jne .L52f503
.L52f557:
 pop    edi
.L52f558:
 pop    esi
.L52f559:
 ret
.equ target_52f5b0,0x52f5b0
