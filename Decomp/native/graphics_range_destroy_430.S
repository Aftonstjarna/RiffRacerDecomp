# Mechanically transcribed reference evidence; NOT high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# VA 0x49d820..0x49d990 exclusive. All branches included; adjacent functions excluded.
.intel_syntax noprefix
.code32
.text
.global original_graphics_range_destroy_430
original_graphics_range_destroy_430:
.L49d820:
 push   ebp
.L49d821:
 {load} mov    ebp,esp
.L49d823:
 push   0xffffffff
.L49d825:
 push   0x902453
.L49d82a:
 mov    eax,fs:0x0
.L49d830:
 push   eax
.L49d831:
 sub    esp,0x8
.L49d834:
 push   ebx
.L49d835:
 push   esi
.L49d836:
 push   edi
.L49d837:
 mov    eax,[0xbaabc0]
.L49d83c:
 {load} xor    eax,ebp
.L49d83e:
 push   eax
.L49d83f:
 lea    eax,[ebp-0xc]
.L49d842:
 mov    fs:0x0,eax
.L49d848:
 {load} mov    eax,edx
.L49d84a:
 mov    DWORD PTR [ebp-0x10],eax
.L49d84d:
 {load} mov    edi,ecx
.L49d84f:
 mov    DWORD PTR [ebp-0x14],edi
.L49d852:
 {load} cmp    edi,eax
.L49d854:
 je .L49d97e
.L49d85a:
 {disp32} lea    ebx,[ebx+0x0]
.L49d860:
 mov    DWORD PTR [ebp-0x4],0x0
.L49d867:
 mov    ecx,DWORD PTR [edi+0x8]
.L49d86a:
 test   ecx,ecx
.L49d86c:
 je .L49d887
.L49d86e:
 mov    eax,DWORD PTR [ecx+0x4]
.L49d871:
 add    ecx,0x4
.L49d874:
 mov    eax,DWORD PTR [eax+0x4]
.L49d877:
 {load} add    ecx,eax
.L49d879:
 dec    DWORD PTR [ecx+0x4]
.L49d87c:
 jne .L49d884
.L49d87e:
 mov    eax,DWORD PTR [ecx]
.L49d880:
 push   0x1
.L49d882:
 call   DWORD PTR [eax]
.L49d884:
 mov    eax,DWORD PTR [ebp-0x10]
.L49d887:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d88e:
 mov    ebx,DWORD PTR [edi+0x4]
.L49d891:
 test   ebx,ebx
.L49d893:
 js .L49d970
.L49d899:
 mov    esi,DWORD PTR [0xc0d3dc]
.L49d89f:
 test   esi,esi
.L49d8a1:
 jne .L49d8ef
.L49d8a3:
 push   0x58
.L49d8a5:
 call   DWORD PTR [0x92d4b4]
.L49d8ab:
 {load} mov    esi,eax
.L49d8ad:
 add    esp,0x4
.L49d8b0:
 mov    DWORD PTR [ebp-0x14],esi
.L49d8b3:
 mov    DWORD PTR [ebp-0x4],0x1
.L49d8ba:
 test   esi,esi
.L49d8bc:
 je .L49d8e0
.L49d8be:
 push   0xbaac7c
.L49d8c3:
 lea    ecx,[esi+0x4]
.L49d8c6:
 mov    WORD PTR [esi],0x100
.L49d8cb:
 mov    BYTE PTR [esi+0x2],0x5c
.L49d8cf:
 call target_417810
.L49d8d4:
 mov    WORD PTR [esi+0x54],0x100
.L49d8da:
 mov    BYTE PTR [esi+0x56],0x5c
.L49d8de:
 jmp .L49d8e2
.L49d8e0:
 {load} xor    esi,esi
.L49d8e2:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d8e9:
 mov    DWORD PTR [0xc0d3dc],esi
.L49d8ef:
 mov    eax,DWORD PTR [esi+0x4]
.L49d8f2:
 movsx  ecx,WORD PTR [eax+ebx*2]
.L49d8f6:
 mov    eax,DWORD PTR [esi+0x28]
.L49d8f9:
 dec    DWORD PTR [eax+ecx*8+0x4]
.L49d8fd:
 cmp    DWORD PTR [eax+ecx*8+0x4],0x0
.L49d902:
 jne .L49d966
.L49d904:
 mov    esi,DWORD PTR [0xc0d3dc]
.L49d90a:
 mov    ebx,DWORD PTR [edi+0x4]
.L49d90d:
 test   esi,esi
.L49d90f:
 jne .L49d95d
.L49d911:
 push   0x58
.L49d913:
 call   DWORD PTR [0x92d4b4]
.L49d919:
 {load} mov    esi,eax
.L49d91b:
 add    esp,0x4
.L49d91e:
 mov    DWORD PTR [ebp-0x14],esi
.L49d921:
 mov    DWORD PTR [ebp-0x4],0x2
.L49d928:
 test   esi,esi
.L49d92a:
 je .L49d94e
.L49d92c:
 push   0xbaac7c
.L49d931:
 lea    ecx,[esi+0x4]
.L49d934:
 mov    WORD PTR [esi],0x100
.L49d939:
 mov    BYTE PTR [esi+0x2],0x5c
.L49d93d:
 call target_417810
.L49d942:
 mov    WORD PTR [esi+0x54],0x100
.L49d948:
 mov    BYTE PTR [esi+0x56],0x5c
.L49d94c:
 jmp .L49d950
.L49d94e:
 {load} xor    esi,esi
.L49d950:
 mov    DWORD PTR [ebp-0x4],0xffffffff
.L49d957:
 mov    DWORD PTR [0xc0d3dc],esi
.L49d95d:
 push   ebx
.L49d95e:
 lea    ecx,[esi+0x4]
.L49d961:
 call target_41c090
.L49d966:
 mov    eax,DWORD PTR [ebp-0x10]
.L49d969:
 mov    DWORD PTR [edi+0x4],0xffffffff
.L49d970:
 add    edi,0xc
.L49d973:
 mov    DWORD PTR [ebp-0x14],edi
.L49d976:
 {load} cmp    edi,eax
.L49d978:
 jne .L49d860
.L49d97e:
 mov    ecx,DWORD PTR [ebp-0xc]
.L49d981:
 mov    DWORD PTR fs:0x0,ecx
.L49d988:
 pop    ecx
.L49d989:
 pop    edi
.L49d98a:
 pop    esi
.L49d98b:
 pop    ebx
.L49d98c:
 {load} mov    esp,ebp
.L49d98e:
 pop    ebp
.L49d98f:
 ret
.equ target_417810,0x417810
.equ target_41c090,0x41c090
.section .note.GNU-stack,"",@progbits
