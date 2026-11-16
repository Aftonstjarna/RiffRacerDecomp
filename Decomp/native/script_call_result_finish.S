# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f57a0,0x4f582c); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_call_result_finish
.equ RETURN_HOOK,0x4f5680
original_script_call_result_finish:
.L4f57a0:
 push   ebp
.L4f57a1:
 mov.s    ebp,esp
.L4f57a3:
 sub    esp,0x8
.L4f57a6:
 push   ebx
.L4f57a7:
 push   esi
.L4f57a8:
 mov.s    esi,ecx
.L4f57aa:
 mov.s    ebx,edx
.L4f57ac:
 push   edi
.L4f57ad:
 mov    DWORD PTR [ebp-0x8],esi
.L4f57b0:
 test   BYTE PTR [esi+0x38],0x2
.L4f57b4:
 je     .L4f57bd
.L4f57b6:
 call   RETURN_HOOK
.L4f57bb:
 mov.s    ebx,eax
.L4f57bd:
 mov.s    edx,DWORD PTR [esi+0x14]
.L4f57c0:
 lea    ecx,[edx-0x18]
.L4f57c3:
 mov    DWORD PTR [esi+0x14],ecx
.L4f57c6:
 mov.s    edi,DWORD PTR [edx+0x10]
.L4f57c9:
 mov.s    ecx,DWORD PTR [ecx]
.L4f57cb:
 mov.s    eax,DWORD PTR [edx+0x4]
.L4f57ce:
 mov    DWORD PTR [esi+0xc],ecx
.L4f57d1:
 mov.s    ecx,DWORD PTR [edx-0xc]
.L4f57d4:
 mov    DWORD PTR [esi+0x18],ecx
.L4f57d7:
 mov.s    ecx,edi
.L4f57d9:
 mov    DWORD PTR [ebp-0x4],edi
.L4f57dc:
 test   ecx,ecx
.L4f57de:
 je     .L4f5802
.L4f57e0:
 cmp.s    ebx,DWORD PTR [esi+0x8]
.L4f57e3:
 jae    .L4f57ff
.L4f57e5:
 mov.s    edx,ebx
.L4f57e7:
 mov.s    esi,eax
.L4f57e9:
 add    eax,0x8
.L4f57ec:
 add    ebx,0x8
.L4f57ef:
 mov.s    ecx,DWORD PTR [edx]
.L4f57f1:
 mov    DWORD PTR [esi],ecx
.L4f57f3:
 mov.s    ecx,DWORD PTR [edx+0x4]
.L4f57f6:
 mov    DWORD PTR [esi+0x4],ecx
.L4f57f9:
 mov.s    esi,DWORD PTR [ebp-0x8]
.L4f57fc:
 dec    edi
.L4f57fd:
 jne    .L4f57e0
.L4f57ff:
 mov.s    ecx,DWORD PTR [ebp-0x4]
.L4f5802:
 test   edi,edi
.L4f5804:
 jle    .L4f581f
.L4f5806:
 jmp    .L4f5810
.L4f5808:
 {disp32} lea esp,[esp+0x0]
.L4f580f:
 nop
.L4f5810:
 dec    edi
.L4f5811:
 mov    DWORD PTR [eax+0x4],0x0
.L4f5818:
 add    eax,0x8
.L4f581b:
 test   edi,edi
.L4f581d:
 jg     .L4f5810
.L4f581f:
 pop    edi
.L4f5820:
 mov    DWORD PTR [esi+0x8],eax
.L4f5823:
 lea    eax,[ecx+0x1]
.L4f5826:
 pop    esi
.L4f5827:
 pop    ebx
.L4f5828:
 mov.s    esp,ebp
.L4f582a:
 pop    ebp
.L4f582b:
 ret
.section .note.GNU-stack,"",@progbits
