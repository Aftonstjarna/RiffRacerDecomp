# Mechanically transcribed reference evidence, not high-level recovery.
# Original SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA 0x49d990; exclusive end 0x49db00.
.intel_syntax noprefix
.code32
.text
.global original_graphics_range_destroy_434
.equ target_417810,0x417810
.equ target_41c090,0x41c090
original_graphics_range_destroy_434:
.L49d990:
 push   ebp
.L49d991:
 {load} mov    ebp,esp
.L49d993:
 push   0xffffffff
.L49d995:
 push   0x902493
.L49d99a:
 mov    eax,fs:0x0
.L49d9a0:
 push   eax
.L49d9a1:
 sub    esp,0x8
.L49d9a4:
 push   ebx
.L49d9a5:
 push   esi
.L49d9a6:
 push   edi
.L49d9a7:
 mov    eax,[0xbaabc0]
.L49d9ac:
 {load} xor    eax,ebp
.L49d9ae:
 push   eax
.L49d9af:
 lea    eax,[ebp-0xc]
.L49d9b2:
 mov    fs:0x0,eax
.L49d9b8:
 {load} mov    eax,edx
.L49d9ba:
 mov    DWORD PTR [ebp-0x10],eax
.L49d9bd:
 {load} mov    edi,ecx
.L49d9bf:
 mov    DWORD PTR [ebp-0x14],edi
.L49d9c2:
 {load} cmp    edi,eax
.L49d9c4:
 je .L49daee
.L49d9ca:
 {disp32} lea    ebx,[ebx+0x0]
.L49d9d0:
 mov    DWORD PTR [ebp-0x4],0x0
.L49d9d7:
 mov    ecx,DWORD PTR [edi+0x8]
.L49d9da:
 test   ecx,ecx
.L49d9dc:
 je .L49d9f7
.L49d9de:
 mov    eax,DWORD PTR [ecx+0x4]
.L49d9e1:
 add    ecx,0x4
.L49d9e4:
 mov    eax,DWORD PTR [eax+0x4]
.L49d9e7:
 {load} add    ecx,eax
.L49d9e9:
 dec    DWORD PTR [ecx+0x4]
.L49d9ec:
 jne .L49d9f4
.L49d9ee:
 {load} mov    eax,DWORD PTR [ecx]
.L49d9f0:
 push   0x1
.L49d9f2:
 call   DWORD PTR [eax]
.L49d9f4:
 mov    eax,DWORD PTR [ebp-0x10]
.L49d9f7:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d9fe:
 mov    ebx,DWORD PTR [edi+0x4]
.L49da01:
 test   ebx,ebx
.L49da03:
 js .L49dae0
.L49da09:
 mov    esi,DWORD PTR [0xc0d3e0]
.L49da0f:
 test   esi,esi
.L49da11:
 jne .L49da5f
.L49da13:
 push   0x58
.L49da15:
 call   DWORD PTR [0x92d4b4]
.L49da1b:
 {load} mov    esi,eax
.L49da1d:
 add    esp,0x4
.L49da20:
 mov    DWORD PTR [ebp-0x14],esi
.L49da23:
 mov    DWORD PTR [ebp-0x4],0x1
.L49da2a:
 test   esi,esi
.L49da2c:
 je .L49da50
.L49da2e:
 push   0xbaac9c
.L49da33:
 lea    ecx,[esi+0x4]
.L49da36:
 mov    WORD PTR [esi],0x100
.L49da3b:
 mov    BYTE PTR [esi+0x2],0x5c
.L49da3f:
 call target_417810
.L49da44:
 mov    WORD PTR [esi+0x54],0x100
.L49da4a:
 mov    BYTE PTR [esi+0x56],0x5c
.L49da4e:
 jmp .L49da52
.L49da50:
 {load} xor    esi,esi
.L49da52:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49da59:
 mov    DWORD PTR [0xc0d3e0],esi
.L49da5f:
 mov    eax,DWORD PTR [esi+0x4]
.L49da62:
 movsx  ecx,WORD PTR [eax+ebx*2]
.L49da66:
 mov    eax,DWORD PTR [esi+0x28]
.L49da69:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L49da6d:
 cmp    DWORD PTR [eax+ecx*8+0x4],0x0
.L49da72:
 jne .L49dad6
.L49da74:
 mov    esi,DWORD PTR [0xc0d3e0]
.L49da7a:
 mov    ebx,DWORD PTR [edi+0x4]
.L49da7d:
 test   esi,esi
.L49da7f:
 jne .L49dacd
.L49da81:
 push   0x58
.L49da83:
 call   DWORD PTR [0x92d4b4]
.L49da89:
 {load} mov    esi,eax
.L49da8b:
 add    esp,0x4
.L49da8e:
 mov    DWORD PTR [ebp-0x14],esi
.L49da91:
 mov    DWORD PTR [ebp-0x4],0x2
.L49da98:
 test   esi,esi
.L49da9a:
 je .L49dabe
.L49da9c:
 push   0xbaac9c
.L49daa1:
 lea    ecx,[esi+0x4]
.L49daa4:
 mov    WORD PTR [esi],0x100
.L49daa9:
 mov    BYTE PTR [esi+0x2],0x5c
.L49daad:
 call target_417810
.L49dab2:
 mov    WORD PTR [esi+0x54],0x100
.L49dab8:
 mov    BYTE PTR [esi+0x56],0x5c
.L49dabc:
 jmp .L49dac0
.L49dabe:
 {load} xor    esi,esi
.L49dac0:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49dac7:
 mov    DWORD PTR [0xc0d3e0],esi
.L49dacd:
 push   ebx
.L49dace:
 lea    ecx,[esi+0x4]
.L49dad1:
 call target_41c090
.L49dad6:
 mov    eax,DWORD PTR [ebp-0x10]
.L49dad9:
 mov    DWORD PTR [edi+0x4],0xffffffff
.L49dae0:
 add    edi,0xc
.L49dae3:
 mov    DWORD PTR [ebp-0x14],edi
.L49dae6:
 {load} cmp    edi,eax
.L49dae8:
 jne .L49d9d0
.L49daee:
 mov    ecx,DWORD PTR [ebp-0xc]
.L49daf1:
 mov    DWORD PTR fs:0x0,ecx
.L49daf8:
 pop    ecx
.L49daf9:
 pop    edi
.L49dafa:
 pop    esi
.L49dafb:
 pop    ebx
.L49dafc:
 {load} mov    esp,ebp
.L49dafe:
 pop    ebp
.L49daff:
 ret
.section .note.GNU-stack,"",@progbits
