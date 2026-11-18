# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x51db50.
.intel_syntax noprefix
.code32
.text
.global original_worker_reserve_record_vectors
.equ dep_51fc10,0x51fc10
.equ dep_51fd40,0x51fd40
.equ dep_51fe60,0x51fe60
.equ dep_51ff50,0x51ff50
.equ dep_520080,0x520080
original_worker_reserve_record_vectors:
 push   ebx
 push   esi
 push   edi
 lea    esi,[ecx+0x28]
 mov    ebx,0x4
 jmp .L51db60
 {disp8} lea ecx,[ecx+0x0]
.L51db60:
 mov    ecx,DWORD PTR [esi-0xc]
 mov    eax,0x66666667
 sub    ecx,DWORD PTR [esi-0x14]
 imul   ecx
 sar    edx,0x4
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x20
 jae .L51db86
 push   0x20
 lea    ecx,[esi-0x14]
 call dep_51fc10
.L51db86:
 mov    ecx,DWORD PTR [esi]
 mov    eax,0x66666667
 sub    ecx,DWORD PTR [esi-0x8]
 imul   ecx
 sar    edx,0x4
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x40
 jae .L51dbab
 push   0x40
 lea    ecx,[esi-0x8]
 call dep_51fc10
.L51dbab:
 mov    ecx,DWORD PTR [esi+0xc]
 mov    eax,0x92492493
 sub    ecx,DWORD PTR [esi+0x4]
 imul   ecx
 add.s    edx,ecx
 sar    edx,0x5
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x20
 jae .L51dbd3
 push   0x20
 lea    ecx,[esi+0x4]
 call dep_51fd40
.L51dbd3:
 mov    ecx,DWORD PTR [esi+0x18]
 mov    eax,0x92492493
 sub    ecx,DWORD PTR [esi+0x10]
 imul   ecx
 add.s    edx,ecx
 sar    edx,0x5
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x20
 jae .L51dbfb
 push   0x20
 lea    ecx,[esi+0x10]
 call dep_51fd40
.L51dbfb:
 mov    eax,DWORD PTR [esi+0x24]
 lea    ecx,[esi+0x1c]
 sub    eax,DWORD PTR [ecx]
 sar    eax,0x6
 cmp    eax,0x20
 jae .L51dc12
 push   0x20
 call dep_51fe60
.L51dc12:
 mov    ecx,DWORD PTR [esi+0x30]
 mov    eax,0x30c30c31
 sub    ecx,DWORD PTR [esi+0x28]
 imul   ecx
 sar    edx,0x4
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x20
 jae .L51dc38
 push   0x20
 lea    ecx,[esi+0x28]
 call dep_51ff50
.L51dc38:
 mov    ecx,DWORD PTR [esi+0x3c]
 mov    eax,0x30c30c31
 sub    ecx,DWORD PTR [esi+0x34]
 imul   ecx
 sar    edx,0x4
 mov.s    eax,edx
 shr    eax,0x1f
 add.s    eax,edx
 cmp    eax,0x20
 jae .L51dc5e
 push   0x20
 lea    ecx,[esi+0x34]
 call dep_51ff50
.L51dc5e:
 mov    eax,DWORD PTR [esi+0x48]
 lea    ecx,[esi+0x40]
 sub    eax,DWORD PTR [ecx]
 sar    eax,0x5
 cmp    eax,0x20
 jae .L51dc75
 push   0x20
 call dep_520080
.L51dc75:
 add    esi,0x74
 dec    ebx
 jne .L51db60
 pop    edi
 pop    esi
 pop    ebx
 ret
.section .note.GNU-stack,"",@progbits
