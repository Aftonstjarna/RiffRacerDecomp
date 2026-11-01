# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original objdump listings and private Ghidra exports:
# /tmp/cloud-path-refresh/{exports,*.asm,pe.txt,ghidra.log}; no shared DB writes.
# Exact function bodies; following INT3 padding excluded; no inline data.
# VA [0x44f8f0,0x44f9a1); Ghidra inclusive end 0x44f9a0.
# ECX=wide string; stack +8 unused, +12 UTF-16 character; EAX=this, RET 8.
# ESI/EDI/EBP preserved. Length at +0x10, capacity at +0x14; capacity<8
# selects inline storage, otherwise pointer at +0. Appends exactly one WCHAR
# and NUL, growing via unresolved 0x44fde0(new_length, old_length) as needed.
# Both unsigned overflow guards and all zero-length return arms retained.
# IAT 0x92d168 is std::_Xlength_error; message 0x99994c: string too long.
# No local SEH/cookie; allocation/length exceptions propagate to caller.
.intel_syntax noprefix
.code32
.text
.global original_wide_append_char
original_wide_append_char:
.L44f8f0:
 push   ebp
.L44f8f1:
 {load} mov    ebp,esp
.L44f8f3:
 push   esi
.L44f8f4:
 {load} mov    esi,ecx
.L44f8f6:
 or     eax,0xffffffff
.L44f8f9:
 push   edi
.L44f8fa:
 mov    ecx,DWORD PTR [esi+0x10]
.L44f8fd:
 {load} sub    eax,ecx
.L44f8ff:
 cmp    eax,0x1
.L44f902:
 ja .L44f90f
.L44f904:
 push   0x99994c
.L44f909:
 call   DWORD PTR [0x92d168]
.L44f90f:
 lea    edi,[ecx+0x1]
.L44f912:
 cmp    edi,0x7ffffffe
.L44f918:
 jbe .L44f925
.L44f91a:
 push   0x99994c
.L44f91f:
 call   DWORD PTR [0x92d168]
.L44f925:
 mov    eax,DWORD PTR [esi+0x14]
.L44f928:
 {load} cmp    eax,edi
.L44f92a:
 jae .L44f946
.L44f92c:
 push   ecx
.L44f92d:
 push   edi
.L44f92e:
 {load} mov    ecx,esi
.L44f930:
 call target_44fde0
.L44f935:
 test   edi,edi
.L44f937:
 je .L44f999
.L44f939:
 cmp    DWORD PTR [esi+0x14],0x8
.L44f93d:
 mov    edx,DWORD PTR [esi+0x10]
.L44f940:
 jb .L44f96e
.L44f942:
 mov    ecx,DWORD PTR [esi]
.L44f944:
 jmp .L44f970
.L44f946:
 test   edi,edi
.L44f948:
 jne .L44f939
.L44f94a:
 mov    DWORD PTR [esi+0x10],edi
.L44f94d:
 cmp    eax,0x8
.L44f950:
 jb .L44f961
.L44f952:
 mov    eax,DWORD PTR [esi]
.L44f954:
 {load} xor    ecx,ecx
.L44f956:
 pop    edi
.L44f957:
 mov    WORD PTR [eax],cx
.L44f95a:
 {load} mov    eax,esi
.L44f95c:
 pop    esi
.L44f95d:
 pop    ebp
.L44f95e:
 ret    0x8
.L44f961:
 {load} mov    eax,esi
.L44f963:
 {load} xor    ecx,ecx
.L44f965:
 pop    edi
.L44f966:
 pop    esi
.L44f967:
 mov    WORD PTR [eax],cx
.L44f96a:
 pop    ebp
.L44f96b:
 ret    0x8
.L44f96e:
 {load} mov    ecx,esi
.L44f970:
 mov    ax,WORD PTR [ebp+0xc]
.L44f974:
 mov    WORD PTR [ecx+edx*2],ax
.L44f978:
 cmp    DWORD PTR [esi+0x14],0x8
.L44f97c:
 mov    DWORD PTR [esi+0x10],edi
.L44f97f:
 jb .L44f991
.L44f981:
 mov    eax,DWORD PTR [esi]
.L44f983:
 {load} xor    ecx,ecx
.L44f985:
 mov    WORD PTR [eax+edi*2],cx
.L44f989:
 {load} mov    eax,esi
.L44f98b:
 pop    edi
.L44f98c:
 pop    esi
.L44f98d:
 pop    ebp
.L44f98e:
 ret    0x8
.L44f991:
 {load} mov    eax,esi
.L44f993:
 {load} xor    ecx,ecx
.L44f995:
 mov    WORD PTR [eax+edi*2],cx
.L44f999:
 pop    edi
.L44f99a:
 {load} mov    eax,esi
.L44f99c:
 pop    esi
.L44f99d:
 pop    ebp
.L44f99e:
 ret    0x8
.equ target_44fde0,0x44fde0
