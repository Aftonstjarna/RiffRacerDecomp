# Reviewed symbolic assembly reference evidence; not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2
# Complete VA [0x48a260,0x48a2dd); instruction-contiguous extent, INT3 padding excluded.
# Archive member clone: allocates and copies a member record through the original operator new/delete and bad_alloc import. Called from archive member verification.
# Derived from original instructions; reference-assembly evidence only, no matching-source credit.
# UNREVIEWED generated draft: inspect control flow and verify rebuilt bytes.
# Original VA range 0x48a260..0x48a2dd
.intel_syntax noprefix
.code32
.text
.global original_archive_member_clone
original_archive_member_clone:
.L48a260:
 push   ebp
.L48a261:
 {load} mov    ebp,esp
.L48a263:
 push   ebx
.L48a264:
 push   esi
.L48a265:
 push   edi
.L48a266:
 mov    edi,DWORD PTR [ebp+0x8]
.L48a269:
 {load} xor    esi,esi
.L48a26b:
 {load} mov    ebx,ecx
.L48a26d:
 test   edi,edi
.L48a26f:
 je .L48a296
.L48a271:
 cmp    edi,0x1fffffff
.L48a277:
 ja .L48a290
.L48a279:
 lea    eax,[edi*8+0x0]
.L48a280:
 push   eax
.L48a281:
 call   DWORD PTR [0x92d4b4]
.L48a287:
 {load} mov    esi,eax
.L48a289:
 add    esp,0x4
.L48a28c:
 test   esi,esi
.L48a28e:
 jne .L48a296
.L48a290:
 call   DWORD PTR [0x92d164]
.L48a296:
 push   DWORD PTR [ebp+0x8]
.L48a299:
 mov    edx,DWORD PTR [ebx+0x4]
.L48a29c:
 mov    ecx,DWORD PTR [ebx]
.L48a29e:
 sub    esp,0x8
.L48a2a1:
 push   esi
.L48a2a2:
 call target_48a350
.L48a2a7:
 mov    ecx,DWORD PTR [ebx]
.L48a2a9:
 add    esp,0x10
.L48a2ac:
 mov    eax,DWORD PTR [ebx+0x4]
.L48a2af:
 {load} sub    eax,ecx
.L48a2b1:
 sar    eax,0x3
.L48a2b4:
 mov    DWORD PTR [ebp+0x8],eax
.L48a2b7:
 test   ecx,ecx
.L48a2b9:
 je .L48a2c5
.L48a2bb:
 push   ecx
.L48a2bc:
 call   DWORD PTR [0x92d4b0]
.L48a2c2:
 add    esp,0x4
.L48a2c5:
 lea    eax,[esi+edi*8]
.L48a2c8:
 mov    DWORD PTR [ebx],esi
.L48a2ca:
 mov    DWORD PTR [ebx+0x8],eax
.L48a2cd:
 mov    eax,DWORD PTR [ebp+0x8]
.L48a2d0:
 pop    edi
.L48a2d1:
 lea    eax,[esi+eax*8]
.L48a2d4:
 pop    esi
.L48a2d5:
 mov    DWORD PTR [ebx+0x4],eax
.L48a2d8:
 pop    ebx
.L48a2d9:
 pop    ebp
.L48a2da:
 ret    0x4
.equ target_48a350,0x48a350
