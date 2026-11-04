# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original /tmp/cloud-worker-review/dispatch.asm, private read-only
# Ghidra export /tmp/cloud-worker-review/exports/0048d9c0.txt and .rdata.
# ECX=this from vtable slot +8 / registered thread thunk 0x48dc50.
# Preserves EBP/EBX/ESI/EDI, aligns stack to 8, returns EAX=0, plain ret.
# Wait +0x14, check stop +0x1c; search backward for final dot in SSO string
# +0x20 (length +0x30/capacity +0x34). 0x416160 returns storage begin.
# _stricmp literals at 0x9fbe0c/14 are .flac/.fla -> 0x4f9080;
# 0x9fbdfc .mp3 -> 0x4f87e0; 0x9fbe04 .ogg -> 0x4f8a90.
# Supported build has NO M4A branch. External strings/vtables not claimed.
# Decoder ABI: ECX=input +0x44, EDX=length +0x48, caller-popped stack
# arguments: OGG (+0x38,&+0x3c,&+0x40); MP3 adds &+0x40,&+0x4c,
# &+0x40,&+0x14c,&+0x40. FLAC uses &+0x40 in stack slots 1 and 3.
# Preserve repeated output pointers and AL success, not inferred prototypes.
# After recognized decode, operator delete[] input and clear +0x44/+0x48;
# AL=0 also deletes output +0x3c and clears +0x3c/+0x40. Unknown/no dot
# bypasses that cleanup. Signal +0x18, wait again, stop returns zero.
# No local SEH/unwind cleanup: decoder exceptions propagate unchanged.
# 0x48d9ed LEA is original internal alignment, not data; all returns and
# loop edges checked. Bounds end at ret, exclude following INT3 padding.
# Original VA range 0x48d9c0..0x48db7c
.intel_syntax noprefix
.code32
.text
.global original_decode_worker_dispatch
original_decode_worker_dispatch:
.L48d9c0:
 push   ebp
.L48d9c1:
 {load} mov    ebp,esp
.L48d9c3:
 and    esp,0xfffffff8
.L48d9c6:
 sub    esp,0xc
.L48d9c9:
 push   ebx
.L48d9ca:
 push   esi
.L48d9cb:
 push   edi
.L48d9cc:
 {load} mov    edi,ecx
.L48d9ce:
 push   0xffffffff
.L48d9d0:
 push   DWORD PTR [edi+0x14]
.L48d9d3:
 call   DWORD PTR [0x92d124]
.L48d9d9:
 cmp    BYTE PTR [edi+0x1c],0x0
.L48d9dd:
 jne .L48db73
.L48d9e3:
 mov    BYTE PTR [esp+0x14],0x2e
.L48d9e8:
 or     ecx,0xffffffff
.L48d9eb:
 jmp .L48d9f0
.L48d9ed:
 {disp8} lea    ecx,[ecx+0x0]
.L48d9f0:
 mov    eax,DWORD PTR [edi+0x30]
.L48d9f3:
 cmp    eax,0x1
.L48d9f6:
 jb .L48db50
.L48d9fc:
 dec    eax
.L48d9fd:
 cmp    eax,0xffffffff
.L48da00:
 cmova  eax,ecx
.L48da03:
 cmp    DWORD PTR [edi+0x34],0x10
.L48da07:
 jb .L48da0e
.L48da09:
 mov    ecx,DWORD PTR [edi+0x20]
.L48da0c:
 jmp .L48da11
.L48da0e:
 lea    ecx,[edi+0x20]
.L48da11:
 lea    esi,[ecx+eax*1]
.L48da14:
 cmp    BYTE PTR [esi],0x2e
.L48da17:
 jne .L48da23
.L48da19:
 mov    al,BYTE PTR [esi]
.L48da1b:
 lea    ecx,[esp+0x14]
.L48da1f:
 cmp    al,BYTE PTR [ecx]
.L48da21:
 je .L48da36
.L48da23:
 lea    ecx,[edi+0x20]
.L48da26:
 call target_416160
.L48da2b:
 {load} cmp    esi,eax
.L48da2d:
 je .L48db50
.L48da33:
 dec    esi
.L48da34:
 jmp .L48da14
.L48da36:
 cmp    DWORD PTR [edi+0x34],0x10
.L48da3a:
 jb .L48da41
.L48da3c:
 mov    eax,DWORD PTR [edi+0x20]
.L48da3f:
 jmp .L48da44
.L48da41:
 lea    eax,[edi+0x20]
.L48da44:
 {load} sub    esi,eax
.L48da46:
 cmp    esi,0xffffffff
.L48da49:
 je .L48db50
.L48da4f:
 cmp    DWORD PTR [edi+0x34],0x10
.L48da53:
 jb .L48da5a
.L48da55:
 mov    eax,DWORD PTR [edi+0x20]
.L48da58:
 jmp .L48da5d
.L48da5a:
 lea    eax,[edi+0x20]
.L48da5d:
 {load} add    esi,eax
