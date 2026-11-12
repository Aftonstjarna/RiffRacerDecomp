# Mechanically transcribed reference evidence; not high-level recovery.
# Original Game.exe SHA-256: 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Original VA [0x47ad90,0x47aeb6); complete function, no padding.
.intel_syntax noprefix
.code32
.text
.equ ABS_FLOAT,0x426cf0
.global original_matrix3_absolute
original_matrix3_absolute:
 push   ebp # 0x47ad90
 mov.s    ebp,esp # 0x47ad91
 sub    esp,0x28 # 0x47ad93
 push   esi # 0x47ad96
 mov.s    esi,ecx # 0x47ad97
 push   ecx # 0x47ad99
 movss  xmm0,DWORD PTR [esi+0x28] # 0x47ad9a
 movss  DWORD PTR [esp],xmm0 # 0x47ad9f
 call ABS_FLOAT # 0x47ada4
 movss  xmm0,DWORD PTR [esi+0x24] # 0x47ada9
 fstp   DWORD PTR [ebp-0x24] # 0x47adae
 movss  DWORD PTR [esp],xmm0 # 0x47adb1
 call ABS_FLOAT # 0x47adb6
 movss  xmm0,DWORD PTR [esi+0x20] # 0x47adbb
 fstp   DWORD PTR [ebp-0x20] # 0x47adc0
 movss  DWORD PTR [esp],xmm0 # 0x47adc3
 call ABS_FLOAT # 0x47adc8
 movss  xmm0,DWORD PTR [esi+0x18] # 0x47adcd
 fstp   DWORD PTR [ebp-0x1c] # 0x47add2
 movss  DWORD PTR [esp],xmm0 # 0x47add5
 call ABS_FLOAT # 0x47adda
 movss  xmm0,DWORD PTR [esi+0x14] # 0x47addf
 fstp   DWORD PTR [ebp-0x18] # 0x47ade4
 movss  DWORD PTR [esp],xmm0 # 0x47ade7
 call ABS_FLOAT # 0x47adec
 movss  xmm0,DWORD PTR [esi+0x10] # 0x47adf1
 fstp   DWORD PTR [ebp-0x14] # 0x47adf6
 movss  DWORD PTR [esp],xmm0 # 0x47adf9
 call ABS_FLOAT # 0x47adfe
 movss  xmm0,DWORD PTR [esi+0x8] # 0x47ae03
 fstp   DWORD PTR [ebp-0x10] # 0x47ae08
 movss  DWORD PTR [esp],xmm0 # 0x47ae0b
 call ABS_FLOAT # 0x47ae10
 movss  xmm0,DWORD PTR [esi+0x4] # 0x47ae15
 fstp   DWORD PTR [ebp-0xc] # 0x47ae1a
 movss  DWORD PTR [esp],xmm0 # 0x47ae1d
 call ABS_FLOAT # 0x47ae22
 movss  xmm0,DWORD PTR [esi] # 0x47ae27
 fstp   DWORD PTR [ebp-0x8] # 0x47ae2b
 movss  DWORD PTR [esp],xmm0 # 0x47ae2e
 call ABS_FLOAT # 0x47ae33
 mov    eax,DWORD PTR [ebp+0x8] # 0x47ae38
 add    esp,0x4 # 0x47ae3b
 fstp   DWORD PTR [ebp-0x4] # 0x47ae3e
 movss  xmm0,DWORD PTR [ebp-0x4] # 0x47ae41
 movss  DWORD PTR [eax],xmm0 # 0x47ae46
 movss  xmm0,DWORD PTR [ebp-0x8] # 0x47ae4a
 movss  DWORD PTR [eax+0x4],xmm0 # 0x47ae4f
 movss  xmm0,DWORD PTR [ebp-0xc] # 0x47ae54
 movss  DWORD PTR [eax+0x8],xmm0 # 0x47ae59
 movss  xmm0,DWORD PTR [ebp-0x10] # 0x47ae5e
 mov    DWORD PTR [eax+0xc],0x0 # 0x47ae63
 movss  DWORD PTR [eax+0x10],xmm0 # 0x47ae6a
 movss  xmm0,DWORD PTR [ebp-0x14] # 0x47ae6f
 movss  DWORD PTR [eax+0x14],xmm0 # 0x47ae74
 movss  xmm0,DWORD PTR [ebp-0x18] # 0x47ae79
 movss  DWORD PTR [eax+0x18],xmm0 # 0x47ae7e
 movss  xmm0,DWORD PTR [ebp-0x1c] # 0x47ae83
 mov    DWORD PTR [eax+0x1c],0x0 # 0x47ae88
 movss  DWORD PTR [eax+0x20],xmm0 # 0x47ae8f
 movss  xmm0,DWORD PTR [ebp-0x20] # 0x47ae94
 movss  DWORD PTR [eax+0x24],xmm0 # 0x47ae99
 movss  xmm0,DWORD PTR [ebp-0x24] # 0x47ae9e
 movss  DWORD PTR [eax+0x28],xmm0 # 0x47aea3
 mov    DWORD PTR [eax+0x2c],0x0 # 0x47aea8
 pop    esi # 0x47aeaf
 mov.s    esp,ebp # 0x47aeb0
 pop    ebp # 0x47aeb2
 ret    0x4 # 0x47aeb3
.section .note.GNU-stack,"",@progbits
