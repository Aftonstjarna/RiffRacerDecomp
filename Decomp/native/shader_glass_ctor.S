# Reviewed mnemonic reconstruction of Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Ghidra recovery/00579860.txt cross-checked against original instructions.
# thiscall ECX=this; stack shader index/name/arg3; EAX=this, RET 12.
# Caller 0x53048b allocates 0xfc bytes and supplies all three arguments.
# Exact end 0x579aa9 excludes INT3 padding. Base ctor 0x5421b0;
# EH state -1 -> 0 after base, then byte state 1 at 0x5798cc.
# Saved this [ebp-0x10]; handler 0x908136 uses cookie [registration-0x10]
# and metadata 0xb7f7e8. Funclets 0x908120 -> base dtor 0x52c9f0,
# 0x908128 -> member +0xf4 cleanup 0x499d50. Unwind table 0xb7f80c
# maps state 0 to (-1,0x908120), state 1 to (0,0x908128).
# Installs Glass vtable 0xa01940, initializes identity matrix and fields,
# selects shaders from 0xbfcd04 with 16-byte stride; lookup 0x542340
# cleans 8 argument bytes, common-parameter helper 0x542230 takes ECX.
# External handlers/member cleanup, data, strings and vtable remain dependencies.
# Original VA range 0x579860..0x579aa9
.intel_syntax noprefix
.code32
.text
.global original_shader_glass_ctor
original_shader_glass_ctor:
.L579860:
 push   ebp
.L579861:
 {load} mov    ebp,esp
.L579863:
 push   0xffffffff
.L579865:
 push   0x908136
.L57986a:
 mov    eax,fs:0x0
.L579870:
 push   eax
.L579871:
 sub    esp,0x8
.L579874:
 push   esi
.L579875:
 mov    eax,[0xbaabc0]
.L57987a:
 {load} xor    eax,ebp
.L57987c:
 push   eax
.L57987d:
 lea    eax,[ebp-0xc]
.L579880:
 mov    fs:0x0,eax
.L579886:
 {load} mov    esi,ecx
.L579888:
 mov    DWORD PTR [ebp-0x10],esi
.L57988b:
 call target_5421b0
.L579890:
 mov    eax,DWORD PTR [ebp+0xc]
.L579893:
 mov    edx,DWORD PTR [ebp+0x8]
.L579896:
 mov    DWORD PTR [ebp-0x4],0x0
.L57989d:
 mov    DWORD PTR [esi],0xa01940
.L5798a3:
 mov    DWORD PTR [esi+0x58],eax
.L5798a6:
 mov    DWORD PTR [esi+0x5c],0x0
.L5798ad:
 mov    DWORD PTR [esi+0xec],edx
.L5798b3:
 mov    DWORD PTR [esi+0xf0],0x0
.L5798bd:
 mov    DWORD PTR [esi+0xf4],0x0
.L5798c7:
 mov    eax,DWORD PTR [ebp+0x10]
.L5798ca:
 {load} add    edx,edx
.L5798cc:
 mov    BYTE PTR [ebp-0x4],0x1
.L5798d0:
 mov    ecx,DWORD PTR [0xbfcd04]
.L5798d6:
 mov    BYTE PTR [esi+0xf8],0x0
.L5798dd:
 mov    DWORD PTR [esi+0xc],eax
.L5798e0:
 mov    DWORD PTR [esi+0xbc],0x0
.L5798ea:
 mov    eax,DWORD PTR [ecx+edx*8+0x8]
.L5798ee:
 mov    DWORD PTR [esi+0xb8],0x0
.L5798f8:
 mov    DWORD PTR [esi+0xb4],0x0
.L579902:
 mov    DWORD PTR [esi+0xb0],0x0
.L57990c:
 mov    DWORD PTR [esi+0xa8],0x0
.L579916:
 mov    DWORD PTR [esi+0xa4],0x0
.L579920:
 mov    DWORD PTR [esi+0xa0],0x0
.L57992a:
 mov    DWORD PTR [esi+0x9c],0x0
.L579934:
 mov    DWORD PTR [esi+0x94],0x0
.L57993e:
 mov    DWORD PTR [esi+0x90],0x0
.L579948:
 mov    DWORD PTR [esi+0x8c],0x0
.L579952:
 mov    DWORD PTR [esi+0x88],0x0
.L57995c:
 mov    DWORD PTR [esi+0xc0],0x3f800000
.L579966:
 mov    DWORD PTR [esi+0xac],0x3f800000