.L48da5f:
 push   0x9fbe0c
.L48da64:
 push   esi
.L48da65:
 call   DWORD PTR [0x92d3d8]
.L48da6b:
 add    esp,0x8
.L48da6e:
 test   eax,eax
.L48da70:
 je .L48daef
.L48da72:
 push   0x9fbe14
.L48da77:
 push   esi
.L48da78:
 call   DWORD PTR [0x92d3d8]
.L48da7e:
 add    esp,0x8
.L48da81:
 test   eax,eax
.L48da83:
 je .L48daef
.L48da85:
 push   0x9fbdfc
.L48da8a:
 push   esi
.L48da8b:
 call   DWORD PTR [0x92d3d8]
.L48da91:
 add    esp,0x8
.L48da94:
 test   eax,eax
.L48da96:
 je .L48daca
.L48da98:
 push   0x9fbe04
.L48da9d:
 push   esi
.L48da9e:
 call   DWORD PTR [0x92d3d8]
.L48daa4:
 add    esp,0x8
.L48daa7:
 test   eax,eax
.L48daa9:
 jne .L48db50
.L48daaf:
 mov    edx,DWORD PTR [edi+0x48]
.L48dab2:
 lea    eax,[edi+0x40]
.L48dab5:
 mov    ecx,DWORD PTR [edi+0x44]
.L48dab8:
 lea    esi,[edi+0x3c]
.L48dabb:
 push   eax
.L48dabc:
 push   esi
.L48dabd:
 push   DWORD PTR [edi+0x38]
.L48dac0:
 call target_4f8a90
.L48dac5:
 add    esp,0xc
.L48dac8:
 jmp .L48db13
.L48daca:
 mov    edx,DWORD PTR [edi+0x48]
.L48dacd:
 lea    ecx,[edi+0x40]
.L48dad0:
 push   ecx
.L48dad1:
 lea    eax,[edi+0x14c]
.L48dad7:
 push   eax
.L48dad8:
 push   ecx
.L48dad9:
 lea    eax,[edi+0x4c]
.L48dadc:
 push   eax
.L48dadd:
 push   ecx
.L48dade:
 mov    ecx,DWORD PTR [edi+0x44]
.L48dae1:
 lea    esi,[edi+0x3c]
.L48dae4:
 push   esi
.L48dae5:
 push   DWORD PTR [edi+0x38]
.L48dae8:
 call target_4f87e0
.L48daed:
 jmp .L48db10
.L48daef:
 mov    edx,DWORD PTR [edi+0x48]
.L48daf2:
 lea    ecx,[edi+0x40]
.L48daf5:
 push   ecx
.L48daf6:
 lea    eax,[edi+0x14c]
.L48dafc:
 push   eax
.L48dafd:
 push   ecx
.L48dafe:
 lea    eax,[edi+0x4c]
.L48db01:
 push   eax
.L48db02:
 push   ecx
.L48db03:
 lea    esi,[edi+0x3c]
.L48db06:
 push   esi
.L48db07:
 push   ecx
.L48db08:
 mov    ecx,DWORD PTR [edi+0x44]
.L48db0b:
 call target_4f9080
.L48db10:
 add    esp,0x1c
.L48db13:
 push   DWORD PTR [edi+0x44]
.L48db16:
 mov    BYTE PTR [esp+0x17],al
.L48db1a:
 call   DWORD PTR [0x92d4a0]
.L48db20:
 add    esp,0x4
.L48db23:
 mov    DWORD PTR [edi+0x44],0x0
.L48db2a:
 cmp    BYTE PTR [esp+0x13],0x0
.L48db2f:
 mov    DWORD PTR [edi+0x48],0x0
.L48db36:
 jne .L48db50
.L48db38:
 push   DWORD PTR [esi]
.L48db3a:
 call   DWORD PTR [0x92d4a0]
.L48db40:
 add    esp,0x4
.L48db43:
 mov    DWORD PTR [esi],0x0
.L48db49:
 mov    DWORD PTR [edi+0x40],0x0
.L48db50:
 push   DWORD PTR [edi+0x18]
.L48db53:
 call   DWORD PTR [0x92d120]
.L48db59:
 push   0xffffffff
.L48db5b:
 push   DWORD PTR [edi+0x14]
.L48db5e:
 call   DWORD PTR [0x92d124]
.L48db64:
 cmp    BYTE PTR [edi+0x1c],0x0
.L48db68:
 mov    ecx,0xffffffff
.L48db6d:
 je .L48d9f0
.L48db73:
 pop    edi
.L48db74:
 pop    esi
.L48db75:
 {load} xor    eax,eax
.L48db77:
 pop    ebx
.L48db78:
 {load} mov    esp,ebp
.L48db7a:
 pop    ebp
.L48db7b:
 ret
.equ target_416160,0x416160
.equ target_4f87e0,0x4f87e0
.equ target_4f8a90,0x4f8a90
.equ target_4f9080,0x4f9080
