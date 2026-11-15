# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x4f49b0,0x4f4aa2); INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_script_close_upvalues
.equ REALLOCATE,0x4f7d10
.equ GC_BARRIER,0x4f2560
original_script_close_upvalues:
 push   ebp
 mov.s    ebp,esp
 push   ecx
 push   ebx
 push   esi
 push   edi
 mov.s    edi,ecx
 mov.s    ebx,edx
 cmp    DWORD PTR [edi+0x58],0x0
 mov    esi,DWORD PTR [edi+0x10]
 mov    DWORD PTR [ebp-0x4],esi
 je     .L4f4a9b
 jmp    .L4f49d0
 {disp8} lea ecx,[ecx+0]
.L4f49d0:
 mov    eax,DWORD PTR [edi+0x58]
 cmp    DWORD PTR [eax+0x8],ebx
 jb     .L4f4a9b
 mov    ecx,DWORD PTR [eax]
 mov    DWORD PTR [edi+0x58],ecx
 movzx  ecx,BYTE PTR [esi+0x14]
 lea    esi,[eax+0xc]
 movzx  edx,BYTE PTR [eax+0x5]
 not    ecx
 and    edx,0x3
 test   cl,dl
 je     .L4f4a1c
 cmp    DWORD PTR [eax+0x8],esi
 je     .L4f4a0a
 mov    edx,DWORD PTR [eax+0x10]
 mov    ecx,DWORD PTR [esi]
 mov    DWORD PTR [edx+0xc],ecx
 mov    edx,DWORD PTR [esi]
 mov    ecx,DWORD PTR [eax+0x10]
 mov    DWORD PTR [edx+0x10],ecx
.L4f4a0a:
 push   0x0
 push   0x14
 mov.s    edx,eax
 mov.s    ecx,edi
 call   REALLOCATE
 add    esp,0x8
 jmp    .L4f4a8e
.L4f4a1c:
 mov    edx,DWORD PTR [eax+0x10]
 mov    ecx,DWORD PTR [esi]
 mov    DWORD PTR [edx+0xc],ecx
 mov    edx,DWORD PTR [esi]
 mov    ecx,DWORD PTR [eax+0x10]
 mov    DWORD PTR [edx+0x10],ecx
 mov    edx,DWORD PTR [eax+0x8]
 mov    ecx,DWORD PTR [edx]
 mov    DWORD PTR [esi],ecx
 mov    ecx,DWORD PTR [edx+0x4]
 mov    DWORD PTR [esi+0x4],ecx
 mov    DWORD PTR [eax+0x8],esi
 mov    esi,DWORD PTR [edi+0x10]
 mov    ecx,DWORD PTR [esi+0x1c]
 mov    DWORD PTR [eax],ecx
 mov    DWORD PTR [esi+0x1c],eax
 mov    dl,BYTE PTR [eax+0x5]
 test   dl,0x7
 jne    .L4f4a8e
 cmp    BYTE PTR [esi+0x15],0x1
 jne    .L4f4a80
 mov    ecx,DWORD PTR [eax+0x8]
 or     dl,0x4
 mov    BYTE PTR [eax+0x5],dl
 cmp    DWORD PTR [ecx+0x4],0x4
 jl     .L4f4a8e
 mov    ecx,DWORD PTR [ecx]
 test   BYTE PTR [ecx+0x5],0x3
 je     .L4f4a8e
 test   dl,0x4
 je     .L4f4a8e
 push   ecx
 mov.s    edx,eax
 mov.s    ecx,edi
 call   GC_BARRIER
 add    esp,0x4
 jmp    .L4f4a8e
.L4f4a80:
 mov    cl,BYTE PTR [esi+0x14]
 and    dl,0xf8
 and    cl,0x3
 or.s     cl,dl
 mov    BYTE PTR [eax+0x5],cl
.L4f4a8e:
 cmp    DWORD PTR [edi+0x58],0x0
 mov    esi,DWORD PTR [ebp-0x4]
 jne    .L4f49d0
.L4f4a9b:
 pop    edi
 pop    esi
 pop    ebx
 mov.s    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
