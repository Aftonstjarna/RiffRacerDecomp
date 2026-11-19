.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42c5c0.
.global original_worker_view_pivot_order
original_worker_view_pivot_order:
 push   ebp
 {load} mov    ebp,esp
 sub    esp,0x10
 push   ebx
 mov    ebx,DWORD PTR [ebp+0x8]
 {load} mov    eax,ebx
 push   esi
 push   edi
 {load} mov    edi,ecx
 {load} mov    esi,edx
 {load} sub    eax,edi
 sar    eax,0x2
 cmp    eax,0x28
 jle .L42c785
 inc    eax
 cdq
 and    edx,0x7
 {load} add    eax,edx
 mov    edx,DWORD PTR [edi]
 sar    eax,0x3
 lea    ecx,[eax*8+0x0]
 mov    DWORD PTR [ebp-0x8],ecx
 lea    ecx,[eax*4+0x0]
 mov    eax,DWORD PTR [ecx+edi*1]
 mov    DWORD PTR [ebp-0xc],eax
 mov    DWORD PTR [ebp-0x4],ecx
 mov    eax,DWORD PTR [eax+0x188]
 cmp    eax,DWORD PTR [edx+0x188]
 jge .L42c61c
 mov    eax,DWORD PTR [ebp-0xc]
 mov    DWORD PTR [ecx+edi*1],edx
 mov    DWORD PTR [edi],eax
.L42c61c:
 mov    eax,DWORD PTR [ebp-0x8]
 mov    ecx,DWORD PTR [ecx+edi*1]
 mov    edx,DWORD PTR [eax+edi*1]
 mov    eax,DWORD PTR [edx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c65f
 mov    ecx,DWORD PTR [ebp-0x4]
 mov    ebx,DWORD PTR [ebp-0x8]
 mov    eax,DWORD PTR [ecx+edi*1]
 mov    DWORD PTR [ebx+edi*1],eax
 mov    ebx,DWORD PTR [ebp+0x8]
 mov    DWORD PTR [ecx+edi*1],edx
 mov    ecx,DWORD PTR [edi]
 mov    eax,DWORD PTR [edx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 mov    eax,DWORD PTR [ebp-0x4]
 jge .L42c662
 mov    DWORD PTR [eax+edi*1],ecx
 mov    DWORD PTR [edi],edx
 jmp .L42c662
.L42c65f:
 mov    eax,DWORD PTR [ebp-0x4]
.L42c662:
 {load} mov    edx,esi
 {load} sub    edx,eax
 mov    eax,DWORD PTR [esi]
 mov    DWORD PTR [ebp-0xc],eax
 mov    ecx,DWORD PTR [edx]
 mov    eax,DWORD PTR [eax+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c682
 mov    eax,DWORD PTR [ebp-0xc]
 mov    DWORD PTR [esi],ecx
 mov    DWORD PTR [edx],eax
.L42c682:
 mov    eax,DWORD PTR [ebp-0x4]
 mov    ecx,DWORD PTR [esi]
 mov    eax,DWORD PTR [eax+esi*1]
 mov    DWORD PTR [ebp-0xc],eax
 mov    eax,DWORD PTR [eax+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c6c1
 {load} mov    eax,ecx
 mov    ecx,DWORD PTR [ebp-0x4]
 mov    DWORD PTR [ecx+esi*1],eax
 mov    ecx,DWORD PTR [ebp-0xc]
 mov    DWORD PTR [esi],ecx
 mov    ebx,DWORD PTR [edx]
 mov    eax,DWORD PTR [ecx+0x188]
 cmp    eax,DWORD PTR [ebx+0x188]
 mov    ebx,DWORD PTR [ebp+0x8]
 jge .L42c6c1
 mov    eax,DWORD PTR [edx]
 mov    DWORD PTR [esi],eax
 mov    DWORD PTR [edx],ecx
.L42c6c1:
 {load} mov    edx,ebx
 {load} mov    ecx,ebx
 sub    edx,DWORD PTR [ebp-0x4]
 sub    ecx,DWORD PTR [ebp-0x8]
 mov    DWORD PTR [ebp-0x8],ecx
 mov    eax,DWORD PTR [edx]
 mov    ebx,DWORD PTR [ecx]
 mov    DWORD PTR [ebp-0x10],eax
 mov    eax,DWORD PTR [eax+0x188]
 cmp    eax,DWORD PTR [ebx+0x188]
 mov    ebx,DWORD PTR [ebp+0x8]
 jge .L42c6ef
 mov    eax,DWORD PTR [ecx]
 mov    DWORD PTR [edx],eax
 mov    eax,DWORD PTR [ebp-0x10]
 mov    DWORD PTR [ecx],eax
.L42c6ef:
 mov    eax,DWORD PTR [ebx]
 mov    ecx,DWORD PTR [edx]
 mov    DWORD PTR [ebp+0x8],eax
 mov    eax,DWORD PTR [eax+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c72f
 {load} mov    eax,ecx
 mov    ecx,DWORD PTR [ebp-0x8]
 mov    DWORD PTR [ebx],eax
 mov    ebx,DWORD PTR [ebp+0x8]
 mov    DWORD PTR [edx],ebx
 mov    eax,DWORD PTR [ecx]
 mov    DWORD PTR [ebp+0x8],eax
 {load} mov    ecx,eax
 mov    eax,DWORD PTR [ebx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 mov    ecx,DWORD PTR [ebp-0x8]
 jge .L42c72f
 mov    eax,DWORD PTR [ebp+0x8]
 mov    DWORD PTR [edx],eax
 mov    DWORD PTR [ecx],ebx
.L42c72f:
 mov    eax,DWORD PTR [ebp-0x4]
 mov    ebx,DWORD PTR [esi]
 mov    ecx,DWORD PTR [eax+edi*1]
 mov    eax,DWORD PTR [ebx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c74d
 mov    eax,DWORD PTR [ebp-0x4]
 mov    DWORD PTR [esi],ecx
 mov    DWORD PTR [eax+edi*1],ebx
.L42c74d:
 mov    ebx,DWORD PTR [edx]
 mov    ecx,DWORD PTR [esi]
 mov    eax,DWORD PTR [ebx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c7c7
 {load} mov    eax,ecx
 mov    DWORD PTR [edx],eax
 mov    edx,DWORD PTR [ebp-0x4]
 mov    DWORD PTR [esi],ebx
 mov    eax,DWORD PTR [ebx+0x188]
 mov    ecx,DWORD PTR [edx+edi*1]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c7c7
 mov    DWORD PTR [esi],ecx
 mov    DWORD PTR [edx+edi*1],ebx
 pop    edi
 pop    esi
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret
.L42c785:
 mov    edx,DWORD PTR [esi]
 mov    ecx,DWORD PTR [edi]
 mov    eax,DWORD PTR [edx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c79b
 mov    DWORD PTR [esi],ecx
 mov    DWORD PTR [edi],edx
.L42c79b:
 mov    edx,DWORD PTR [ebx]
 mov    ecx,DWORD PTR [esi]
 mov    eax,DWORD PTR [edx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c7c7
 {load} mov    eax,ecx
 mov    DWORD PTR [ebx],eax
 mov    DWORD PTR [esi],edx
 mov    ecx,DWORD PTR [edi]
 mov    eax,DWORD PTR [edx+0x188]
 cmp    eax,DWORD PTR [ecx+0x188]
 jge .L42c7c7
 mov    DWORD PTR [esi],ecx
 mov    DWORD PTR [edi],edx
.L42c7c7:
 pop    edi
 pop    esi
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret
.section .note.GNU-stack,"",@progbits
