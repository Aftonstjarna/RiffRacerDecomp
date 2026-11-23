# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x528120,0x5281d4); instruction-contiguous extent, INT3 padding excluded.
# Worker thread creation: creates the completion event and worker thread, applies the requested priority and returns the original success/handle result. Called from the application worker.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x528120..0x5281d4
.intel_syntax noprefix
.code32
.text
.global original_worker_thread_create
original_worker_thread_create:
.L528120:
 push   ebp
.L528121:
 {load} mov    ebp,esp
.L528123:
 mov    eax,DWORD PTR [ebp+0x8]
.L528126:
 push   ebx
.L528127:
 push   edi
.L528128:
 {load} mov    edi,ecx
.L52812a:
 push   0x0
.L52812c:
 lea    ebx,[edi+0x8]
.L52812f:
 push   0x0
.L528131:
 mov    DWORD PTR [edi+0x4],eax
.L528134:
 mov    DWORD PTR [ebx],0x9fbe20
.L52813a:
 mov    DWORD PTR [ebx+0x4],0x1
.L528141:
 mov    DWORD PTR [ebx+0x8],0x0
.L528148:
 mov    DWORD PTR [ebx+0xc],0x0
.L52814f:
 push   0x1
.L528151:
 mov    DWORD PTR [edi],0x9fe654
.L528157:
 mov    DWORD PTR [ebx],0x9fe644
.L52815d:
 push   0x0
.L52815f:
 mov    BYTE PTR [edi+0x28],0x0
.L528163:
 call   DWORD PTR [0x92d114]
.L528169:
 push   0x0
.L52816b:
 push   0x0
.L52816d:
 push   0x1
.L52816f:
 push   0x0
.L528171:
 mov    DWORD PTR [edi+0x1c],eax
.L528174:
 call   DWORD PTR [0x92d114]
.L52817a:
 mov    DWORD PTR [edi+0x18],eax
.L52817d:
 lea    eax,[ebx+0xc]
.L528180:
 push   eax
.L528181:
 push   0x0
.L528183:
 push   ebx
.L528184:
 push   0x48dc50
.L528189:
 push   0x0
.L52818b:
 push   0x0
.L52818d:
 call   DWORD PTR [0x92d37c]
.L528193:
 add    esp,0x18
.L528196:
 mov    DWORD PTR [ebx+0x8],eax
.L528199:
 cmp    eax,0xffffffff
.L52819c:
 je .L5281c1
.L52819e:
 mov    ecx,DWORD PTR [ebx+0x4]
.L5281a1:
 {load} xor    edx,edx
.L5281a3:
 {load} sub    ecx,edx
.L5281a5:
 je .L5281b6
.L5281a7:
 dec    ecx
.L5281a8:
 je .L5281b2
.L5281aa:
 dec    ecx
.L5281ab:
 jne .L5281b9
.L5281ad:
 lea    edx,[ecx+0x1]
.L5281b0:
 jmp .L5281b9
.L5281b2:
 {load} xor    edx,edx
.L5281b4:
 jmp .L5281b9
.L5281b6:
 or     edx,0xffffffff
.L5281b9:
 push   edx
.L5281ba:
 push   eax
.L5281bb:
 call   DWORD PTR [0x92d0d8]
.L5281c1:
 push   0xffffffff
.L5281c3:
 push   DWORD PTR [edi+0x1c]
.L5281c6:
 call   DWORD PTR [0x92d124]
.L5281cc:
 {load} mov    eax,edi
.L5281ce:
 pop    edi
.L5281cf:
 pop    ebx
.L5281d0:
 pop    ebp
.L5281d1:
 ret    0x4
