# Reviewed original mnemonic recovery; see UI-MATRIX.md. No copied byte arrays.
# Original VA range 0x458810..0x4588a2
.intel_syntax noprefix
.code32
.text
.global original_ui_matrix_scale
original_ui_matrix_scale:
.L458810:
 push   ebp
.L458811:
 {load} mov    ebp,esp
.L458813:
 movss  xmm0,DWORD PTR [ecx]
.L458817:
 movss  xmm1,DWORD PTR [ebp+0x8]
.L45881c:
 mulss  xmm0,xmm1
.L458820:
 movss  DWORD PTR [ecx],xmm0
.L458824:
 movss  xmm0,DWORD PTR [ecx+0x4]
.L458829:
 mulss  xmm0,xmm1
.L45882d:
 movss  DWORD PTR [ecx+0x4],xmm0
.L458832:
 movss  xmm0,DWORD PTR [ecx+0x8]
.L458837:
 mulss  xmm0,xmm1
.L45883b:
 movss  xmm1,DWORD PTR [ebp+0xc]
.L458840:
 movss  DWORD PTR [ecx+0x8],xmm0
.L458845:
 movss  xmm0,DWORD PTR [ecx+0xc]
.L45884a:
 mulss  xmm0,xmm1
.L45884e:
 movss  DWORD PTR [ecx+0xc],xmm0
.L458853:
 movss  xmm0,DWORD PTR [ecx+0x10]
.L458858:
 mulss  xmm0,xmm1
.L45885c:
 movss  DWORD PTR [ecx+0x10],xmm0
.L458861:
 movss  xmm0,DWORD PTR [ecx+0x14]
.L458866:
 mulss  xmm0,xmm1
.L45886a:
 movss  xmm1,DWORD PTR [ebp+0x10]
.L45886f:
 movss  DWORD PTR [ecx+0x14],xmm0
.L458874:
 movss  xmm0,DWORD PTR [ecx+0x18]
.L458879:
 mulss  xmm0,xmm1
.L45887d:
 movss  DWORD PTR [ecx+0x18],xmm0
.L458882:
 movss  xmm0,DWORD PTR [ecx+0x1c]
.L458887:
 mulss  xmm0,xmm1
.L45888b:
 movss  DWORD PTR [ecx+0x1c],xmm0
.L458890:
 movss  xmm0,DWORD PTR [ecx+0x20]
.L458895:
 mulss  xmm0,xmm1
.L458899:
 movss  DWORD PTR [ecx+0x20],xmm0
.L45889e:
 pop    ebp
.L45889f:
 ret    0xc
