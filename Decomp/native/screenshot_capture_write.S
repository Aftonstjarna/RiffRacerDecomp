# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x4a4fb0,0x4a5237); instruction-contiguous extent, INT3 padding excluded.
# Screenshot capture writer: builds the capture_%d.bmp path, writes the captured pixel buffer through the original CRT calls and preserves both failure and flush/close ordering. Reached from the application frame update.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x4a4fb0..0x4a5237
.intel_syntax noprefix
.code32
.text
.global original_screenshot_capture_write
original_screenshot_capture_write:
.L4a4fb0:
 push   ebp
.L4a4fb1:
 {load} mov    ebp,esp
.L4a4fb3:
 sub    esp,0x154
.L4a4fb9:
 mov    eax,[0xbaabc0]
.L4a4fbe:
 {load} xor    eax,ebp
.L4a4fc0:
 mov    DWORD PTR [ebp-0x4],eax
.L4a4fc3:
 push   ebx
.L4a4fc4:
 {load} mov    ebx,ecx
.L4a4fc6:
 push   esi
.L4a4fc7:
 push   edi
.L4a4fc8:
 mov    DWORD PTR [ebp-0x154],ebx
.L4a4fce:
 cmp    BYTE PTR [ebx+0x1],0x0
.L4a4fd2:
 je .L4a5226
.L4a4fd8:
 cmp    BYTE PTR [ebx+0x2],0x0
.L4a4fdc:
 mov    BYTE PTR [ebx+0x1],0x0
.L4a4fe0:
 mov    BYTE PTR [ebx+0x3],0x0
.L4a4fe4:
 je .L4a4fee
.L4a4fe6:
 mov    edx,DWORD PTR [ebx+0x450]
.L4a4fec:
 jmp .L4a4ff0
.L4a4fee:
 {load} xor    edx,edx
.L4a4ff0:
 mov    ecx,DWORD PTR [ebx+0x78]
.L4a4ff3:
 push   DWORD PTR [ebx+0x18]
.L4a4ff6:
 push   DWORD PTR [ebx+edx*4+0xc]
.L4a4ffa:
 mov    eax,DWORD PTR [ecx]
.L4a4ffc:
 push   ecx
.L4a4ffd:
 call   DWORD PTR [eax+0x80]
.L4a5003:
 test   eax,eax
.L4a5005:
 js .L4a521f
.L4a500b:
 mov    eax,DWORD PTR [ebx+0x18]
.L4a500e:
 lea    edx,[ebp-0x150]
.L4a5014:
 push   0x10
.L4a5016:
 push   0x0
.L4a5018:
 push   edx
.L4a5019:
 mov    ecx,DWORD PTR [eax]
.L4a501b:
 push   eax
.L4a501c:
 call   DWORD PTR [ecx+0x34]
.L4a501f:
 test   eax,eax
.L4a5021:
 js .L4a521f
.L4a5027:
 push   DWORD PTR [0xc0d440]
.L4a502d:
 lea    eax,[ebp-0x108]
.L4a5033:
 push   0x9fc570
.L4a5038:
 push   0x100
.L4a503d:
 push   eax
.L4a503e:
 call target_452ca0
.L4a5043:
 push   0x9fc56c
.L4a5048:
 lea    eax,[ebp-0x108]
.L4a504e:
 mov    DWORD PTR [ebp-0x144],0x0
.L4a5058:
 push   eax
.L4a5059:
 lea    eax,[ebp-0x144]
.L4a505f:
 push   eax
.L4a5060:
 call   DWORD PTR [0x92d3cc]
.L4a5066:
 add    esp,0x1c
.L4a5069:
 test   eax,eax
.L4a506b:
 jne .L4a5216
.L4a5071:
 mov    esi,DWORD PTR [ebx+0x24]
.L4a5074:
 xorps  xmm0,xmm0
.L4a5077:
 mov    ecx,DWORD PTR [ebx+0x28]
.L4a507a:
 mov    edx,0x4d42
.L4a507f:
 push   DWORD PTR [ebp-0x144]
.L4a5085:
 mov    edi,DWORD PTR [0x92d454]
.L4a508b:
 lea    eax,[esi*4+0x0]
.L4a5092:
 movq   QWORD PTR [ebp-0x118],xmm0
.L4a509a:
 imul   eax,ecx
.L4a509d:
 push   0xe
.L4a509f:
 movdqu XMMWORD PTR [ebp-0x140],xmm0
.L4a50a7:
 push   0x1
.L4a50a9:
 movdqu XMMWORD PTR [ebp-0x130],xmm0
.L4a50b1:
 add    eax,0x36
.L4a50b4:
 mov    DWORD PTR [ebp-0x110],0x0
.L4a50be:
 mov    DWORD PTR [ebp-0x116],eax
.L4a50c4:
 lea    eax,[ebp-0x118]
.L4a50ca:
 mov    WORD PTR [ebp-0x10c],0x0
.L4a50d3:
 push   eax
.L4a50d4:
 mov    DWORD PTR [ebp-0x148],ecx
.L4a50da:
 movq   QWORD PTR [ebp-0x120],xmm0
.L4a50e2:
 mov    WORD PTR [ebp-0x118],dx
