.intel_syntax noprefix
.code32
.text
# Mechanically transcribed reference evidence, not high-level recovery.
# Game.exe SHA-256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2; VA 0x41db40.
.global original_worker_record12_range_destroy
original_worker_record12_range_destroy:
 push   ebp
 {load} mov    ebp,esp
 push   0xffffffff
 push   0x8fdb73
 mov    eax,fs:[0]
 push   eax
 sub    esp,0x8
 push   ebx
 push   esi
 push   edi
 mov    eax,DWORD PTR [0xbaabc0]
 {load} xor    eax,ebp
 push   eax
 lea    eax,[ebp-0xc]
 mov    fs:[0],eax
 {load} mov    eax,edx
 mov    DWORD PTR [ebp-0x10],eax
 {load} mov    edi,ecx
 mov    DWORD PTR [ebp-0x14],edi
 {load} cmp    edi,eax
 je .L41dc9e
 {disp32} lea ebx,[ebx+0]
.L41db80:
 mov    DWORD PTR [ebp-0x4],0x0
 mov    ecx,DWORD PTR [edi+0x8]
 test   ecx,ecx
 je .L41dba7
 mov    eax,DWORD PTR [ecx+0x4]
 add    ecx,0x4
 mov    eax,DWORD PTR [eax+0x4]
 {load} add    ecx,eax
 dec    DWORD PTR [ecx+0x4]
 jne .L41dba4
 mov    eax,DWORD PTR [ecx]
 push   0x1
 call   DWORD PTR [eax]
.L41dba4:
 mov    eax,DWORD PTR [ebp-0x10]
.L41dba7:
 mov    DWORD PTR [ebp-0x4],0xffffffff
 mov    ebx,DWORD PTR [edi+0x4]
 test   ebx,ebx
 js .L41dc90
 mov    esi,DWORD PTR [0xc0d3d8]
 test   esi,esi
 jne .L41dc0f
 push   0x58
 call   DWORD PTR [0x92d4b4]
 {load} mov    esi,eax
 add    esp,0x4
 mov    DWORD PTR [ebp-0x14],esi
 mov    DWORD PTR [ebp-0x4],0x1
 test   esi,esi
 je .L41dc00
 push   0xbaac0c
 lea    ecx,[esi+0x4]
 mov    WORD PTR [esi],0x100
 mov    BYTE PTR [esi+0x2],0x5c
 call constructor
 mov    WORD PTR [esi+0x54],0x100
 mov    BYTE PTR [esi+0x56],0x5c
 jmp .L41dc02
.L41dc00:
 {load} xor    esi,esi
.L41dc02:
 mov    DWORD PTR [ebp-0x4],0xffffffff
 mov    DWORD PTR [0xc0d3d8],esi
.L41dc0f:
 mov    eax,DWORD PTR [esi+0x4]
 movsx  ecx,WORD PTR [eax+ebx*2]
 mov    eax,DWORD PTR [esi+0x28]
 dec    DWORD PTR [eax+ecx*8+0x4]
 cmp    DWORD PTR [eax+ecx*8+0x4],0x0
 jne .L41dc86
 mov    esi,DWORD PTR [0xc0d3d8]
 mov    ebx,DWORD PTR [edi+0x4]
 test   esi,esi
 jne .L41dc7d
 push   0x58
 call   DWORD PTR [0x92d4b4]
 {load} mov    esi,eax
 add    esp,0x4
 mov    DWORD PTR [ebp-0x14],esi
 mov    DWORD PTR [ebp-0x4],0x2
 test   esi,esi
 je .L41dc6e
 push   0xbaac0c
 lea    ecx,[esi+0x4]
 mov    WORD PTR [esi],0x100
 mov    BYTE PTR [esi+0x2],0x5c
 call constructor
 mov    WORD PTR [esi+0x54],0x100
 mov    BYTE PTR [esi+0x56],0x5c
 jmp .L41dc70
.L41dc6e:
 {load} xor    esi,esi
.L41dc70:
 mov    DWORD PTR [ebp-0x4],0xffffffff
 mov    DWORD PTR [0xc0d3d8],esi
.L41dc7d:
 push   ebx
 lea    ecx,[esi+0x4]
 call release_handle
.L41dc86:
 mov    eax,DWORD PTR [ebp-0x10]
 mov    DWORD PTR [edi+0x4],0xffffffff
.L41dc90:
 add    edi,0xc
 mov    DWORD PTR [ebp-0x14],edi
 {load} cmp    edi,eax
 jne .L41db80
.L41dc9e:
 mov    ecx,DWORD PTR [ebp-0xc]
 mov    DWORD PTR fs:[0],ecx
 pop    ecx
 pop    edi
 pop    esi
 pop    ebx
 {load} mov    esp,ebp
 pop    ebp
 ret
.equ constructor,0x417810
.equ release_handle,0x41c090
.section .note.GNU-stack,"",@progbits
