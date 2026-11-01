# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original instructions and private Ghidra exports in development:
# /tmp/cloud-string-growth/{*.asm,exports,eh-data.txt,messages.txt,pe.txt,ghidra.log}.
# Private Strings DB copied from /tmp/cloud-path-refresh; no shared DB writes.
# Exact instruction bodies; following INT3 padding excluded; no inline data.
# String layout: +0 inline WCHAR[8]/pointer, +0x10 length, +0x14 capacity;
# capacity<8 selects inline storage. External CRT/EH/data keep original VAs.
# VA [0x44fcf0,0x44fd2f); ECX=this, stack new_length; EAX=this; RET 4.
# EBP/ESI preserved. Rejects new_length>length via std::_Xout_of_range
# (IAT 0x92d16c/message 0x99995c), then sets length and WCHAR NUL.
# Both storage arms retained; no allocation/local EH; exceptions propagate.
.intel_syntax noprefix
.code32
.text
.global original_wide_truncate
original_wide_truncate:
.L44fcf0:
 push   ebp
.L44fcf1:
 {load} mov    ebp,esp
.L44fcf3:
 mov    eax,DWORD PTR [ebp+0x8]
.L44fcf6:
 cmp    DWORD PTR [ecx+0x10],eax
.L44fcf9:
 jae .L44fd06
.L44fcfb:
 push   0x99995c
.L44fd00:
 call   DWORD PTR [0x92d16c]
.L44fd06:
 cmp    DWORD PTR [ecx+0x14],0x8
.L44fd0a:
 mov    DWORD PTR [ecx+0x10],eax
.L44fd0d:
 jb .L44fd1f
.L44fd0f:
 mov    edx,DWORD PTR [ecx]
.L44fd11:
 push   esi
.L44fd12:
 {load} xor    esi,esi
.L44fd14:
 mov    WORD PTR [edx+eax*2],si
.L44fd18:
 {load} mov    eax,ecx
.L44fd1a:
 pop    esi
.L44fd1b:
 pop    ebp
.L44fd1c:
 ret    0x4
.L44fd1f:
 {load} mov    edx,ecx
.L44fd21:
 push   esi
.L44fd22:
 {load} xor    esi,esi
.L44fd24:
 mov    WORD PTR [edx+eax*2],si
.L44fd28:
 {load} mov    eax,ecx
.L44fd2a:
 pop    esi
.L44fd2b:
 pop    ebp
.L44fd2c:
 ret    0x4
