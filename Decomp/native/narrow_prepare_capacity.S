# Mechanically transcribed reference evidence, not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x416730,0x4167de); three returns; adjacent INT3 padding excluded.
.intel_syntax noprefix
.code32
.text
.global original_narrow_prepare_capacity
.equ target_416890,0x416890
.equ target_8f8d66,0x8f8d66
original_narrow_prepare_capacity:
.L416730:
 push   ebp
.L416731:
 {load} mov    ebp,esp
.L416733:
 push   esi
.L416734:
 push   edi
.L416735:
 mov    edi,DWORD PTR [ebp+0x8]
.L416738:
 {load} mov    esi,ecx
.L41673a:
 cmp    edi,0xfffffffe
.L41673d:
 jbe .L41674a
.L41673f:
 push   0x99994c
.L416744:
 call   DWORD PTR [0x92d168]
.L41674a:
 mov    eax,DWORD PTR [esi+0x14]
.L41674d:
 {load} cmp    eax,edi
.L41674f:
 jae .L416768
.L416751:
 push   DWORD PTR [esi+0x10]
.L416754:
 push   edi
.L416755:
 call target_416890
.L41675a:
 {load} xor    eax,eax
.L41675c:
 {load} cmp    eax,edi
.L41675e:
 pop    edi
.L41675f:
 {load} sbb    eax,eax
.L416761:
 neg    eax
.L416763:
 pop    esi
.L416764:
 pop    ebp
.L416765:
 ret    0x8
.L416768:
 cmp    BYTE PTR [ebp+0xc],0x0
.L41676c:
 je .L4167bf
.L41676e:
 cmp    edi,0x10
.L416771:
 jae .L4167bf
.L416773:
 push   ebx
.L416774:
 mov    ebx,DWORD PTR [esi+0x10]
.L416777:
 {load} cmp    edi,ebx
.L416779:
 cmovb  ebx,edi
.L41677c:
 cmp    eax,0x10
.L41677f:
 jb .L4167a2
.L416781:
 mov    eax,DWORD PTR [esi]
.L416783:
 mov    DWORD PTR [ebp+0xc],eax
.L416786:
 test   ebx,ebx
.L416788:
 je .L416798
.L41678a:
 push   ebx
.L41678b:
 push   eax
.L41678c:
 push   esi
.L41678d:
 call target_8f8d66
.L416792:
 mov    eax,DWORD PTR [ebp+0xc]
.L416795:
 add    esp,0xc
.L416798:
 push   eax
.L416799:
 call   DWORD PTR [0x92d4b0]
.L41679f:
 add    esp,0x4
.L4167a2:
 {load} xor    eax,eax
.L4167a4:
 mov    DWORD PTR [esi+0x10],ebx
.L4167a7:
 mov    DWORD PTR [esi+0x14],0xf
.L4167ae:
 {load} cmp    eax,edi
.L4167b0:
 mov    BYTE PTR [ebx+esi*1],0x0
.L4167b4:
 pop    ebx
.L4167b5:
 {load} sbb    eax,eax
.L4167b7:
 pop    edi
.L4167b8:
 neg    eax
.L4167ba:
 pop    esi
.L4167bb:
 pop    ebp
.L4167bc:
 ret    0x8
.L4167bf:
 test   edi,edi
.L4167c1:
 jne .L4167d0
.L4167c3:
 mov    DWORD PTR [esi+0x10],edi
.L4167c6:
 cmp    eax,0x10
.L4167c9:
 jb .L4167cd
.L4167cb:
 mov    esi,DWORD PTR [esi]
.L4167cd:
 mov    BYTE PTR [esi],0x0
.L4167d0:
 {load} xor    eax,eax
.L4167d2:
 {load} cmp    eax,edi
.L4167d4:
 pop    edi
.L4167d5:
 {load} sbb    eax,eax
.L4167d7:
 neg    eax
.L4167d9:
 pop    esi
.L4167da:
 pop    ebp
.L4167db:
 ret    0x8
.section .note.GNU-stack,"",@progbits
