# Reviewed mnemonic reconstruction of Game.exe SHA256
# 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Ghidra recovery/005794f0.txt cross-checked against original instructions.
# ECX=this, EAX=this result, no stack arguments (caller 0x530f4c).
# Exact end is RET at 0x57964e; following INT3 is excluded.
# Base ctor 0x5421b0 precedes EH state -1 -> 0; saved this [ebp-0x10].
# Handler 0x9080f8 uses cookie [registration-0x14], metadata 0xb7f7bc;
# unwind funclet 0x9080f0 tail-calls base destructor 0x52c9f0.
# Installs FXAA vtable 0xa01888; shader globals 0xbfcd04/0xbfcc44,
# constant-table vcall +0x24 with three callee-cleaned arguments.
# Preserves SSE unsigned dimension conversion via doubles at 0xa071b0,
# reciprocal/half-texel divisions and zero fields at +0x80/+0x84.
# External handlers, vtables, globals, strings and constants remain dependencies.
# Original VA range 0x5794f0..0x57964f
.intel_syntax noprefix
.code32
.text
.global original_shader_fxaa_ctor
original_shader_fxaa_ctor:
.L5794f0:
 push   ebp
.L5794f1:
 {load} mov    ebp,esp
.L5794f3:
 push   0xffffffff
.L5794f5:
 push   0x9080f8
.L5794fa:
 mov    eax,fs:0x0
.L579500:
 push   eax
.L579501:
 push   ecx
.L579502:
 push   ebx
.L579503:
 push   esi
.L579504:
 push   edi
.L579505:
 mov    eax,[0xbaabc0]
.L57950a:
 {load} xor    eax,ebp
.L57950c:
 push   eax
.L57950d:
 lea    eax,[ebp-0xc]
.L579510:
 mov    fs:0x0,eax
.L579516:
 {load} mov    ebx,ecx
.L579518:
 mov    DWORD PTR [ebp-0x10],ebx
.L57951b:
 call target_5421b0
.L579520:
 mov    DWORD PTR [ebp-0x4],0x0
.L579527:
 mov    esi,DWORD PTR [0xbfcd04]
.L57952d:
 mov    edi,DWORD PTR [0xbfcc44]
.L579533:
 mov    DWORD PTR [ebx],0xa01888
.L579539:
 push   0x9fe740
.L57953e:
 mov    eax,DWORD PTR [esi+0xbc8]
.L579544:
 mov    DWORD PTR [ebx+0x4],eax
.L579547:
 mov    ecx,DWORD PTR [esi+0xbcc]
.L57954d:
 mov    DWORD PTR [ebx+0x10],ecx
.L579550:
 push   0x0
.L579552:
 push   ecx
.L579553:
 mov    eax,DWORD PTR [ecx]
.L579555:
 call   DWORD PTR [eax+0x24]
.L579558:
 mov    DWORD PTR [ebx+0x58],eax
.L57955b:
 mov    eax,DWORD PTR [ebx+0x10]
.L57955e:
 push   0xa0186c
.L579563:
 push   0x0
.L579565:
 push   eax
.L579566:
 mov    ecx,DWORD PTR [eax]
.L579568:
 call   DWORD PTR [ecx+0x24]
.L57956b:
 mov    DWORD PTR [ebx+0x5c],eax
.L57956e:
 mov    eax,DWORD PTR [esi+0xbd0]
.L579574:
 mov    DWORD PTR [ebx+0x8],eax
.L579577:
 mov    ecx,DWORD PTR [esi+0xbd4]
.L57957d:
 push   0xa0186c
.L579582:
 mov    DWORD PTR [ebx+0x14],ecx
.L579585:
 push   0x0
.L579587:
 mov    eax,DWORD PTR [ecx]
.L579589:
 push   ecx
.L57958a:
 call   DWORD PTR [eax+0x24]
.L57958d:
 mov    DWORD PTR [ebx+0x60],eax
.L579590:
 mov    eax,DWORD PTR [ebx+0x14]
.L579593:
 push   0xa01878
.L579598:
 push   0x0
.L57959a:
 push   eax
.L57959b:
 mov    ecx,DWORD PTR [eax]
.L57959d:
 call   DWORD PTR [ecx+0x24]
.L5795a0:
 mov    DWORD PTR [ebx+0x64],eax
.L5795a3:
 mov    eax,DWORD PTR [edi+0x1b8]
.L5795a9:
 movss  xmm1,DWORD PTR [0xa06508]
.L5795b1:
 movd   xmm0,eax
.L5795b5:
 cvtdq2pd xmm0,xmm0
.L5795b9:
 shr    eax,0x1f
.L5795bc:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L5795c5:
 cvtpd2ps xmm0,xmm0
.L5795c9:
 movss  DWORD PTR [ebx+0x68],xmm0
.L5795ce:
 mov    eax,DWORD PTR [edi+0x1bc]
.L5795d4:
 mov    DWORD PTR [ebx+0x80],0x0
.L5795de:
 mov    DWORD PTR [ebx+0x84],0x0
.L5795e8:
 movd   xmm0,eax
.L5795ec:
 cvtdq2pd xmm0,xmm0
.L5795f0:
 shr    eax,0x1f
.L5795f3:
 addsd  xmm0,QWORD PTR [eax*8+0xa071b0]
.L5795fc:
 {load} mov    eax,ebx
.L5795fe:
 cvtpd2ps xmm0,xmm0
.L579602:
 movss  DWORD PTR [ebx+0x6c],xmm0
.L579607:
 movaps xmm0,xmm1
.L57960a:
 divss  xmm1,DWORD PTR [ebx+0x6c]
.L57960f:
 divss  xmm0,DWORD PTR [ebx+0x68]
.L579614:
 movss  DWORD PTR [ebx+0x74],xmm1
.L579619:
 movss  xmm1,DWORD PTR [0xa06558]
.L579621:
 movss  DWORD PTR [ebx+0x70],xmm0
.L579626:
 movaps xmm0,xmm1
.L579629:
 divss  xmm0,DWORD PTR [ebx+0x68]
.L57962e:
 divss  xmm1,DWORD PTR [ebx+0x6c]
.L579633:
 movss  DWORD PTR [ebx+0x78],xmm0
.L579638:
 movss  DWORD PTR [ebx+0x7c],xmm1
.L57963d:
 mov    ecx,DWORD PTR [ebp-0xc]
.L579640:
 mov    DWORD PTR fs:0x0,ecx
.L579647:
 pop    ecx
.L579648:
 pop    edi
.L579649:
 pop    esi
.L57964a:
 pop    ebx
.L57964b:
 {load} mov    esp,ebp
.L57964d:
 pop    ebp
.L57964e:
 ret
.equ target_5421b0,0x5421b0
