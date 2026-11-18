.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x42c7d0.
.global original_worker_view_heap_prepare
original_worker_view_heap_prepare:
.L42c7d0:
 push   ebp
.L42c7d1:
 {load} mov    ebp,esp
.L42c7d3:
 sub    esp,0x10
.L42c7d6:
 push   ebx
.L42c7d7:
 push   esi
.L42c7d8:
 {load} mov    esi,ecx
.L42c7da:
 {load} mov    ecx,edx
.L42c7dc:
 {load} sub    ecx,esi
.L42c7de:
 sar    ecx,0x2
.L42c7e1:
 {load} mov    eax,ecx
.L42c7e3:
 mov    DWORD PTR [ebp-0x4],ecx
.L42c7e6:
 cdq
.L42c7e7:
 {load} sub    eax,edx
.L42c7e9:
 {load} mov    ebx,eax
.L42c7eb:
 sar    ebx,1
.L42c7ed:
 test   ebx,ebx
.L42c7ef:
 jle    .L42c8af
.L42c7f5:
 lea    edx,[ebx*2+0x2]
.L42c7fc:
 push   edi
.L42c7fd:
 {disp8} lea    ecx,[ecx+0x0]
.L42c800:
 mov    eax,DWORD PTR [esi+ebx*4-0x4]
.L42c804:
 dec    ebx
.L42c805:
 sub    edx,0x2
.L42c808:
 mov    DWORD PTR [ebp-0xc],eax
.L42c80b:
 mov    DWORD PTR [ebp-0x8],ebx
.L42c80e:
 {load} mov    edi,ebx
.L42c810:
 mov    DWORD PTR [ebp-0x10],edx
.L42c813:
 {load} mov    eax,edx
.L42c815:
 {load} cmp    edx,ecx
.L42c817:
 jge    .L42c84f
.L42c819:
 mov    ebx,DWORD PTR [ebp-0x4]
.L42c81c:
 {disp8} lea    esp,[esp+0x0]
.L42c820:
 mov    ecx,DWORD PTR [esi+eax*4]
.L42c823:
 mov    edx,DWORD PTR [esi+eax*4-0x4]
.L42c827:
 mov    ecx,DWORD PTR [ecx+0x188]
.L42c82d:
 cmp    ecx,DWORD PTR [edx+0x188]
.L42c833:
 jge    .L42c836
.L42c835:
 dec    eax
.L42c836:
 mov    ecx,DWORD PTR [esi+eax*4]
.L42c839:
 mov    DWORD PTR [esi+edi*4],ecx
.L42c83c:
 {load} mov    edi,eax
.L42c83e:
 lea    eax,[eax*2+0x2]
.L42c845:
 {load} cmp    eax,ebx
.L42c847:
 jl     .L42c820
.L42c849:
 mov    ebx,DWORD PTR [ebp-0x8]
.L42c84c:
 mov    ecx,DWORD PTR [ebp-0x4]
.L42c84f:
 {load} cmp    eax,ecx
.L42c851:
 jne    .L42c85d
.L42c853:
 mov    eax,DWORD PTR [esi+ecx*4-0x4]
.L42c857:
 mov    DWORD PTR [esi+edi*4],eax
.L42c85a:
 lea    edi,[ecx-0x1]
.L42c85d:
 lea    eax,[edi-0x1]
.L42c860:
 cdq
.L42c861:
 {load} sub    eax,edx
.L42c863:
 {load} mov    ecx,eax
.L42c865:
 sar    ecx,1
.L42c867:
 {load} cmp    ebx,edi
.L42c869:
 jge    .L42c89a
.L42c86b:
 jmp    .L42c870
.L42c86d:
 {disp8} lea    ecx,[ecx+0x0]
.L42c870:
 mov    edx,DWORD PTR [esi+ecx*4]
.L42c873:
 mov    ebx,DWORD PTR [ebp-0xc]
.L42c876:
 mov    eax,DWORD PTR [edx+0x188]
.L42c87c:
 cmp    eax,DWORD PTR [ebx+0x188]
.L42c882:
 mov    ebx,DWORD PTR [ebp-0x8]
.L42c885:
 jge    .L42c89a
.L42c887:
 lea    eax,[ecx-0x1]
.L42c88a:
 mov    DWORD PTR [esi+edi*4],edx
.L42c88d:
 cdq
.L42c88e:
 {load} mov    edi,ecx
.L42c890:
 {load} sub    eax,edx
.L42c892:
 {load} mov    ecx,eax
.L42c894:
 sar    ecx,1
.L42c896:
 {load} cmp    ebx,edi
.L42c898:
 jl     .L42c870
.L42c89a:
 mov    eax,DWORD PTR [ebp-0xc]
.L42c89d:
 mov    ecx,DWORD PTR [ebp-0x4]
.L42c8a0:
 mov    edx,DWORD PTR [ebp-0x10]
.L42c8a3:
 mov    DWORD PTR [esi+edi*4],eax
.L42c8a6:
 test   ebx,ebx
.L42c8a8:
 jg     .L42c800
.L42c8ae:
 pop    edi
.L42c8af:
 pop    esi
.L42c8b0:
 pop    ebx
.L42c8b1:
 {load} mov    esp,ebp
.L42c8b3:
 pop    ebp
.L42c8b4:
 ret
.section .note.GNU-stack,"",@progbits
