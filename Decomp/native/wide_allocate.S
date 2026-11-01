# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original instructions and private Ghidra exports in development:
# /tmp/cloud-string-growth/{*.asm,exports,eh-data.txt,messages.txt,pe.txt,ghidra.log}.
# Private Strings DB copied from /tmp/cloud-path-refresh; no shared DB writes.
# Exact instruction bodies; following INT3 padding excluded; no inline data.
# String layout: +0 inline WCHAR[8]/pointer, +0x10 length, +0x14 capacity;
# capacity<8 selects inline storage. External CRT/EH/data keep original VAs.
# VA [0x44ff40,0x44ff71); stack WCHAR count; RET 4 (callee cleanup).
# ECX is not an input; EBP preserved; EAX=pointer, or zero for zero count.
# Rejects count>0x7fffffff/null allocation via std::_Xbad_alloc (0x92d164);
# otherwise operator new(count*2) through IAT 0x92d4b4. No local EH;
# allocation exceptions propagate to growth retry handler.
.intel_syntax noprefix
.code32
.text
.global original_wide_allocate
original_wide_allocate:
.L44ff40:
 push   ebp
.L44ff41:
 {load} mov    ebp,esp
.L44ff43:
 mov    eax,DWORD PTR [ebp+0x8]
.L44ff46:
 {load} xor    ecx,ecx
.L44ff48:
 test   eax,eax
.L44ff4a:
 je .L44ff6b
.L44ff4c:
 cmp    eax,0x7fffffff
.L44ff51:
 ja .L44ff65
.L44ff53:
 {load} add    eax,eax
.L44ff55:
 push   eax
.L44ff56:
 call   DWORD PTR [0x92d4b4]
.L44ff5c:
 {load} mov    ecx,eax
.L44ff5e:
 add    esp,0x4
.L44ff61:
 test   ecx,ecx
.L44ff63:
 jne .L44ff6b
.L44ff65:
 call   DWORD PTR [0x92d164]
.L44ff6b:
 {load} mov    eax,ecx
.L44ff6d:
 pop    ebp
.L44ff6e:
 ret    0x4
