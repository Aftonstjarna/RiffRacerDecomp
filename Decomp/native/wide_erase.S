# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original instructions and private Ghidra exports in development:
# /tmp/cloud-string-growth/{*.asm,exports,eh-data.txt,messages.txt,pe.txt,ghidra.log}.
# Private Strings DB copied from /tmp/cloud-path-refresh; no shared DB writes.
# Exact instruction bodies; following INT3 padding excluded; no inline data.
# String layout: +0 inline WCHAR[8]/pointer, +0x10 length, +0x14 capacity;
# capacity<8 selects inline storage. External CRT/EH/data keep original VAs.
# VA [0x44fd30,0x44fdd5); ECX=this; stack position,count; EAX=this; RET 8.
# EBP/ESI/EDI and EBX(on shifting path) preserved. Rejects position>length
# via std::_Xout_of_range (IAT 0x92d16c/message 0x99995c). Count reaching
# end truncates; otherwise nonzero count shifts suffix via memmove (0x92d4a4)
# and writes length/WCHAR NUL. Zero count is a no-op. Inline/heap arms retained.
# No local EH; exceptions propagate.
.intel_syntax noprefix
.code32
.text
.global original_wide_erase
original_wide_erase:
.L44fd30:
 push   ebp
.L44fd31:
 {load} mov    ebp,esp
.L44fd33:
 push   esi
.L44fd34:
 {load} mov    esi,ecx
.L44fd36:
 mov    ecx,DWORD PTR [ebp+0x8]
.L44fd39:
 push   edi
.L44fd3a:
 mov    edi,DWORD PTR [esi+0x10]
.L44fd3d:
 {load} cmp    edi,ecx
.L44fd3f:
 jae .L44fd4c
.L44fd41:
 push   0x99995c
.L44fd46:
 call   DWORD PTR [0x92d16c]
.L44fd4c:
 mov    edx,DWORD PTR [ebp+0xc]
.L44fd4f:
 {load} mov    eax,edi
.L44fd51:
 {load} sub    eax,ecx
.L44fd53:
 {load} cmp    eax,edx
.L44fd55:
 ja .L44fd7e
.L44fd57:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fd5b:
 mov    DWORD PTR [esi+0x10],ecx
.L44fd5e:
 jb .L44fd70
.L44fd60:
 mov    eax,DWORD PTR [esi]
.L44fd62:
 {load} xor    edx,edx
.L44fd64:
 pop    edi
.L44fd65:
 mov    WORD PTR [eax+ecx*2],dx
.L44fd69:
 {load} mov    eax,esi
.L44fd6b:
 pop    esi
.L44fd6c:
 pop    ebp
.L44fd6d:
 ret    0x8
.L44fd70:
 {load} mov    eax,esi
.L44fd72:
 {load} xor    edx,edx
.L44fd74:
 pop    edi
.L44fd75:
 pop    esi
.L44fd76:
 mov    WORD PTR [eax+ecx*2],dx
.L44fd7a:
 pop    ebp
.L44fd7b:
 ret    0x8
.L44fd7e:
 test   edx,edx
.L44fd80:
 je .L44fdcd
.L44fd82:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fd86:
 jb .L44fd8c
.L44fd88:
 mov    eax,DWORD PTR [esi]
.L44fd8a:
 jmp .L44fd8e
.L44fd8c:
 {load} mov    eax,esi
.L44fd8e:
 {load} sub    edi,edx
.L44fd90:
 push   ebx
.L44fd91:
 lea    ebx,[eax+ecx*2]
.L44fd94:
 {load} mov    eax,edi
.L44fd96:
 {load} sub    eax,ecx
.L44fd98:
 je .L44fdab
.L44fd9a:
 {load} add    eax,eax
.L44fd9c:
 push   eax
.L44fd9d:
 lea    eax,[ebx+edx*2]
.L44fda0:
 push   eax
.L44fda1:
 push   ebx
.L44fda2:
 call   DWORD PTR [0x92d4a4]
.L44fda8:
 add    esp,0xc
.L44fdab:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fdaf:
 mov    DWORD PTR [esi+0x10],edi
.L44fdb2:
 pop    ebx
.L44fdb3:
 jb .L44fdc5
.L44fdb5:
 mov    eax,DWORD PTR [esi]
.L44fdb7:
 {load} xor    ecx,ecx
.L44fdb9:
 mov    WORD PTR [eax+edi*2],cx
.L44fdbd:
 {load} mov    eax,esi
.L44fdbf:
 pop    edi
.L44fdc0:
 pop    esi
.L44fdc1:
 pop    ebp
.L44fdc2:
 ret    0x8
.L44fdc5:
 {load} mov    eax,esi
.L44fdc7:
 {load} xor    ecx,ecx
.L44fdc9:
 mov    WORD PTR [eax+edi*2],cx
.L44fdcd:
 pop    edi
.L44fdce:
 {load} mov    eax,esi
.L44fdd0:
 pop    esi
.L44fdd1:
 pop    ebp
.L44fdd2:
 ret    0x8
