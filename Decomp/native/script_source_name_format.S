# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4eff60,0x4f00b2); excludes following INT3 padding.
.intel_syntax noprefix
.code32
.text
.global original_script_source_name_format
original_script_source_name_format:
 push   ebp
 mov.s    ebp,esp
 push   ecx
 push   ebx
 mov.s    ebx,edx
 push   esi
 mov.s    esi,ecx
 push   edi
 mov    al,BYTE PTR [ebx]
 mov    DWORD PTR [ebp-0x4],esi
 cmp    al,0x3d
 jne L4eff94
 mov    esi,DWORD PTR [ebp+0x8]
 lea    eax,[ebx+0x1]
 push   esi
 push   eax
 mov.s    edi,ecx
 push   edi
 call   DWORD PTR [0x92d3e4]
 add    esp,0xc
 mov    BYTE PTR [edi+esi*1-0x1],0x0
 pop    edi
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
L4eff94:
 cmp    al,0x40
 jne L4f0001
 mov    edx,DWORD PTR [ebp+0x8]
 inc    ebx
 mov.s    ecx,ebx
 sub    edx,0x8
 lea    edi,[ecx+0x1]
L4effa4:
 mov    al,BYTE PTR [ecx]
 inc    ecx
 test   al,al
 jne L4effa4
 sub.s    ecx,edi
 mov    BYTE PTR [esi],al
 cmp.s    ecx,edx
 jbe L4effd1
 sub.s    ecx,edx
 lea    edi,[esi-0x1]
 add.s    ebx,ecx
 {disp32} lea    ebx,[ebx+0x0]
L4effc0:
 mov    al,BYTE PTR [edi+0x1]
 lea    edi,[edi+0x1]
 test   al,al
 jne L4effc0
 mov    eax,[0x9fd70c]
 mov    DWORD PTR [edi],eax
L4effd1:
 mov.s    edx,ebx
L4effd3:
 mov    al,BYTE PTR [ebx]
 inc    ebx
 test   al,al
 jne L4effd3
 sub.s    ebx,edx
 dec    esi
 {disp8} lea ecx,[ecx+0x0]
L4effe0:
 mov    al,BYTE PTR [esi+0x1]
 inc    esi
 test   al,al
 jne L4effe0
 mov.s    edi,esi
 mov.s    ecx,ebx
 shr    ecx,0x2
 mov.s    esi,edx
 rep movs DWORD PTR es:[edi],DWORD PTR [esi]
 mov.s    ecx,ebx
 and    ecx,0x3
 rep movs BYTE PTR es:[edi],BYTE PTR [esi]
 pop    edi
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
L4f0001:
 push   0x9fd710
 push   ebx
 call   DWORD PTR [0x92d368]
 mov    ecx,DWORD PTR [ebp+0x8]
 add    esp,0x8
 movq   xmm0,QWORD PTR [0x9fd6f4]
 sub    ecx,0x11
 cmp.s    eax,ecx
 movq   QWORD PTR [esi],xmm0
 cmova  eax,ecx
 mov    cx,WORD PTR [0x9fd6fc]
 mov    WORD PTR [esi+0x8],cx
 cmp    BYTE PTR [eax+ebx*1],0x0
 je L4f005a
 push   eax
 push   ebx
 push   esi
 call   DWORD PTR [0x92d36c]
 add    esp,0xc
 lea    edi,[esi-0x1]
L4f0047:
 mov    al,BYTE PTR [edi+0x1]
 lea    edi,[edi+0x1]
 test   al,al
 jne L4f0047
 mov    eax,[0x9fd70c]
 mov    DWORD PTR [edi],eax
 jmp L4f008d
L4f005a:
 mov.s    edx,ebx
 {disp8} lea esp,[esp+0x0]
L4f0060:
 mov    al,BYTE PTR [ebx]
 inc    ebx
 test   al,al
 jne L4f0060
 sub.s    ebx,edx
 dec    esi
 {disp32} lea    ebx,[ebx+0x0]
L4f0070:
 mov    al,BYTE PTR [esi+0x1]
 inc    esi
 test   al,al
 jne L4f0070
 mov.s    edi,esi
 mov.s    ecx,ebx
 shr    ecx,0x2
 mov.s    esi,edx
 rep movs DWORD PTR es:[edi],DWORD PTR [esi]
 mov.s    ecx,ebx
 and    ecx,0x3
 rep movs BYTE PTR es:[edi],BYTE PTR [esi]
 mov    esi,DWORD PTR [ebp-0x4]
L4f008d:
 dec    esi
 mov.s    edi,edi
L4f0090:
 mov    al,BYTE PTR [esi+0x1]
 lea    esi,[esi+0x1]
 test   al,al
 jne L4f0090
 mov    ax,[0x9fd700]
 mov    WORD PTR [esi],ax
 mov    al,[0x9fd702]
 pop    edi
 mov    BYTE PTR [esi+0x2],al
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
