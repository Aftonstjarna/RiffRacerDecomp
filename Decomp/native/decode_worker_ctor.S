# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed objdump /tmp/cloud-worker-review/ctor.asm and private Ghidra
# /tmp/cloud-cleanup-review/exports/0048d6e0.txt; no shared database writes.
# ECX=this, EAX=this; preserves EBX/EDI, plain ret, no stack arguments.
# Vtable 0x9fbdf0 slots: deleting wrapper 0x48d7d0, start 0x48dbc0,
# dispatch 0x48d9c0. +8 thread handle, +0xc thread ID, +4 priority mode.
# +0x20 is 24-byte narrow SSO string (size +0x30, capacity +0x34).
# Initializes stop +0x1c, request/output +0x38..+0x48, text +0x4c/+0x14c.
# CreateEventA gives auto-reset nonsignaled +0x14 and manual-reset signaled
# +0x18; _beginthreadex receives this and +0xc through existing 0x48dc50.
# Preserve original failure test ==-1 (not a corrected zero test), unchecked
# event failures and priority mapping 0/-1, 1/0, 2/1, other/0.
# No SEH registration or failure cleanup; calls retain stdcall/cdecl ABI.
# Bounds exclude following INT3 padding; no inline data.
# Original VA range 0x48d6e0..0x48d7ca
.intel_syntax noprefix
.code32
.text
.global original_decode_worker_ctor
original_decode_worker_ctor:
.L48d6e0:
 push   ebx
.L48d6e1:
 {load} mov    ebx,ecx
.L48d6e3:
 push   edi
.L48d6e4:
 mov    DWORD PTR [ebx+0xc],0x0
.L48d6eb:
 lea    edi,[ebx+0xc]
.L48d6ee:
 push   0x0
.L48d6f0:
 mov    DWORD PTR [ebx+0x4],0x1
.L48d6f7:
 mov    DWORD PTR [ebx+0x8],0x0
.L48d6fe:
 mov    DWORD PTR [ebx],0x9fbdf0
.L48d704:
 mov    BYTE PTR [ebx+0x10],0x0
.L48d708:
 mov    BYTE PTR [ebx+0x1c],0x0
.L48d70c:
 mov    DWORD PTR [ebx+0x34],0xf
.L48d713:
 mov    DWORD PTR [ebx+0x30],0x0
.L48d71a:
 mov    BYTE PTR [ebx+0x20],0x0
.L48d71e:
 push   0x0
.L48d720:
 push   0x0
.L48d722:
 mov    DWORD PTR [ebx+0x38],0x0
.L48d729:
 mov    DWORD PTR [ebx+0x3c],0x0
.L48d730:
 mov    DWORD PTR [ebx+0x40],0x0
.L48d737:
 mov    DWORD PTR [ebx+0x44],0x0
.L48d73e:
 mov    DWORD PTR [ebx+0x48],0x0
.L48d745:
 push   0x0
.L48d747:
 mov    BYTE PTR [ebx+0x4c],0x0
.L48d74b:
 mov    BYTE PTR [ebx+0x14c],0x0
.L48d752:
 call   DWORD PTR [0x92d114]
.L48d758:
 push   0x0
.L48d75a:
 push   0x1
.L48d75c:
 push   0x1
.L48d75e:
 push   0x0
.L48d760:
 mov    DWORD PTR [ebx+0x14],eax
.L48d763:
 call   DWORD PTR [0x92d114]
.L48d769:
 push   edi
.L48d76a:
 push   0x0
.L48d76c:
 push   ebx
.L48d76d:
 push   0x48dc50
.L48d772:
 push   0x0
.L48d774:
 push   0x0
.L48d776:
 mov    DWORD PTR [ebx+0x18],eax
.L48d779:
 call   DWORD PTR [0x92d37c]
.L48d77f:
 add    esp,0x18
.L48d782:
 mov    DWORD PTR [ebx+0x8],eax
.L48d785:
 cmp    eax,0xffffffff
.L48d788:
 je .L48d7c5
.L48d78a:
 mov    ecx,DWORD PTR [ebx+0x4]
.L48d78d:
 {load} xor    edx,edx
.L48d78f:
 {load} sub    ecx,edx
.L48d791:
 je .L48d7ba
.L48d793:
 dec    ecx
.L48d794:
 je .L48d7ab
.L48d796:
 dec    ecx
.L48d797:
 jne .L48d7bd
.L48d799:
 mov    edx,0x1
.L48d79e:
 push   edx
.L48d79f:
 push   eax
.L48d7a0:
 call   DWORD PTR [0x92d0d8]
.L48d7a6:
 pop    edi
.L48d7a7:
 {load} mov    eax,ebx
.L48d7a9:
 pop    ebx
.L48d7aa:
 ret
.L48d7ab:
 {load} xor    edx,edx
.L48d7ad:
 push   edx
.L48d7ae:
 push   eax
.L48d7af:
 call   DWORD PTR [0x92d0d8]
.L48d7b5:
 pop    edi
.L48d7b6:
 {load} mov    eax,ebx
.L48d7b8:
 pop    ebx
.L48d7b9:
 ret
.L48d7ba:
 or     edx,0xffffffff
.L48d7bd:
 push   edx
.L48d7be:
 push   eax
.L48d7bf:
 call   DWORD PTR [0x92d0d8]
.L48d7c5:
 pop    edi
.L48d7c6:
 {load} mov    eax,ebx
.L48d7c8:
 pop    ebx
.L48d7c9:
 ret
