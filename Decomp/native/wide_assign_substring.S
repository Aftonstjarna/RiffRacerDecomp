# Supported Game.exe SHA256 2d1af8a01ec6b1e3477ff6dbe4a44895828e2ac71449344fec9d7d99e87a58e2.
# Reviewed original instructions and private Ghidra exports in development:
# /tmp/cloud-string-growth/{*.asm,exports,eh-data.txt,messages.txt,pe.txt,ghidra.log}.
# Private Strings DB copied from /tmp/cloud-path-refresh; no shared DB writes.
# Exact instruction bodies; following INT3 padding excluded; no inline data.
# String layout: +0 inline WCHAR[8]/pointer, +0x10 length, +0x14 capacity;
# capacity<8 selects inline storage. External CRT/EH/data keep original VAs.
# VA [0x44fb30,0x44fc27); ECX=destination; stack source-string,position,count.
# EAX=destination; RET 12; EBX/ESI/EDI/EBP preserved. Position>source length
# throws std::_Xout_of_range via IAT 0x92d16c/message 0x99995c (invalid string
# position). Clamps count to remaining source length. Self assignment truncates
# at position+count then erases prefix. Distinct source: guard 0x7ffffffe via
# std::_Xlength_error, IAT 0x92d168/message 0x99994c (string too long); grow
# if needed, memcpy count*2 through 0x8f8d66, publish length and WCHAR NUL.
# All empty/inline/heap arms retained. No local EH; exceptions propagate.
.intel_syntax noprefix
.code32
.text
.global original_wide_assign_substring
original_wide_assign_substring:
.L44fb30:
 push   ebp
.L44fb31:
 {load} mov    ebp,esp
.L44fb33:
 push   ebx
.L44fb34:
 mov    ebx,DWORD PTR [ebp+0x8]
.L44fb37:
 push   esi
.L44fb38:
 push   edi
.L44fb39:
 {load} mov    esi,ecx
.L44fb3b:
 mov    ecx,DWORD PTR [ebp+0xc]
.L44fb3e:
 mov    edi,DWORD PTR [ebx+0x10]
.L44fb41:
 {load} cmp    edi,ecx
.L44fb43:
 jae .L44fb50
.L44fb45:
 push   0x99995c
.L44fb4a:
 call   DWORD PTR [0x92d16c]
.L44fb50:
 {load} sub    edi,ecx
.L44fb52:
 cmp    DWORD PTR [ebp+0x10],edi
.L44fb55:
 cmovb  edi,DWORD PTR [ebp+0x10]
.L44fb59:
 {load} cmp    esi,ebx
.L44fb5b:
 jne .L44fb7d
.L44fb5d:
 lea    eax,[edi+ecx*1]
.L44fb60:
 {load} mov    ecx,esi
.L44fb62:
 push   eax
.L44fb63:
 call target_44fcf0
.L44fb68:
 push   DWORD PTR [ebp+0xc]
.L44fb6b:
 {load} mov    ecx,esi
.L44fb6d:
 push   0x0
.L44fb6f:
 call target_44fd30
.L44fb74:
 pop    edi
.L44fb75:
 {load} mov    eax,esi
.L44fb77:
 pop    esi
.L44fb78:
 pop    ebx
.L44fb79:
 pop    ebp
.L44fb7a:
 ret    0xc
.L44fb7d:
 cmp    edi,0x7ffffffe
.L44fb83:
 jbe .L44fb90
.L44fb85:
 push   0x99994c
.L44fb8a:
 call   DWORD PTR [0x92d168]
.L44fb90:
 mov    eax,DWORD PTR [esi+0x14]
.L44fb93:
 {load} cmp    eax,edi
.L44fb95:
 jae .L44fbbb
.L44fb97:
 push   DWORD PTR [esi+0x10]
.L44fb9a:
 {load} mov    ecx,esi
.L44fb9c:
 push   edi
.L44fb9d:
 call target_44fde0
.L44fba2:
 mov    ecx,DWORD PTR [ebp+0xc]
.L44fba5:
 test   edi,edi
.L44fba7:
 je .L44fc1e
.L44fba9:
 cmp    DWORD PTR [ebx+0x14],0x8
.L44fbad:
 jb .L44fbb1
.L44fbaf:
 mov    ebx,DWORD PTR [ebx]
.L44fbb1:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fbb5:
 jb .L44fbe5
.L44fbb7:
 mov    edx,DWORD PTR [esi]
.L44fbb9:
 jmp .L44fbe7
.L44fbbb:
 test   edi,edi
.L44fbbd:
 jne .L44fba9
.L44fbbf:
 mov    DWORD PTR [esi+0x10],edi
.L44fbc2:
 cmp    eax,0x8
.L44fbc5:
 jb .L44fbd7
.L44fbc7:
 mov    eax,DWORD PTR [esi]
.L44fbc9:
 {load} xor    ecx,ecx
.L44fbcb:
 pop    edi
.L44fbcc:
 mov    WORD PTR [eax],cx
.L44fbcf:
 {load} mov    eax,esi
.L44fbd1:
 pop    esi
.L44fbd2:
 pop    ebx
.L44fbd3:
 pop    ebp
.L44fbd4:
 ret    0xc
.L44fbd7:
 {load} mov    eax,esi
.L44fbd9:
 {load} xor    ecx,ecx
.L44fbdb:
 pop    edi
.L44fbdc:
 pop    esi
.L44fbdd:
 pop    ebx
.L44fbde:
 mov    WORD PTR [eax],cx
.L44fbe1:
 pop    ebp
.L44fbe2:
 ret    0xc
.L44fbe5:
 {load} mov    edx,esi
.L44fbe7:
 test   edi,edi
.L44fbe9:
 je .L44fbfc
.L44fbeb:
 lea    eax,[edi+edi*1]
.L44fbee:
 push   eax
.L44fbef:
 lea    eax,[ebx+ecx*2]
.L44fbf2:
 push   eax
.L44fbf3:
 push   edx
.L44fbf4:
 call target_8f8d66
.L44fbf9:
 add    esp,0xc
.L44fbfc:
 cmp    DWORD PTR [esi+0x14],0x8
.L44fc00:
 mov    DWORD PTR [esi+0x10],edi
.L44fc03:
 jb .L44fc16
.L44fc05:
 mov    eax,DWORD PTR [esi]
.L44fc07:
 {load} xor    ecx,ecx
.L44fc09:
 mov    WORD PTR [eax+edi*2],cx
.L44fc0d:
 {load} mov    eax,esi
.L44fc0f:
 pop    edi
.L44fc10:
 pop    esi
.L44fc11:
 pop    ebx
.L44fc12:
 pop    ebp
.L44fc13:
 ret    0xc
.L44fc16:
 {load} mov    eax,esi
.L44fc18:
 {load} xor    ecx,ecx
.L44fc1a:
 mov    WORD PTR [eax+edi*2],cx
.L44fc1e:
 pop    edi
.L44fc1f:
 {load} mov    eax,esi
.L44fc21:
 pop    esi
.L44fc22:
 pop    ebx
.L44fc23:
 pop    ebp
.L44fc24:
 ret    0xc
.equ target_44fcf0,0x44fcf0
.equ target_44fd30,0x44fd30
.equ target_44fde0,0x44fde0
.equ target_8f8d66,0x8f8d66
