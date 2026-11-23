# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x562260,0x562308); instruction-contiguous extent, INT3 padding excluded.
# Wide-entry element move: memmove transfer over the 28-byte record vector used by the wide-entry reallocator. No ownership is created or destroyed here.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x562260..0x562308
.intel_syntax noprefix
.code32
.text
.global original_wide_entry_move_elements
original_wide_entry_move_elements:
.L562260:
 push   ebp
.L562261:
 {load} mov    ebp,esp
.L562263:
 push   ecx
.L562264:
 mov    DWORD PTR [ebp-0x4],edx
.L562267:
 {load} cmp    ecx,edx
.L562269:
 je .L562301
.L56226f:
 push   ebx
.L562270:
 mov    ebx,DWORD PTR [ebp+0x8]
.L562273:
 push   esi
.L562274:
 push   edi
.L562275:
 lea    esi,[ecx+0x14]
.L562278:
 lea    edi,[ebx+0x18]
.L56227b:
 jmp .L562280
.L56227d:
 {disp8} lea    ecx,[ecx+0x0]
.L562280:
 test   ebx,ebx
.L562282:
 je .L5622e8
.L562284:
 mov    eax,DWORD PTR [esi-0x14]
.L562287:
 lea    ecx,[edi-0x14]
.L56228a:
 mov    DWORD PTR [ebx],eax
.L56228c:
 {load} xor    eax,eax
.L56228e:
 mov    DWORD PTR [edi],0x7
.L562294:
 mov    DWORD PTR [edi-0x4],0x0
.L56229b:
 mov    WORD PTR [ecx],ax
.L56229e:
 cmp    DWORD PTR [esi+0x4],0x8
.L5622a2:
 jae .L5622bf
.L5622a4:
 mov    eax,DWORD PTR [esi]
.L5622a6:
 inc    eax
.L5622a7:
 je .L5622cb
.L5622a9:
 {load} add    eax,eax
.L5622ab:
 push   eax
.L5622ac:
 lea    eax,[esi-0x10]
.L5622af:
 push   eax
.L5622b0:
 push   ecx
.L5622b1:
 call   DWORD PTR [0x92d4a4]
.L5622b7:
 mov    edx,DWORD PTR [ebp-0x4]
.L5622ba:
 add    esp,0xc
.L5622bd:
 jmp .L5622cb
.L5622bf:
 mov    eax,DWORD PTR [esi-0x10]
.L5622c2:
 mov    DWORD PTR [ecx],eax
.L5622c4:
 mov    DWORD PTR [esi-0x10],0x0
.L5622cb:
 mov    eax,DWORD PTR [esi]
.L5622cd:
 mov    DWORD PTR [edi-0x4],eax
.L5622d0:
 mov    eax,DWORD PTR [esi+0x4]
.L5622d3:
 mov    DWORD PTR [edi],eax
.L5622d5:
 {load} xor    eax,eax
.L5622d7:
 mov    DWORD PTR [esi+0x4],0x7
.L5622de:
 mov    DWORD PTR [esi],0x0
.L5622e4:
 mov    WORD PTR [esi-0x10],ax
.L5622e8:
 add    esi,0x1c
.L5622eb:
 add    ebx,0x1c
.L5622ee:
 add    edi,0x1c
.L5622f1:
 lea    ecx,[esi-0x14]
.L5622f4:
 {load} cmp    ecx,edx
.L5622f6:
 jne .L562280
.L5622f8:
 pop    edi
.L5622f9:
 pop    esi
.L5622fa:
 {load} mov    eax,ebx
.L5622fc:
 pop    ebx
.L5622fd:
 {load} mov    esp,ebp
.L5622ff:
 pop    ebp
.L562300:
 ret
.L562301:
 mov    eax,DWORD PTR [ebp+0x8]
.L562304:
 {load} mov    esp,ebp
.L562306:
 pop    ebp
.L562307:
 ret