.L4a50e9:
 mov    DWORD PTR [ebp-0x10e],0x36
.L4a50f3:
 mov    DWORD PTR [ebp-0x140],0x28
.L4a50fd:
 mov    DWORD PTR [ebp-0x13c],esi
.L4a5103:
 mov    DWORD PTR [ebp-0x138],ecx
.L4a5109:
 mov    DWORD PTR [ebp-0x134],0x200001
.L4a5113:
 mov    DWORD PTR [ebp-0x130],0x0
.L4a511d:
 mov    DWORD PTR [ebp-0x128],0xec4
.L4a5127:
 mov    DWORD PTR [ebp-0x124],0xec4
.L4a5131:
 call   edi
.L4a5133:
 push   DWORD PTR [ebp-0x144]
.L4a5139:
 lea    eax,[ebp-0x140]
.L4a513f:
 push   0x28
.L4a5141:
 push   0x1
.L4a5143:
 push   eax
.L4a5144:
 call   edi
.L4a5146:
 mov    eax,DWORD PTR [ebp-0x150]
.L4a514c:
 add    esp,0x20
.L4a514f:
 mov    ecx,DWORD PTR [ebp-0x148]
.L4a5155:
 {load} mov    edi,eax
.L4a5157:
 imul   edi,ecx
.L4a515a:
 add    edi,DWORD PTR [ebp-0x14c]
.L4a5160:
 test   ecx,ecx
.L4a5162:
 je .L4a51f5
.L4a5168:
 lea    ebx,[esi*4+0x0]
.L4a516f:
 nop
.L4a5170:
 {load} sub    edi,eax
.L4a5172:
 {load} xor    eax,eax
.L4a5174:
 test   esi,esi
.L4a5176:
 je .L4a51cc
.L4a5178:
 cmp    esi,0x8
.L4a517b:
 jb .L4a51b5
.L4a517d:
 movdqa xmm1,XMMWORD PTR [0xa07240]
.L4a5185:
 {load} mov    ecx,esi
.L4a5187:
 and    ecx,0x7
.L4a518a:
 {load} mov    edx,esi
.L4a518c:
 {load} sub    edx,ecx
.L4a518e:
 {load} mov    ecx,edi
.L4a5190:
 movdqu xmm0,XMMWORD PTR [ecx]
.L4a5194:
 add    eax,0x8
.L4a5197:
 lea    ecx,[ecx+0x20]
.L4a519a:
 por    xmm0,xmm1
.L4a519e:
 movdqu XMMWORD PTR [ecx-0x20],xmm0
.L4a51a3:
 movdqu xmm0,XMMWORD PTR [ecx-0x10]
.L4a51a8:
 por    xmm0,xmm1
.L4a51ac:
 movdqu XMMWORD PTR [ecx-0x10],xmm0
.L4a51b1:
 {load} cmp    eax,edx
.L4a51b3:
 jb .L4a5190
.L4a51b5:
 {load} cmp    eax,esi
.L4a51b7:
 jae .L4a51cc
.L4a51b9:
 {disp32} lea    esp,[esp+0x0]
.L4a51c0:
 or     DWORD PTR [edi+eax*4],0xff000000
.L4a51c7:
 inc    eax
.L4a51c8:
 {load} cmp    eax,esi
.L4a51ca:
 jb .L4a51c0
.L4a51cc:
 push   DWORD PTR [ebp-0x144]
.L4a51d2:
 push   ebx
.L4a51d3:
 push   0x1
.L4a51d5:
 push   edi
.L4a51d6:
 call   DWORD PTR [0x92d454]
.L4a51dc:
 add    esp,0x10
.L4a51df:
 dec    DWORD PTR [ebp-0x148]
.L4a51e5:
 je .L4a51ef
.L4a51e7:
 mov    eax,DWORD PTR [ebp-0x150]
.L4a51ed:
 jmp .L4a5170
.L4a51ef:
 mov    ebx,DWORD PTR [ebp-0x154]
.L4a51f5:
 push   DWORD PTR [ebp-0x144]
.L4a51fb:
 call   DWORD PTR [0x92d46c]
.L4a5201:
 push   DWORD PTR [ebp-0x144]
.L4a5207:
 call   DWORD PTR [0x92d470]
.L4a520d:
 add    esp,0x8
.L4a5210:
 inc    DWORD PTR [0xc0d440]
.L4a5216:
 mov    eax,DWORD PTR [ebx+0x18]
.L4a5219:
 push   eax
.L4a521a:
 mov    edx,DWORD PTR [eax]
.L4a521c:
 call   DWORD PTR [edx+0x38]
.L4a521f:
 {load} mov    ecx,ebx
.L4a5221:
 call target_4a4ea0
.L4a5226:
 mov    ecx,DWORD PTR [ebp-0x4]
.L4a5229:
 pop    edi
.L4a522a:
 pop    esi
.L4a522b:
 {load} xor    ecx,ebp
.L4a522d:
 pop    ebx
.L4a522e:
 call target_8f8958
.L4a5233:
 {load} mov    esp,ebp
.L4a5235:
 pop    ebp
.L4a5236:
 ret
.equ target_452ca0,0x452ca0
.equ target_4a4ea0,0x4a4ea0
.equ target_8f8958,0x8f8958