.L579970:
 mov    DWORD PTR [esi+0x98],0x3f800000
.L57997a:
 mov    DWORD PTR [esi+0x84],0x3f800000
.L579984:
 mov    DWORD PTR [esi+0x4],eax
.L579987:
 mov    eax,DWORD PTR [ecx+edx*8+0x10]
.L57998b:
 mov    DWORD PTR [esi+0x8],eax
.L57998e:
 mov    eax,DWORD PTR [ecx+edx*8+0xc]
.L579992:
 mov    DWORD PTR [esi+0x10],eax
.L579995:
 mov    eax,DWORD PTR [ecx+edx*8+0x14]
.L579999:
 push   0x9fe740
.L57999e:
 push   DWORD PTR [esi+0x10]
.L5799a1:
 mov    DWORD PTR [esi+0x14],eax
.L5799a4:
 call target_542340
.L5799a9:
 push   0x9fe764
.L5799ae:
 push   DWORD PTR [esi+0x10]
.L5799b1:
 mov    DWORD PTR [esi+0x60],eax
.L5799b4:
 call target_542340
.L5799b9:
 push   0x9fe754
.L5799be:
 push   DWORD PTR [esi+0x10]
.L5799c1:
 mov    DWORD PTR [esi+0x64],eax
.L5799c4:
 call target_542340
.L5799c9:
 push   0x9fe7ac
.L5799ce:
 push   DWORD PTR [esi+0x10]
.L5799d1:
 mov    DWORD PTR [esi+0x68],eax
.L5799d4:
 call target_542340
.L5799d9:
 push   0xa01690
.L5799de:
 push   DWORD PTR [esi+0x10]
.L5799e1:
 mov    DWORD PTR [esi+0x6c],eax
.L5799e4:
 call target_542340
.L5799e9:
 push   0xa017b0
.L5799ee:
 push   DWORD PTR [esi+0x10]
.L5799f1:
 mov    DWORD PTR [esi+0xc4],eax
.L5799f7:
 call target_542340
.L5799fc:
 push   0x9fe704
.L579a01:
 push   DWORD PTR [esi+0x14]
.L579a04:
 mov    DWORD PTR [esi+0x70],eax
.L579a07:
 call target_542340
.L579a0c:
 push   0x9fe6e8
.L579a11:
 push   DWORD PTR [esi+0x14]
.L579a14:
 mov    DWORD PTR [esi+0x74],eax
.L579a17:
 call target_542340
.L579a1c:
 push   0x9fe714
.L579a21:
 push   DWORD PTR [esi+0x14]
.L579a24:
 mov    DWORD PTR [esi+0x78],eax
.L579a27:
 call target_542340
.L579a2c:
 push   0xa01924
.L579a31:
 push   DWORD PTR [esi+0x14]
.L579a34:
 mov    DWORD PTR [esi+0x7c],eax
.L579a37:
 call target_542340
.L579a3c:
 push   0xa01900
.L579a41:
 push   DWORD PTR [esi+0x14]
.L579a44:
 mov    DWORD PTR [esi+0xc8],eax
.L579a4a:
 call target_542340
.L579a4f:
 push   0xa01910
.L579a54:
 push   DWORD PTR [esi+0x14]
.L579a57:
 mov    DWORD PTR [esi+0xcc],eax
.L579a5d:
 call target_542340
.L579a62:
 push   0xa018e0
.L579a67:
 push   DWORD PTR [esi+0x14]
.L579a6a:
 mov    DWORD PTR [esi+0xd4],eax
.L579a70:
 call target_542340
.L579a75:
 push   0xa018f4
.L579a7a:
 push   DWORD PTR [esi+0x14]
.L579a7d:
 mov    DWORD PTR [esi+0xd8],eax
.L579a83:
 call target_542340
.L579a88:
 {load} mov    ecx,esi
.L579a8a:
 mov    DWORD PTR [esi+0xd0],eax
.L579a90:
 call target_542230
.L579a95:
 {load} mov    eax,esi
.L579a97:
 mov    ecx,DWORD PTR [ebp-0xc]
.L579a9a:
 mov    DWORD PTR fs:0x0,ecx
.L579aa1:
 pop    ecx
.L579aa2:
 pop    esi
.L579aa3:
 {load} mov    esp,ebp
.L579aa5:
 pop    ebp
.L579aa6:
 ret    0xc
.equ target_5421b0,0x5421b0
.equ target_542230,0x542230
.equ target_542340,0x542340
